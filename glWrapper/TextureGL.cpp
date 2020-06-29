#include <assert.h>
#include <ObjectGL.h>
#include <BufferGL.h>
#include <TextureGL.h>
#include <TextureGLFunctionBind.h>
#include <TextureGLFunctionDSA.h>

using namespace OpenGLSandbox::GLWrapper;

class TextureGLUtil
{
public:
    static void getTexData(const TextureGL *texGL, GLenum target, void *data, GLuint mipLevel);
    static size_t getCompressedSizeInByte(GLenum format, GLsizei w, GLsizei h, GLsizei d, GLsizei layers = 0);
    static bool isIntegerInternalFormat(GLenum format);
    static ITextureGLFunction *getTextureGLFunction();
    static unsigned int getMipMapNumLevels(unsigned int w, unsigned int h, unsigned int d);
    static bool isCompressedFormat(GLenum format);
    static GLsizei getMipMapSize(GLsizei sz, GLuint level);
};

void TextureGLUtil::getTexData(const TextureGL *texGL, GLenum target, void *data, GLuint mipLevel)
{
    if (isCompressedFormat(texGL->getPixelFormat()))
    {
        getTextureGLFunction()->getCompressedImage(texGL->getGLId(), texGL->getTarget(), mipLevel, data);
    }
    else
    {
        getTextureGLFunction()->getImage(texGL->getGLId(), texGL->getTarget(), mipLevel, texGL->getPixelFormat(), texGL->getDataType(), data);
    }
}

size_t TextureGLUtil::getCompressedSizeInByte(GLenum format, GLsizei w, GLsizei h, GLsizei d, GLsizei layers /*= 0 */)
{
    // http://www.opengl.org/registry/specs/NV/texture_compression_vtc.txt
    // blocks = ceil(w/4) * ceil(h/4) * d;

    layers = std::max(1, layers);

    size_t blocks = ((w + 3) / 4) * ((h + 3) / 4) * d;

    // written against OpenGL 4.1 compatibility profile

    size_t bytesPerBlock = 0;
    switch (format)
    {
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:

    case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:

    case GL_COMPRESSED_LUMINANCE_LATC1_EXT:
    case GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT:
    case GL_COMPRESSED_RED_RGTC1:
    case GL_COMPRESSED_SIGNED_RED_RGTC1:
        // these formats use 8 bytes per block
        bytesPerBlock = 8;
        break;

    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:

    case GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT:
    case GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT:
    case GL_COMPRESSED_RG_RGTC2:
    case GL_COMPRESSED_SIGNED_RG_RGTC2:

    case GL_COMPRESSED_RGBA_BPTC_UNORM_ARB:
    case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB:

    case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB:
    case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB:
        // these formats use 16 bytes per block
        bytesPerBlock = 16;
        break;
    }

    return (bytesPerBlock * blocks * layers);
}

