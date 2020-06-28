#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <memory>
#include <GL/glew.h>

namespace OpenGLSandbox
{
    namespace GLWrapper
    {
        class ITextureGLFunction
        {
        public:
            virtual void attachBuffer(GLuint texture, GLenum target, GLenum internalFormat, GLuint buffer) = 0;
            virtual void generateMipMap(GLuint texture, GLenum target) = 0;
            virtual void getCompressedImage(GLuint texture, GLenum target, GLint lod, GLvoid *img) = 0;
            virtual void getImage(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels) = 0;
            virtual void setCompareParameters(GLuint texture, GLenum target, GLenum mode, GLenum func) = 0;
            virtual void setCompressedImage1D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLsizei imageSize, GLvoid const *data) = 0;
            virtual void setCompressedImage2D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLvoid const *data) = 0;
            virtual void setCompressedImage3D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLvoid const *data) = 0;
            virtual void setCompressedSubImage1D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLsizei width, GLenum format, GLsizei imageSize, GLvoid const *data) = 0;
            virtual void setCompressedSubImage2D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLvoid const *data) = 0;
            virtual void setCompressedSubImage3D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLvoid const *data) = 0;
            virtual void setFilterParameters(GLuint texture, GLenum target, GLenum minFilter, GLenum magFilter) = 0;
            virtual void setImage1D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid const *pixels) = 0;
            virtual void setImage2D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid const *pixels) = 0;
            virtual void setImage3D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid const *pixels) = 0;
            virtual void setLODParameters(GLuint texture, GLenum target, float minLOD, float maxLOD, float LODBias) = 0;
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLint param) = 0;
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLfloat param) = 0;
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLfloat const *param) = 0;
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLint const *param) = 0;
            virtual void setParameter(GLuint texture, GLenum target, GLenum pname, GLuint const *param) = 0;
            virtual void setSubImage1D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLsizei width, GLenum format, GLenum type, GLvoid const *pixels) = 0;
            virtual void setSubImage2D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid const *pixels) = 0;
            virtual void setSubImage3D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid const *pixels) = 0;
            virtual void setWrapParameters(GLuint texture, GLenum target, GLenum wrapS, GLenum wrapT, GLenum wrapR) = 0;
        };
    }; // namespace GLWrapper
};     // namespace OpenGLSandbox
