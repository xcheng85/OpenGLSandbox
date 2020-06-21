#pragma once

#include "common.h"

#include <GL/glew.h>

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

        }; // namespace GL
    };     // namespace Common
};         // namespace OpenGLSandbox