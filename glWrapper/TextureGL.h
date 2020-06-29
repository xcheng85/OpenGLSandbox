#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <glWrapper/ObjectGL.h>
#include <glWrapper/BufferGL.h>

namespace OpenGLSandbox
{
    namespace GLWrapper
    {
       // class ObjectGL;
        class TextureGL : public ObjectGL
        {
        public:
            virtual ~TextureGL();

            void bind() const;

            void unbind() const;

            void generateMipMap();

            inline GLenum getPixelFormat() const
            {
                return pixelFormat_;
            };

            inline GLenum getInternalFormat() const
            {
                return internalFormat_;
            };

            inline GLuint getMaxLevel() const
            {
                return maxLevel_;
            };

            inline GLenum getTarget() const
            {
                return target_;
            };

            inline GLenum getDataType() const
            {
                return dataType_;
            };

            inline bool isMipMapComplete() const
            {
                return ((1u << (maxLevel_ + 1u)) - 1u) == definedLevels_;
            };

            inline bool isMipMapLevelDefined(GLuint level) const
            {
                return (definedLevels_ & (1 << level)) == 1;
            }

            inline bool isMipMapLevelValid(GLuint level) const
            {
                return level < maxLevel_;
            }

            void setBorderColor(float color[4]);
            void setBorderColor(unsigned int color[4]);

            void setCompareParameters(GLenum mode, GLenum func);
            void setPixelFormat(GLenum format);

            void setFilterParameters(GLenum minFilter, GLenum magFilter);

            void setLODParameters(float minLOD, float maxLOD, float LODBias);
            void setMaxAnisotropy(float anisotropy);
            void setDataType(GLenum type);
            void setWrapParameters(GLenum wrapS, GLenum wrapT, GLenum wrapR);

        protected:
            TextureGL(GLenum target, GLenum internalFormat, GLenum format, GLenum type, GLsizei border = 0);
            void addMipMapLevel(GLuint level);
            void resetMipMapLevels();
            void setMaxMipMapLevel(GLuint level);

        private:
            GLenum target_;
            GLenum internalFormat_;
            GLenum pixelFormat_;
            GLenum dataType_;
            GLuint maxLevel_; // max mipmap level for the texture

            // 32 bit, each bit represet mip level
            GLbitfield definedLevels_;
        };

        class Texture1DGL : public TextureGL
        {
        public:
            // other class may reference
            static std::shared_ptr<Texture1DGL> create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width = 0);

            void setData(const void *data, GLuint mipLevel = 0);

            void getData(void *data, GLuint mipLevel = 0) const;

            void resize(GLsizei width);

            inline GLsizei getWidth() const
            {
                return width_;
            };

            static GLsizei getMaximumSize();

        protected:
            Texture1DGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width);

        private:
            GLsizei width_;
        };

        class Texture1DArrayGL : public TextureGL
        {
        public:
            static std::shared_ptr<Texture1DArrayGL> create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width = 0, GLsizei numLayers = 0);

            void setData(const void *data, GLint layer, GLuint mipLevel = 0);

            void getData(void *data, GLuint mipLevel = 0) const;

            void resize(GLsizei width, GLint numLayers);

            inline GLsizei getWidth() const
            {
                return width_;
            };

            inline GLsizei getNumLayers() const
            {
                return numLayers_;
            };

            static GLsizei getMaximumSize();

            static GLsizei getMaximumLayers();

            static bool isSupported();

        protected:
            Texture1DArrayGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei numLayers);

        private:
            GLsizei width_;
            GLsizei numLayers_;
        };

        class Texture2DGL : public TextureGL
        {
        public:
            static std::shared_ptr<Texture2DGL> create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width = 0, GLsizei height = 0);

            void setData(const void *data, GLuint mipLevel = 0);

            void getData(void *data, GLuint mipLevel = 0) const;

            void resize(GLsizei width, GLsizei height);

            inline GLsizei getWidth() const
            {
                return width_;
            };

            inline GLsizei getHeight() const
            {
                return height_;
            };

            static GLsizei getMaximumSize();

        protected:
            Texture2DGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height);

        private:
            int width_;
            int height_;
        };

        class Texture2DArrayGL : public TextureGL
        {
        public:
            static std::shared_ptr<Texture2DArrayGL> create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width = 0, GLsizei height = 0, GLsizei numLayers = 0);

            void setData(const void *data, GLint layer, GLuint mipLevel = 0);

            void getData(void *data, GLuint mipLevel = 0) const;

            void resize(GLsizei width, GLsizei height, GLsizei numLayers);

            inline GLsizei getWidth() const
            {
                return width_;
            };

            GLsizei getHeight() const
            {
                return height_;
            };

            GLsizei getLayers() const
            {
                return numLayers_;
            };

            static GLsizei getMaximumSize();

            static GLsizei getMaximumLayers();

            static bool isSupported();

        protected:
            Texture2DArrayGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, GLsizei layers);

        private:
            int width_;
            int height_;
            int numLayers_;
        };

        class Texture3DGL : public TextureGL
        {
        public:
            static std::shared_ptr<Texture3DGL> create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width = 0, GLsizei height = 0, GLsizei depth = 0);

            void setData(const void *data, GLuint mipLevel = 0);

            void getData(void *data, GLuint mipLevel = 0) const;

            void resize(GLsizei width, GLsizei height, GLsizei depth);

            inline GLsizei getWidth() const
            {
                return width_;
            };

            inline GLsizei getHeight() const
            {
                return height_;
            };

            inline GLsizei getDepth() const
            {
                return depth_;
            };

            static GLsizei getMaximumSize();

        protected:
            Texture3DGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, GLsizei depth);

        private:
            int width_;
            int height_;
            int depth_;
        };

        class TextureCubeMapGL : public TextureGL
        {
        public:
            static std::shared_ptr<TextureCubeMapGL> create(GLenum internalFormat, GLenum format, GLenum type, GLsizei width = 0, GLsizei height = 0);

            void setData(const void *data, int face, GLuint mipLevel = 0);

            void getData(void *data, int face, GLuint mipLevel = 0) const;

            void resize(GLsizei width, GLsizei height);

            inline GLsizei getWidth() const
            {
                return width_;
            };

            inline GLsizei getHeight() const
            {
                return height_;
            };

            static GLsizei getMaximumSize();

        protected:
            TextureCubeMapGL(GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height);

        private:
            int width_;
            int height_;
        };

        class TextureBufferGL : public TextureGL
        {
        public:
            //shared_ptr, does not have the ownership
            static std::shared_ptr<TextureBufferGL> create(GLenum internalFormat, const std::shared_ptr<BufferGL> &buffer);
            static std::shared_ptr<TextureBufferGL> create(GLenum internalFormat, unsigned int size = 0, GLvoid const *data = nullptr, GLenum usage = GL_DYNAMIC_COPY);
            virtual ~TextureBufferGL();

        public:
            const auto &getBuffer() const;
            void setBuffer(const std::shared_ptr<BufferGL> &buffer);

            static GLsizei getMaximumSize();
            static bool isSupported();

        protected:
            TextureBufferGL(GLenum internalFormat, const std::shared_ptr<BufferGL> &buffer);

        private:
            std::shared_ptr<BufferGL> bufferShared_;
        };

    }; // namespace GLWrapper
};     // namespace OpenGLSandbox
