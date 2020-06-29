#include <assert.h>
#include <TextureGLFunctionBind.h>

using namespace OpenGLSandbox::GLWrapper;

GLenum TextureGLFunctionBind::TextureBinding::getBindingTarget(GLenum target)
{
    switch (target)
    {
    case GL_TEXTURE_1D:
        return (GL_TEXTURE_BINDING_1D);
    case GL_TEXTURE_1D_ARRAY:
        return (GL_TEXTURE_BINDING_1D_ARRAY);
    case GL_TEXTURE_2D:
        return (GL_TEXTURE_BINDING_2D);
    case GL_TEXTURE_2D_ARRAY:
        return (GL_TEXTURE_BINDING_2D_ARRAY);
    case GL_TEXTURE_2D_MULTISAMPLE:
        return (GL_TEXTURE_BINDING_2D_MULTISAMPLE);
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
        return (GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY);
    case GL_TEXTURE_3D:
        return (GL_TEXTURE_BINDING_3D);
    case GL_TEXTURE_BUFFER:
        return (GL_TEXTURE_BINDING_BUFFER);
    case GL_TEXTURE_CUBE_MAP:
        return (GL_TEXTURE_BINDING_CUBE_MAP);
    case GL_TEXTURE_CUBE_MAP_ARRAY:
        return (GL_TEXTURE_BINDING_CUBE_MAP_ARRAY);
    case GL_TEXTURE_RECTANGLE:
        return (GL_TEXTURE_BINDING_RECTANGLE);
    default:
        assert(false);
        return (GL_INVALID_ENUM);
    }
}

GLenum TextureGLFunctionBind::TextureBinding::getBindingBaseTarget(GLenum target)
{
    switch (target)
    {
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        return (GL_TEXTURE_CUBE_MAP);
    default:
        return target;
    }
}

TextureGLFunctionBind::TextureBinding::TextureBinding(GLenum target, GLuint texture)
{
    target_ = getBindingBaseTarget(target);
    glGetIntegerv(getBindingTarget(target), &oldBinding_);
    glBindTexture(target_, texture);
}

TextureGLFunctionBind::TextureBinding::~TextureBinding()
{
    glBindTexture(target_, oldBinding_);
}

void TextureGLFunctionBind::attachBuffer(GLuint texture, GLenum target, GLenum internalFormat, GLuint buffer)
{
    TextureBinding textureBinding(target, texture);
    glTexBuffer(target, internalFormat, buffer);
}

void TextureGLFunctionBind::generateMipMap(GLuint texture, GLenum target)
{
    TextureBinding textureBinding(target, texture);
    glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
    glGenerateMipmap(target);
}

void TextureGLFunctionBind::getCompressedImage(GLuint texture, GLenum target, GLint lod, GLvoid *img)
{
    TextureBinding textureBinding(target, texture);
    glGetCompressedTexImage(target, lod, img);
}

void TextureGLFunctionBind::getImage(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels)
{
    TextureBinding textureBinding(target, texture);
    glGetTexImage(target, level, format, type, pixels);
}

void TextureGLFunctionBind::setCompareParameters(GLuint texture, GLenum target, GLenum mode, GLenum func)
{
    TextureBinding textureBinding(target, texture);
    glTexParameteri(target, GL_TEXTURE_COMPARE_MODE, mode);
    glTexParameteri(target, GL_TEXTURE_COMPARE_FUNC, func);
}

void TextureGLFunctionBind::setCompressedImage1D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLsizei imageSize, GLvoid const *data)
{
    TextureBinding tb(target, texture);
    glCompressedTexImage1D(target, level, internalFormat, width, border, imageSize, data);
}

void TextureGLFunctionBind::setCompressedImage2D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLvoid const *data)
{
    TextureBinding tb(target, texture);
    glCompressedTexImage2D(target, level, internalFormat, width, height, border, imageSize, data);
}

void TextureGLFunctionBind::setCompressedImage3D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLvoid const *data)
{
    TextureBinding tb(target, texture);
    glCompressedTexImage3D(target, level, internalFormat, width, height, depth, border, imageSize, data);
}

void TextureGLFunctionBind::setCompressedSubImage1D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLsizei width, GLenum format, GLsizei imageSize, GLvoid const *data)
{
    TextureBinding tb(target, texture);
    glCompressedTexSubImage1D(target, level, xOffset, width, format, imageSize, data);
}