bool TextureGLUtil::isIntegerInternalFormat(GLenum format)
{
    bool ok = false;
    switch (format)
    {
    // http://www.opengl.org/registry/specs/ARB/texture_rg.txt
    case GL_R8I:
    case GL_R8UI:
    case GL_R16I:
    case GL_R16UI:
    case GL_R32I:
    case GL_R32UI:
    case GL_RG8I:
    case GL_RG8UI:
    case GL_RG16I:
    case GL_RG16UI:
    case GL_RG32I:
    case GL_RG32UI:

    // http://www.opengl.org/registry/specs/EXT/texture_integer.txt
    case GL_RGBA32UI_EXT:
    case GL_RGB32UI_EXT:
    case GL_ALPHA32UI_EXT:
    case GL_INTENSITY32UI_EXT:
    case GL_LUMINANCE32UI_EXT:
    case GL_LUMINANCE_ALPHA32UI_EXT:

    case GL_RGBA16UI_EXT:
    case GL_RGB16UI_EXT:
    case GL_ALPHA16UI_EXT:
    case GL_INTENSITY16UI_EXT:
    case GL_LUMINANCE16UI_EXT:
    case GL_LUMINANCE_ALPHA16UI_EXT:

    case GL_RGBA8UI_EXT:
    case GL_RGB8UI_EXT:
    case GL_ALPHA8UI_EXT:
    case GL_INTENSITY8UI_EXT:
    case GL_LUMINANCE8UI_EXT:
    case GL_LUMINANCE_ALPHA8UI_EXT:

    case GL_RGBA32I_EXT:
    case GL_RGB32I_EXT:
    case GL_ALPHA32I_EXT:
    case GL_INTENSITY32I_EXT:
    case GL_LUMINANCE32I_EXT:
    case GL_LUMINANCE_ALPHA32I_EXT:

    case GL_RGBA16I_EXT:
    case GL_RGB16I_EXT:
    case GL_ALPHA16I_EXT:
    case GL_INTENSITY16I_EXT:
    case GL_LUMINANCE16I_EXT:
    case GL_LUMINANCE_ALPHA16I_EXT:

    case GL_RGBA8I_EXT:
    case GL_RGB8I_EXT:
    case GL_ALPHA8I_EXT:
    case GL_INTENSITY8I_EXT:
    case GL_LUMINANCE8I_EXT:
    case GL_LUMINANCE_ALPHA8I_EXT:
        ok = true;
        break;
    }
    return (ok);
}

ITextureGLFunction *TextureGLUtil::getTextureGLFunction()
{
    static TextureGLFunctionBind textureGLFuncBind;
    static TextureGLFunctionDSA textureGLFuncDSA;
    return GLEW_EXT_direct_state_access ? static_cast<ITextureGLFunction *>(&textureGLFuncDSA) : static_cast<ITextureGLFunction *>(&textureGLFuncBind);
}

unsigned int TextureGLUtil::getMipMapNumLevels(unsigned int w, unsigned int h, unsigned int d)
{
    unsigned int bits = std::max(w, std::max(h, d));
    unsigned int i = 1;
    while (bits >>= 1)
    {
        ++i;
    }
    return i;
}

bool TextureGLUtil::isCompressedFormat(GLenum format)
{
    bool ok = false;
    switch (format)
    {
    case GL_COMPRESSED_RG:
    case GL_COMPRESSED_RGB:
    case GL_COMPRESSED_RGBA:
    case GL_COMPRESSED_ALPHA:
    case GL_COMPRESSED_LUMINANCE:
    case GL_COMPRESSED_LUMINANCE_ALPHA:
    case GL_COMPRESSED_INTENSITY:
    case GL_COMPRESSED_SLUMINANCE:
    case GL_COMPRESSED_SLUMINANCE_ALPHA:
    case GL_COMPRESSED_SRGB:
    case GL_COMPRESSED_SRGB_ALPHA:

    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:

    case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:

    case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB:
    case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB:
    case GL_COMPRESSED_RGBA_BPTC_UNORM_ARB:
    case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB:

    case GL_COMPRESSED_RED_RGTC1:
    case GL_COMPRESSED_SIGNED_RED_RGTC1:
    case GL_COMPRESSED_RG_RGTC2:
    case GL_COMPRESSED_SIGNED_RG_RGTC2:

    case GL_COMPRESSED_LUMINANCE_LATC1_EXT:
    case GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT:
    case GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT:
    case GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT:
        ok = true;
        break;
    }
    return (ok);
}

GLsizei TextureGLUtil::getMipMapSize(GLsizei sz, GLuint level)
{
    sz = (sz >> level);
    return sz ? sz : 1;
}

