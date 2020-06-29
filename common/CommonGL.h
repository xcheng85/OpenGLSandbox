#pragma once

#include <common.h>

#include <GL/glew.h>
//#include <glWrapper/TextureGL.h>

namespace OpenGLSandbox
{
    namespace Common
    {
        namespace GL
        {
            inline static const unsigned int GL_MAX_ATTRIBUTES = 16;
            enum class UsageHint
            {
                STREAM_DRAW,
                STREAM_READ,
                STREAM_COPY,
                STATIC_DRAW,
                STATIC_READ,
                STATIC_COPY,
                DYNAMIC_DRAW,
                DYNAMIC_READ,
                DYNAMIC_COPY
            };

            struct BufferCreateInfoGL : public OpenGLSandbox::Common::BufferCreateInfo
            {
                BufferCreateInfoGL(UsageHint usageHint) : OpenGLSandbox::Common::BufferCreateInfo(OpenGLSandbox::Common::BufferCreateInfoType::GL),
                                                          usageHint(usageHint)
                {
                }

                virtual ~BufferCreateInfoGL()
                {
                }

                UsageHint usageHint;
            };

            inline GLenum getGLUsage(UsageHint usageHint)
            {
                GLenum result = GL_STATIC_DRAW;

                switch (usageHint)
                {
                case UsageHint::STREAM_DRAW:
                    result = GL_STREAM_DRAW;
                    break;
                case UsageHint::STREAM_READ:
                    result = GL_STREAM_READ;
                    break;
                case UsageHint::STREAM_COPY:
                    result = GL_STREAM_COPY;
                    break;
                case UsageHint::STATIC_DRAW:
                    result = GL_STATIC_DRAW;
                    break;
                case UsageHint::STATIC_READ:
                    result = GL_STATIC_READ;
                    break;
                case UsageHint::STATIC_COPY:
                    result = GL_STATIC_COPY;
                    break;
                case UsageHint::DYNAMIC_DRAW:
                    result = GL_DYNAMIC_DRAW;
                    break;
                case UsageHint::DYNAMIC_READ:
                    result = GL_DYNAMIC_READ;
                    break;
                case UsageHint::DYNAMIC_COPY:
                    result = GL_DYNAMIC_COPY;
                    break;
                }
                return result;
            }

            inline GLbitfield getGLAccessBitField(AccessType access)
            {
                switch (access)
                {
                case AccessType::READ_ONLY:
                    return GL_MAP_READ_BIT;
                case AccessType::WRITE_ONLY:
                    return GL_MAP_WRITE_BIT;
                case AccessType::READ_WRITE:
                    return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
                default:
                    assert(false);
                    return 0;
                }
            }

            inline GLenum getGLPixelFormat(PixelFormat pixelFormat, GLenum internalFormat)
            {
                // handle integer formats differently
                switch (internalFormat)
                {
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
                case GL_RGB8I:
                case GL_RGB8UI:
                case GL_RGB16I:
                case GL_RGB16UI:
                case GL_RGB32I:
                case GL_RGB32UI:
                case GL_RGBA8I:
                case GL_RGBA8UI:
                case GL_RGBA16I:
                case GL_RGBA16UI:
                case GL_RGBA32I:
                case GL_RGBA32UI:
                    switch (pixelFormat)
                    {
                    case PixelFormat::R:
                        return GL_RED_INTEGER;
                    case PixelFormat::RG:
                        return GL_RG_INTEGER;
                    case PixelFormat::RGB:
                        return GL_RGB_INTEGER;
                    case PixelFormat::RGBA:
                        return GL_RGBA_INTEGER;
                    case PixelFormat::BGR:
                        return GL_BGR_INTEGER;
                    case PixelFormat::BGRA:
                        return GL_BGRA_INTEGER;
                    case PixelFormat::LUMINANCE:
                        return GL_LUMINANCE_INTEGER_EXT;
                    case PixelFormat::ALPHA:
                        return GL_ALPHA_INTEGER;
                    case PixelFormat::LUMINANCE_ALPHA:
                        return GL_LUMINANCE_ALPHA_INTEGER_EXT;
                    default:
                        assert(false);
                        return GL_FALSE;
                    }
                default:
                    switch (pixelFormat)
                    {
                    case PixelFormat::R:
                        return GL_RED;
                    case PixelFormat::RG:
                        return GL_RG;
                    case PixelFormat::RGB:
                        return GL_RGB;
                    case PixelFormat::RGBA:
                        return GL_RGBA;
                    case PixelFormat::BGR:
                        return GL_BGR;
                    case PixelFormat::BGRA:
                        return GL_BGRA;
                    case PixelFormat::LUMINANCE:
                        return GL_LUMINANCE;
                    case PixelFormat::ALPHA:
                        return GL_ALPHA;
                    case PixelFormat::LUMINANCE_ALPHA:
                        return GL_LUMINANCE_ALPHA;
                    case PixelFormat::DEPTH_COMPONENT:
                        return GL_DEPTH_COMPONENT;
                    case PixelFormat::DEPTH_STENCIL:
                        return GL_DEPTH_STENCIL;
                    default:
                        assert(false);
                        return GL_FALSE;
                    }
                }
            }

            inline GLenum getGLDataType(DataType dataType)
            {
                switch (dataType)
                {
                case DataType::UNSIGNED_INT_8:
                    return GL_UNSIGNED_BYTE;
                case DataType::UNSIGNED_INT_16:
                    return GL_UNSIGNED_SHORT;
                case DataType::UNSIGNED_INT_32:
                    return GL_UNSIGNED_INT;
                case DataType::INT_8:
                    return GL_BYTE;
                case DataType::INT_16:
                    return GL_SHORT;
                case DataType::INT_32:
                    return GL_INT;
                case DataType::FLOAT_16:
                    return GL_HALF_FLOAT;
                case DataType::FLOAT_32:
                    return GL_FLOAT;
                case DataType::FLOAT_64:
                    return GL_DOUBLE;
                default:
                    assert(false);
                    return GL_FALSE;
                };
            }
        }; // namespace GL
    };     // namespace Common
};         // namespace OpenGLSandbox