void TextureGLFunctionBind::setCompressedSubImage2D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLvoid const *data)
{
    TextureBinding tb(target, texture);
    glCompressedTexSubImage2D(target, level, xOffset, yOffset, width, height, format, imageSize, data);
}

void TextureGLFunctionBind::setCompressedSubImage3D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLvoid const *data)
{
    TextureBinding tb(target, texture);
    glCompressedTexSubImage3D(target, level, xOffset, yOffset, zOffset, width, height, depth, format, imageSize, data);
}

void TextureGLFunctionBind::setFilterParameters(GLuint texture, GLenum target, GLenum minFilter, GLenum magFilter)
{
    TextureBinding tb(target, texture);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
}

void TextureGLFunctionBind::setImage1D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid const *pixels)
{
    //http://www.songho.ca/opengl/gl_pbo.html
    TextureBinding tb(target, texture);
    //http://www.songho.ca/opengl/gl_pbo.html
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0); // make sure, GL_PIXEL_UNPACK_BUFFER is unbound !
    glTexImage1D(target, level, internalFormat, width, border, format, type, pixels);
}

void TextureGLFunctionBind::setImage2D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid const *pixels)
{
    TextureBinding tb(target, texture);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0); // make sure, GL_PIXEL_UNPACK_BUFFER is unbound !
    glTexImage2D(target, level, internalFormat, width, height, 0, format, type, pixels);
}

void TextureGLFunctionBind::setImage3D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid const *pixels)
{
    TextureBinding tb(target, texture);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0); // make sure, GL_PIXEL_UNPACK_BUFFER is unbound !
    glTexImage3D(target, level, internalFormat, width, height, depth, 0, format, type, pixels);
}

void TextureGLFunctionBind::setLODParameters(GLuint texture, GLenum target, float minLOD, float maxLOD, float LODBias)
{
    TextureBinding tb(target, texture);
    glTexParameterf(target, GL_TEXTURE_MIN_LOD, minLOD);
    glTexParameterf(target, GL_TEXTURE_MAX_LOD, maxLOD);
    glTexParameterf(target, GL_TEXTURE_LOD_BIAS, LODBias);
}

void TextureGLFunctionBind::setParameter(GLuint texture, GLenum target, GLenum pname, GLint param)
{
    TextureBinding tb(target, texture);
    glTexParameteri(target, pname, param);
}

void TextureGLFunctionBind::setParameter(GLuint texture, GLenum target, GLenum pname, GLfloat param)
{
    TextureBinding tb(target, texture);
    glTexParameterf(target, pname, param);
}

void TextureGLFunctionBind::setParameter(GLuint texture, GLenum target, GLenum pname, GLfloat const *param)
{
    TextureBinding tb(target, texture);
    glTexParameterfv(target, pname, param);
}

void TextureGLFunctionBind::setParameter(GLuint texture, GLenum target, GLenum pname, GLint const *param)
{
    TextureBinding tb(target, texture);
    glTexParameterIiv(target, pname, param);
}

void TextureGLFunctionBind::setParameter(GLuint texture, GLenum target, GLenum pname, GLuint const *param)
{
    TextureBinding tb(target, texture);
    glTexParameterIuiv(target, pname, param);
}

void TextureGLFunctionBind::setSubImage1D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLsizei width, GLenum format, GLenum type, GLvoid const *pixels)
{
    TextureBinding tb(target, texture);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0); // make sure, GL_PIXEL_UNPACK_BUFFER is unbound !
    glTexSubImage1D(target, level, xOffset, width, format, type, pixels);
}

void TextureGLFunctionBind::setSubImage2D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid const *pixels)
{
    TextureBinding tb(target, texture);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0); // make sure, GL_PIXEL_UNPACK_BUFFER is unbound !
    glTexSubImage2D(target, level, xOffset, yOffset, width, height, format, type, pixels);
}

void TextureGLFunctionBind::setSubImage3D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid const *pixels)
{
    TextureBinding tb(target, texture);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0); // make sure, GL_PIXEL_UNPACK_BUFFER is unbound !
    glTexSubImage3D(target, level, xOffset, yOffset, zOffset, width, height, depth, format, type, pixels);
}

void TextureGLFunctionBind::setWrapParameters(GLuint texture, GLenum target, GLenum wrapS, GLenum wrapT, GLenum wrapR)
{
    TextureBinding tb(target, texture);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(target, GL_TEXTURE_WRAP_R, wrapR);
}