TextureGL::TextureGL(GLenum target, GLenum internalFormat, GLenum format, GLenum type, GLsizei border)
    : target_(target), internalFormat_(internalFormat), pixelFormat_(format), dataType_(type), definedLevels_(0), maxLevel_(0)
{
    GLuint id;
    glGenTextures(1, &id);
    setGLId(id);

    GLenum filter = TextureGLUtil::isIntegerInternalFormat(internalFormat_) ? GL_NEAREST : GL_LINEAR;
    switch (target_)
    {
    case GL_TEXTURE_1D:
    case GL_TEXTURE_2D:
    case GL_TEXTURE_3D:
    case GL_TEXTURE_RECTANGLE:
    case GL_TEXTURE_1D_ARRAY:
    case GL_TEXTURE_2D_ARRAY:
    case GL_TEXTURE_CUBE_MAP:
    case GL_TEXTURE_CUBE_MAP_ARRAY:
        setFilterParameters(filter, filter);
        break;
    default:
        break;
    }
}

TextureGL::~TextureGL()
{
    if (getGLId())
    {
        GLuint id = getGLId();
        glDeleteTextures(1, &id);
    }
}

void TextureGL::bind() const
{
    glBindTexture(target_, getGLId());
}

void TextureGL::unbind() const
{
    glBindTexture(target_, 0);
}

void TextureGL::generateMipMap()
{
    assert(maxLevel_);

    TextureGLUtil::getTextureGLFunction()->generateMipMap(getGLId(), target_);
    // 111111
    definedLevels_ = (1 << (maxLevel_ + 1)) - 1;
}

void TextureGL::setBorderColor(float color[4])
{
    TextureGLUtil::getTextureGLFunction()->setParameter(getGLId(), target_, GL_TEXTURE_BORDER_COLOR, color);
}

void TextureGL::setCompareParameters(GLenum mode, GLenum func)
{
    TextureGLUtil::getTextureGLFunction()->setCompareParameters(getGLId(), target_, mode, func);
}

void TextureGL::setFilterParameters(GLenum minFilter, GLenum magFilter)
{
    TextureGLUtil::getTextureGLFunction()->setFilterParameters(getGLId(), target_, minFilter, magFilter);
}

void TextureGL::setPixelFormat(GLenum format)
{
    if (pixelFormat_ != format)
    {
        pixelFormat_ = format;
        definedLevels_ = 0;
    }
}

void TextureGL::setLODParameters(float minLOD, float maxLOD, float LODBias)
{
    // must not set lod parameters on a texture rectangle (invalid operation)
    if (target_ != GL_TEXTURE_RECTANGLE)
    {
        TextureGLUtil::getTextureGLFunction()->setLODParameters(getGLId(), target_, minLOD, maxLOD, LODBias);
    }
}

void TextureGL::setMaxAnisotropy(float anisotropy)
{
    TextureGLUtil::getTextureGLFunction()->setParameter(getGLId(), target_, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
}

void TextureGL::setDataType(GLenum type)
{
    if (dataType_ != type)
    {
        dataType_ = type;
        definedLevels_ = 0;
    }
}

void TextureGL::setWrapParameters(GLenum wrapS, GLenum wrapT, GLenum wrapR)
{
    TextureGLUtil::getTextureGLFunction()->setWrapParameters(getGLId(), target_, wrapS, wrapT, wrapR);
}

void TextureGL::addMipMapLevel(GLuint level)
{
    definedLevels_ |= (1 << level);
}

void TextureGL::resetMipMapLevels()
{
    definedLevels_ = 1;
}

void TextureGL::setMaxMipMapLevel(GLuint level)
{
    maxLevel_ = level;
}

std::shared_ptr<Texture1DGL> Texture1DGL::create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width)
{
    std::shared_ptr<Texture1DGL> p(new Texture1DGL(internalFormat, format, type, width));
    return p;
}

Texture1DGL::Texture1DGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width)
    : TextureGL(GL_TEXTURE_1D, internalFormat, format, type), width_(0)
{
    resize(width);
}

void Texture1DGL::resize(GLsizei width)
{
    if (width_ != width)
    {
        assert(width <= getMaximumSize());
        width_ = width;
        // clear
        TextureGLUtil::getTextureGLFunction()->setImage1D(getGLId(), getTarget(), 0, getInternalFormat(), width, 0, getPixelFormat(), getDataType(), nullptr);

        resetMipMapLevels();
        setMaxMipMapLevel(TextureGLUtil::getMipMapNumLevels(width_, 1, 1));
    }
}

