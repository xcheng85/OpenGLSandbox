#include <assert.h>
#include <TextureGLFunctionDSA.h>

using namespace OpenGLSandbox::GLWrapper;

void TextureGLFunctionDSA::attachBuffer(GLuint texture, GLenum target, GLenum internalFormat, GLuint buffer)
{
    glTextureBufferEXT(texture, target, internalFormat, buffer);
}

void TextureGLFunctionDSA::generateMipMap(GLuint texture, GLenum target)
{
    glTextureParameteriEXT(texture, target, GL_TEXTURE_BASE_LEVEL, 0);
    glGenerateTextureMipmapEXT(texture, target);
}

void TextureGLFunctionDSA::getCompressedImage(GLuint texture, GLenum target, GLint lod, GLvoid *img)
{
    glGetCompressedTextureImageEXT(texture, target, lod, img);
}

void TextureGLFunctionDSA::getImage(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels)
{
    glGetTextureImageEXT(texture, target, level, format, type, pixels);
}

void TextureGLFunctionDSA::setCompareParameters(GLuint texture, GLenum target, GLenum mode, GLenum func)
{
    glTextureParameteriEXT(texture, target, GL_TEXTURE_COMPARE_MODE, mode);
    glTextureParameteriEXT(texture, target, GL_TEXTURE_COMPARE_FUNC, func);
}

void TextureGLFunctionDSA::setCompressedImage1D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLsizei imageSize, GLvoid const *data)
{
    glCompressedTextureImage1DEXT(texture, target, level, internalFormat, width, border, imageSize, data);
}

void TextureGLFunctionDSA::setCompressedImage2D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLvoid const *data)
{
    glCompressedTextureImage2DEXT(texture, target, level, internalFormat, width, height, border, imageSize, data);
}

void TextureGLFunctionDSA::setCompressedImage3D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLvoid const *data)
{
    glCompressedTextureImage3DEXT(texture, target, level, internalFormat, width, height, depth, border, imageSize, data);
}

void TextureGLFunctionDSA::setCompressedSubImage1D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLsizei width, GLenum format, GLsizei imageSize, GLvoid const *data)
{
    glCompressedTextureSubImage1DEXT(texture, target, level, xOffset, width, format, imageSize, data);
}

void TextureGLFunctionDSA::setCompressedSubImage2D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLvoid const *data)
{
    glCompressedTextureSubImage2DEXT(texture, target, level, xOffset, yOffset, width, height, format, imageSize, data);
}

void TextureGLFunctionDSA::setCompressedSubImage3D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLvoid const *data)
{
    glCompressedTextureSubImage3DEXT(texture, target, level, xOffset, yOffset, zOffset, width, height, depth, format, imageSize, data);
}

void TextureGLFunctionDSA::setFilterParameters(GLuint texture, GLenum target, GLenum minFilter, GLenum magFilter)
{
    glTextureParameteriEXT(texture, target, GL_TEXTURE_MIN_FILTER, minFilter);
    glTextureParameteriEXT(texture, target, GL_TEXTURE_MAG_FILTER, magFilter);
}

void TextureGLFunctionDSA::setImage1D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid const *pixels)
{
    //https://github.com/xcheng85/Guide-to-Modern-OpenGL-Functions
    glPushClientAttribDefaultEXT(GL_CLIENT_PIXEL_STORE_BIT);
    glTextureImage1DEXT(texture, target, level, internalFormat, width, 0, format, type, pixels);
    glPopClientAttrib();
    //glTextureStorage1D(texture, level, internalFormat, width);
}

void TextureGLFunctionDSA::setImage2D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid const *pixels)
{
    glPushClientAttribDefaultEXT(GL_CLIENT_PIXEL_STORE_BIT);
    glTextureImage2DEXT(texture, target, level, internalFormat, width, height, 0, format, type, pixels);
    glPopClientAttrib();
    //glTextureStorage2D(texture, level, internalFormat, width, height);
}

void TextureGLFunctionDSA::setImage3D(GLuint texture, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid const *pixels)
{
    glPushClientAttribDefaultEXT(GL_CLIENT_PIXEL_STORE_BIT);
    glTextureImage3DEXT(texture, target, level, internalFormat, width, height, depth, 0, format, type, pixels);
    glPopClientAttrib();
    //glTextureStorage3D(texture, numlevels, internalFormat, width, height, depth);
}

void TextureGLFunctionDSA::setLODParameters(GLuint texture, GLenum target, float minLOD, float maxLOD, float LODBias)
{
    glTextureParameterfEXT(texture, target, GL_TEXTURE_MIN_LOD, minLOD);
    glTextureParameterfEXT(texture, target, GL_TEXTURE_MAX_LOD, maxLOD);
    glTextureParameterfEXT(texture, target, GL_TEXTURE_LOD_BIAS, LODBias);
}

void TextureGLFunctionDSA::setParameter(GLuint texture, GLenum target, GLenum pname, GLint param)
{
    glTextureParameteriEXT(texture, target, pname, param);
}

void TextureGLFunctionDSA::setParameter(GLuint texture, GLenum target, GLenum pname, GLfloat param)
{
    glTextureParameterfEXT(texture, target, pname, param);
}

void TextureGLFunctionDSA::setParameter(GLuint texture, GLenum target, GLenum pname, GLfloat const *param)
{
    glTextureParameterfvEXT(texture, target, pname, param);
}

void TextureGLFunctionDSA::setParameter(GLuint texture, GLenum target, GLenum pname, GLint const *param)
{
    glTextureParameterIivEXT(texture, target, pname, param);
}

void TextureGLFunctionDSA::setParameter(GLuint texture, GLenum target, GLenum pname, GLuint const *param)
{
    glTextureParameterIuivEXT(texture, target, pname, param);
}

void TextureGLFunctionDSA::setSubImage1D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLsizei width, GLenum format, GLenum type, GLvoid const *pixels)
{
    glTextureSubImage1D(texture, level, xOffset, width, format, type, pixels);
}

void TextureGLFunctionDSA::setSubImage2D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid const *pixels)
{
    glTextureSubImage2D(texture, level, xOffset, yOffset, width, height, format, type, pixels);
}

void TextureGLFunctionDSA::setSubImage3D(GLuint texture, GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid const *pixels)
{
    glTextureSubImage3D(texture, level, xOffset, yOffset, zOffset, width, height, depth, format, type, pixels);
}

void TextureGLFunctionDSA::setWrapParameters(GLuint texture, GLenum target, GLenum wrapS, GLenum wrapT, GLenum wrapR)
{
    glTextureParameteriEXT(texture, target, GL_TEXTURE_WRAP_S, wrapS);
    glTextureParameteriEXT(texture, target, GL_TEXTURE_WRAP_T, wrapT);
    glTextureParameteriEXT(texture, target, GL_TEXTURE_WRAP_R, wrapR);
}