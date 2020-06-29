#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Common.h>
#include <CommonGL.h>

namespace OpenGLSandbox
{
    namespace GLWrapper
    {
        class TextureGL;
    }
}


namespace OpenGLSandbox
{
    namespace Common
    {
        namespace GL
        {
              class TextureDataGLTexture : public OpenGLSandbox::Common::TextureData
            {
            public:
                TextureDataGLTexture(const std::shared_ptr<OpenGLSandbox::GLWrapper::TextureGL> &texture)
                    : TextureData(TextureDataType::NATIVE), texture_(texture)
                {
                }
                inline auto getSharedTexture() const
                {
                    return texture_;
                }

            private:
                std::shared_ptr<OpenGLSandbox::GLWrapper::TextureGL> texture_;
            };

            class TextureGL : public ITexture
            {
            public:
                virtual ~TextureGL();
                // allocate memory for texture
                static std::unique_ptr<ITexture> create(const TextureCreateInfo &desc);
                // upload data, different type may have different behaviour, especially textureBuffer
                virtual bool setData(const TextureData &textureData);

                const OpenGLSandbox::GLWrapper::TextureGL *const getTexture() const { texture_.get(); };

            protected:
                // some shared operation in constructor only depends on, this signature is better than 
                TextureGL(const std::shared_ptr<OpenGLSandbox::GLWrapper::TextureGL>& texture, bool useMipmap);
                // every texture type has different implementation
                virtual void upload(unsigned int mipMapLevel, unsigned int layer, const void *ptr);

                void setTexture( const std::shared_ptr<OpenGLSandbox::GLWrapper::TextureGL>& texture );

            private:
                // this class may/may not have the ownership of texture_; look at setTexture
                std::shared_ptr<OpenGLSandbox::GLWrapper::TextureGL> texture_;
                bool useMipmaps_;
            };

            class Texture1DGL : public TextureGL
            {
            public:
                static std::unique_ptr<ITexture> create(const TextureCreateInfo &desc);

            protected:
                Texture1DGL(const TextureCreateInfo &textureDescription);

                virtual void upload(unsigned int mipMapLevel, unsigned int layer, const void *ptr);
            };

            class Texture1DArrayGL : public TextureGL
            {
            public:
                static std::unique_ptr<ITexture> create(const TextureCreateInfo &desc);

            protected:
                Texture1DArrayGL(const TextureCreateInfo &textureDescription);

                virtual void upload(unsigned int mipMapLevel, unsigned int layer, const void *ptr);
            };

            class Texture2DGL : public TextureGL
            {
            public:
                static std::unique_ptr<ITexture> create(const TextureCreateInfo &desc);

            protected:
                Texture2DGL(const TextureCreateInfo &textureDescription);

                virtual void upload(unsigned int mipMapLevel, unsigned int layer, const void *ptr);
            };

            class Texture2DArrayGL : public TextureGL
            {
            public:
                static std::unique_ptr<ITexture> create(const TextureCreateInfo &desc);

            protected:
                Texture2DArrayGL(const TextureCreateInfo &textureDescription);

                virtual void upload(unsigned int mipMapLevel, unsigned int layer, const void *ptr);
            };

            class Texture3DGL : public TextureGL
            {
            public:
                static std::unique_ptr<ITexture> create(const TextureCreateInfo &desc);

            protected:
                Texture3DGL(const TextureCreateInfo &textureDescription);

                virtual void upload(unsigned int mipMapLevel, unsigned int layer, const void *ptr);
            };

            class TextureBufferGL : public TextureGL
            {
            public:
                static std::unique_ptr<ITexture> create(const TextureCreateInfo &desc);
                virtual bool setData(const TextureData &textureData);

            protected:
                TextureBufferGL(const TextureCreateInfo &textureDescription);

                virtual void upload(unsigned int mipMapLevel, unsigned int layer, const void *ptr);
            };

            class TextureCubeMapGL : public TextureGL
            {
            public:
                static std::unique_ptr<ITexture> create(const TextureCreateInfo &desc);
                virtual bool setData(const TextureData &textureData);

            protected:
                TextureCubeMapGL(const TextureCreateInfo &textureDescription);

                virtual void upload(unsigned int mipMapLevel, unsigned int layer, const void *ptr);
            };
        }; // namespace GL
    };     // namespace Common
};         // namespace OpenGLSandbox