void Texture1DGL::setData(const void *data, GLuint mipLevel /*= 0 */)
{
    // To do compressed texture
    assert(isMipMapLevelValid(mipLevel));

    auto update = isMipMapLevelDefined(mipLevel);
    auto width = TextureGLUtil::getMipMapSize(width_, mipLevel);
    // non-compressed texture
    if (!update)
        TextureGLUtil::getTextureGLFunction()->setImage1D(getGLId(), getTarget(), mipLevel, getInternalFormat(), width, 0, getPixelFormat(), getDataType(), data);
    else
    {
        unsigned int xOffset = 0;
        TextureGLUtil::getTextureGLFunction()->setSubImage1D(getGLId(), getTarget(), mipLevel, xOffset, width, getPixelFormat(), getDataType(), data);
    }

    addMipMapLevel(mipLevel);
}

void Texture1DGL::getData(void *data, GLuint mipLevel /*= 0 */) const
{
    assert(isMipMapLevelDefined(mipLevel));
    assert(data);
    TextureGLUtil::getTexData(this, getTarget(), data, mipLevel);
}

GLsizei Texture1DGL::getMaximumSize()
{
    GLsizei size;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
    return size;
}

std::shared_ptr<Texture1DArrayGL> Texture1DArrayGL::create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei numLayers)
{
    std::shared_ptr<Texture1DArrayGL> p(new Texture1DArrayGL(internalFormat, format, type, width, numLayers));
    return p;
}

Texture1DArrayGL::Texture1DArrayGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei numLayers) : TextureGL(GL_TEXTURE_1D_ARRAY, internalFormat, format, type),
                                                                                                                          width_(0),
                                                                                                                          numLayers_(0)
{
    resize(width, numLayers);
}

void Texture1DArrayGL::resize(GLsizei width, GLsizei numLayers)
{
    if (width_ != width || numLayers_ != numLayers)
    {
        assert(width <= getMaximumSize() && numLayers <= getMaximumLayers());
        width_ = width;
        numLayers_ = numLayers;

        TextureGLUtil::getTextureGLFunction()->setImage2D(getGLId(), getTarget(), 0, getInternalFormat(), width, numLayers, 0, getPixelFormat(), getDataType(), 0);

        resetMipMapLevels();
        setMaxMipMapLevel(TextureGLUtil::getMipMapNumLevels(getWidth(), 1, 1));
    }
}

void Texture1DArrayGL::setData(const void *data, GLint layer, GLuint mipLevel /*= 0 */)
{
    assert(isMipMapLevelValid(mipLevel));
    assert(layer < getNumLayers());

    auto update = isMipMapLevelDefined(mipLevel);
    auto width = TextureGLUtil::getMipMapSize(width_, mipLevel);
    if (!update)
    {
        // allocate memoery fo mipLevel
        TextureGLUtil::getTextureGLFunction()->setImage2D(getGLId(), getTarget(), mipLevel, getInternalFormat(), width, numLayers_, 0, getPixelFormat(), getDataType(), nullptr);
    }

    unsigned int xOffset = 0;
    unsigned int yOffset = layer;
    TextureGLUtil::getTextureGLFunction()->setSubImage2D(getGLId(), getTarget(), mipLevel, xOffset, yOffset, width, numLayers_, getPixelFormat(), getDataType(), data);

    addMipMapLevel(mipLevel);
}

std::shared_ptr<Texture2DGL> Texture2DGL::create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height)
{
    std::shared_ptr<Texture2DGL> p(new Texture2DGL(internalFormat, format, type, width, height));
    return p;
}

Texture2DGL::Texture2DGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height)
    : TextureGL(GL_TEXTURE_2D, internalFormat, format, type), width_(0), height_(0)
{
    resize(width, height);
}

