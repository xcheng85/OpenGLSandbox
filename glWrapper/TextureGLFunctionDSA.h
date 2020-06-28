#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <ITextureGLFunction.h>

namespace OpenGLSandbox
{
    namespace GLWrapper
    {
        class TextureGLFunctionDSA : public OpenGLSandbox::GLWrapper::ITextureGLFunction
        {
        public:
            virtual void attachBuffer(GLuint texture, GLenum target, GLenum internalFormat, GLuint buffer);
            virtual void generateMipMap(GLuint texture, GLenum target);
            virtual void getCompressedImage(GLuint texture, GLenum target, GLint lod, GLvoid *img);
            virtual void getImage(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
            virtual void setCompareParameters(GLuint texture, GLenum target, GLenum mode, GLenum func);
            virtual void setCompressedImage1D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLsizei imageSize, GLvoid const *data);
            virtual void setCompressedImage2D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLvoid const *data);
            virtual void setCompressedImage3D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLvoid const *data);
            virtual void setCompressedSubImage1D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLsizei width, GLenum format, GLsizei imageSize, GLvoid const *data);
            virtual void setCompressedSubImage2D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLvoid const *data);
            virtual void setCompressedSubImage3D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLvoid const *data);
            virtual void setFilterParameters(GLuint texture, GLenum target, GLenum minFilter, GLenum magFilter);
            virtual void setImage1D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid const *pixels);
            virtual void setImage2D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid const *pixels);
            virtual void setImage3D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid const *pixels);
            virtual void setLODParameters(GLuint texture, GLenum target, float minLOD, float maxLOD, float LODBias);
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLint param);
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLfloat param);
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLfloat const *param);
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLint const *param);
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLuint const *param);
            virtual void setSubImage1D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLsizei width, GLenum format, GLenum type, GLvoid const *pixels);
            virtual void setSubImage2D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid const *pixels);
            virtual void setSubImage3D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid const *pixels);
            virtual void setWrapParameters(GLuint texture, GLenum target, GLenum wrapS, GLenum wrapT, GLenum wrapR);
        };
    }; // namespace GLWrapper
};     // namespace OpenGLSandbox
