#include <assert.h>
#include <common/TextureGL.h>
#include <glWrapper/TextureGL.h>

using namespace OpenGLSandbox::Common;
using namespace OpenGLSandbox::Common::GL;

TextureGL::~TextureGL()
{
}

std::unique_ptr<ITexture> TextureGL::create(const TextureCreateInfo &desc)
{
    // TODO replace by factory where objects automatically get registered
    switch (desc.type)
    {
    case TextureType::_1D:
        return Texture1DGL::create(desc);
    case TextureType::_1D_ARRAY:
        return Texture1DArrayGL::create(desc);
    case TextureType::_2D:
        return Texture2DGL::create(desc);
    case TextureType::_2D_ARRAY:
        return Texture2DArrayGL::create(desc);
    case TextureType::_3D:
        return Texture3DGL::create(desc);
    case TextureType::CUBEMAP:
        return TextureCubeMapGL::create(desc);
    case TextureType::BUFFER:
        return TextureBufferGL::create(desc);
    default:
        assert(false);
        return nullptr;
    }
}

bool TextureGL::setData(const TextureData &textureData)
{
    switch (textureData.getTextureDataType())
    {
    case TextureDataType::NATIVE:
    {
        assert(dynamic_cast<const TextureDataGLTexture *>(&textureData));
        const TextureDataGLTexture &textureDataGLTexture = static_cast<const TextureDataGLTexture &>(textureData);
        setTexture(textureDataGLTexture.getSharedTexture());
    }
    break;
    case TextureDataType::BUFFER:
    {
        assert(false);
        return false;
    }
    break;
    case TextureDataType::POINTER:
    {
        assert(texture_->getTarget() != GL_TEXTURE_BUFFER);
        assert(dynamic_cast<const TextureDataPtr *>(&textureData));
        const TextureDataPtr &dataPtr = static_cast<const TextureDataPtr &>(textureData);

        assert(dataPtr.getPixelFormat() < PixelFormat::NUM_PIXELFORMATS);
        assert(dataPtr.getDataType() < DataType::NUM_DATATYPES);

        assert((!useMipmaps_ && dataPtr.getNumMipMapLevels() == 0) || useMipmaps_);

        GLenum glPixelFormat = getGLPixelFormat(dataPtr.getPixelFormat(), texture_->getInternalFormat());
        GLenum glDataType = getGLDataType(dataPtr.getDataType());

        // update storage for the texture
        if (texture_->getPixelFormat() != glPixelFormat || texture_->getDataType() != glDataType)
        {
            texture_->setPixelFormat(glPixelFormat);
            texture_->setDataType(glDataType);
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // E.g. GL_RGB GL_UNSIGNED_BYTE with odd widths requires this!

        // if no mipmap, then 0 must be there
        unsigned int numMipMapLevels = dataPtr.getNumMipMapLevels() ? dataPtr.getNumMipMapLevels() : 1;

        unsigned int idx = 0;
        for (unsigned int layer = 0; layer < dataPtr.getNumLayers(); ++layer)
        {
            for (unsigned int mipMapLevel = 0; mipMapLevel < numMipMapLevels; ++mipMapLevel)
            {
                upload(mipMapLevel, layer, dataPtr.getDataPtr()[idx++]);
            }
        }
        if (useMipmaps_ && !dataPtr.getNumMipMapLevels())
        {
            texture_->generateMipMap();
        }
    }
    break;

    default:
        assert(false);
        break;
    }

    return true;
}

std::unique_ptr<ITexture> Texture1DGL::create(const TextureCreateInfo &desc)
{
    return std::unique_ptr<ITexture>(new Texture1DGL(desc));
}

/*
Texture1DGL::Texture1DGL(const TextureCreateInfo &desc)
    : TextureGL(GLWrapper::Texture1DGL::create(getGLInternalFormat(description), getGLPixelFormat(description.m_pixelFormat, getGLInternalFormat(description)), getGLDataType(description.m_dataType), static_cast<GLsizei>(description.m_width)), description.m_mipmaps)
{
    DP_ASSERT(description.m_height == 0);
    DP_ASSERT(description.m_depth == 0);
    DP_ASSERT(description.m_layers == 0);
}*/