void Texture2DGL::resize(GLsizei width, GLsizei height)
{
    if (width_ != width || height_ != height)
    {
        assert(width_ <= getMaximumSize() && height_ <= getMaximumSize());
        width_ = width;
        height_ = height;

        TextureGLUtil::getTextureGLFunction()->setImage2D(getGLId(), getTarget(), 0, getInternalFormat(), width, height, 0, getPixelFormat(), getDataType(), nullptr);

        resetMipMapLevels();
        setMaxMipMapLevel(TextureGLUtil::getMipMapNumLevels(getWidth(), getWidth(), 1));
    }
}

void Texture2DGL::setData(const void *data, GLuint mipLevel /*= 0 */)
{
    assert(isMipMapLevelValid(mipLevel));

    auto update = isMipMapLevelDefined(mipLevel);

    auto width = TextureGLUtil::getMipMapSize(width_, mipLevel);
    auto height = TextureGLUtil::getMipMapSize(height_, mipLevel);

    if (!update)
        TextureGLUtil::getTextureGLFunction()->setImage2D(getGLId(), getTarget(), mipLevel, getInternalFormat(), width, height, 0, getPixelFormat(), getDataType(), data);
    else
    {
        unsigned int xOffset = 0;
        unsigned int yOffset = 0;
        TextureGLUtil::getTextureGLFunction()->setSubImage2D(getGLId(), getTarget(), mipLevel, xOffset, yOffset, width, height, getPixelFormat(), getDataType(), data);
    }

    addMipMapLevel(mipLevel);
}

void Texture2DGL::getData(void *data, GLuint mipLevel) const
{
    assert(isMipMapLevelDefined(mipLevel));
    assert(data);
    TextureGLUtil::getTexData(this, getTarget(), data, mipLevel);
}

GLsizei Texture2DGL::getMaximumSize()
{
    GLsizei size;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
    return size;
}

std::shared_ptr<Texture2DArrayGL> Texture2DArrayGL::create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, GLsizei numLayers)
{
    std::shared_ptr<Texture2DArrayGL> p(new Texture2DArrayGL(internalFormat, format, type, width, height, numLayers));
    return p;
}

Texture2DArrayGL::Texture2DArrayGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, GLsizei numLayers)
    : TextureGL(GL_TEXTURE_2D_ARRAY, internalFormat, format, type), width_(0), height_(0), numLayers_(0)
{
    resize(width, height, numLayers);
}

void Texture2DArrayGL::resize(GLsizei width, GLsizei height, GLsizei numLayers)
{
    if (width != width || height_ != height || numLayers_ != numLayers)
    {
        assert(width <= getMaximumSize() && height <= getMaximumSize() && numLayers <= getMaximumLayers());
        width_ = width;
        height_ = height;
        numLayers_ = numLayers;

        TextureGLUtil::getTextureGLFunction()->setImage3D(getGLId(), getTarget(), 0, getInternalFormat(), width, height, numLayers_, 0, getPixelFormat(), getDataType(), 0);

        resetMipMapLevels();
        setMaxMipMapLevel(TextureGLUtil::getMipMapNumLevels(getWidth(), getWidth(), 1));
    }
}

void Texture2DArrayGL::setData(const void *data, GLint layer, GLuint mipLevel /*= 0 */)
{
    assert(isMipMapLevelValid(mipLevel));
    assert(layer < getLayers());

    auto update = isMipMapLevelDefined(mipLevel);

    auto width = TextureGLUtil::getMipMapSize(width_, mipLevel);
    auto height = TextureGLUtil::getMipMapSize(height_, mipLevel);

    if (!update)
        TextureGLUtil::getTextureGLFunction()->setImage3D(getGLId(), getTarget(), mipLevel, getInternalFormat(), width, height, numLayers_, 0, getPixelFormat(), getDataType(), nullptr);

    unsigned int xOffset = 0;
    unsigned int yOffset = 0;
    unsigned int zOffset = layer;
    TextureGLUtil::getTextureGLFunction()->setSubImage3D(getGLId(), getTarget(), mipLevel, xOffset, yOffset, zOffset, width, height, numLayers_, getPixelFormat(), getDataType(), data);

    addMipMapLevel(mipLevel);
}

void Texture2DArrayGL::getData(void *data, GLuint mipLevel) const
{
    assert(isMipMapLevelDefined(mipLevel));
    assert(data);
    TextureGLUtil::getTexData(this, getTarget(), data, mipLevel);
}

GLsizei Texture2DArrayGL::getMaximumSize()
{
    GLsizei size;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
    return size;
}

GLsizei Texture2DArrayGL::getMaximumLayers()
{
    GLsizei size;
    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS_EXT, &size);
    return size;
}

bool Texture2DArrayGL::isSupported()
{
    return GLEW_EXT_texture_array;
}

std::shared_ptr<Texture3DGL> Texture3DGL::create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, GLsizei depth)
{
    std::shared_ptr<Texture3DGL> p(new Texture3DGL(internalFormat, format, type, width, height, depth));
    return p;
}

Texture3DGL::Texture3DGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, GLsizei depth)
    : TextureGL(GL_TEXTURE_3D, internalFormat, format, type), width_(0), height_(0), depth_(0)
{
    resize(width, height, depth);
}

void Texture3DGL::resize(GLsizei width, GLsizei height, GLsizei depth)
{
    if (width_ != width || height_ != height || depth_ != depth)
    {
        assert(width <= getMaximumSize() && height <= getMaximumSize() && depth <= getMaximumSize());
        width_ = width;
        height_ = height;
        depth_ = depth;

        TextureGLUtil::getTextureGLFunction()->setImage3D(getGLId(), getTarget(), 0, getInternalFormat(), width, height, depth, 0, getPixelFormat(), getDataType(), 0);

        resetMipMapLevels();
        setMaxMipMapLevel(TextureGLUtil::getMipMapNumLevels(getWidth(), getWidth(), getDepth()));
    }
}

void Texture3DGL::setData(const void *data, GLuint mipLevel)
{
    assert(isMipMapLevelValid(mipLevel));

    auto update = isMipMapLevelDefined(mipLevel);

    auto width = TextureGLUtil::getMipMapSize(width_, mipLevel);
    auto height = TextureGLUtil::getMipMapSize(height_, mipLevel);
    auto depth = TextureGLUtil::getMipMapSize(depth_, mipLevel);

    if (!update)
        TextureGLUtil::getTextureGLFunction()->setImage3D(getGLId(), getTarget(), mipLevel, getInternalFormat(), width, height, depth, 0, getPixelFormat(), getDataType(), data);
    else
    {
        unsigned int xOffset = 0;
        unsigned int yOffset = 0;
        unsigned int zOffset = 0;
        TextureGLUtil::getTextureGLFunction()->setSubImage3D(getGLId(), getTarget(), mipLevel, xOffset, yOffset, zOffset, width, height, depth, getPixelFormat(), getDataType(), data);
    }

    addMipMapLevel(mipLevel);
}

void Texture3DGL::getData(void *data, GLuint mipLevel) const
{
    assert(isMipMapLevelDefined(mipLevel));
    assert(data);
    TextureGLUtil::getTexData(this, getTarget(), data, mipLevel);
}

GLsizei Texture3DGL::getMaximumSize()
{
    GLsizei size;
    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &size);
    return size;
}

std::shared_ptr<TextureCubeMapGL> TextureCubeMapGL::create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height)
{
    return (std::shared_ptr<TextureCubeMapGL>(new TextureCubeMapGL(internalFormat, format, type, width, height)));
}

TextureCubeMapGL::TextureCubeMapGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height)
    : TextureGL(GL_TEXTURE_CUBE_MAP, internalFormat, format, type), width_(0), height_(0)
{
    resize(width, height);
}

void TextureCubeMapGL::resize(GLsizei width, GLsizei height)
{
    if (width_ != width || height_ != height)
    {
        assert(width <= getMaximumSize());
        // cube map must equal
        assert(width == height);
        width_ = width;
        height_ = height;

        for (unsigned int face = 0; face < 6; ++face)
        {
            TextureGLUtil::getTextureGLFunction()->setImage2D(getGLId(), GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, getInternalFormat(), width, height, 0, getPixelFormat(), getDataType(), nullptr);
        }

        resetMipMapLevels();
        setMaxMipMapLevel(TextureGLUtil::getMipMapNumLevels(getWidth(), getWidth(), 1));
    }
}

void TextureCubeMapGL::setData(const void *data, int face, GLuint mipLevel)
{
    assert(0 <= face && face <= 6);
    assert(isMipMapLevelValid(mipLevel));

    auto update = isMipMapLevelDefined(mipLevel);

    auto width = TextureGLUtil::getMipMapSize(width_, mipLevel);
    auto height = TextureGLUtil::getMipMapSize(height_, mipLevel);

    if (!update)
    {
        // create 6 instead of 1.
        for (size_t f = 0; f < 6; f++)
        {
            auto target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + f;
            TextureGLUtil::getTextureGLFunction()->setImage2D(getGLId(), target, mipLevel, getInternalFormat(), width, height, 0, getPixelFormat(), getDataType(), nullptr);
        }
    }

    unsigned int xOffset = 0;
    unsigned int yOffset = 0;
    auto target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
    TextureGLUtil::getTextureGLFunction()->setSubImage2D(getGLId(), target, mipLevel, xOffset, yOffset, width, height, getPixelFormat(), getDataType(), data);
    addMipMapLevel(mipLevel);
}

void TextureCubeMapGL::getData(void *data, int face, GLuint mipLevel) const
{
    assert(0 <= face && face <= 6);
    assert(isMipMapLevelDefined(mipLevel));
    assert(data);
    TextureGLUtil::getTexData(this, GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, data, mipLevel);
}

GLsizei TextureCubeMapGL::getMaximumSize()
{
    GLsizei size;
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &size);
    return size;
}

std::shared_ptr<TextureBufferGL> TextureBufferGL::create(GLenum internalFormat, const std::shared_ptr<BufferGL> &buffer)
{
    return std::shared_ptr<TextureBufferGL>(new TextureBufferGL(internalFormat, buffer));
}

std::shared_ptr<TextureBufferGL> TextureBufferGL::create(GLenum internalFormat, unsigned int size, GLvoid const *data, GLenum usage)
{
    auto buffer = BufferGL::create(BufferGL::ModeCore::Core, usage, GL_TEXTURE_BUFFER);
    buffer->setSize(size);
    buffer->update(data, 0, size);
    return std::shared_ptr<TextureBufferGL>(new TextureBufferGL(internalFormat, buffer));
}

TextureBufferGL::TextureBufferGL(GLenum internalFormat, const std::shared_ptr<BufferGL> &buffer)
    : TextureGL(GL_TEXTURE_BUFFER, internalFormat, GL_INVALID_ENUM, GL_INVALID_ENUM)
{
    setBuffer(buffer);
}

TextureBufferGL::~TextureBufferGL()
{
}

void TextureBufferGL::setBuffer(const std::shared_ptr<BufferGL> &buffer)
{
    if (bufferShared_ != buffer)
    {
        bufferShared_ = buffer;
        TextureGLUtil::getTextureGLFunction()->attachBuffer(getGLId(), GL_TEXTURE_BUFFER, getInternalFormat(), bufferShared_ ? bufferShared_->getGLId() : 0);
    }
}

GLint TextureBufferGL::getMaximumSize()
{
    GLint size;
    glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE, &size);
    return (size);
}

bool TextureBufferGL::isSupported()
{
    return (!!GLEW_ARB_texture_buffer_object || !!GLEW_EXT_texture_buffer_object);
}