#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Common.h"
#include "CommonGL.h"
#include <glWrapper/BufferGL.h>

namespace OpenGLSandbox
{
    namespace Common
    {
        namespace GL
        {
            class BufferGL : public OpenGLSandbox::Common::IBuffer
            {
            public:
                BufferGL(const OpenGLSandbox::Common::BufferCreateInfo &info);
                ~BufferGL();

                static std::unique_ptr<IBuffer> create(const OpenGLSandbox::Common::BufferCreateInfo &info);

                const OpenGLSandbox::GLWrapper::BufferGL *const getBuffer() const { buffer_.get(); };

                void setSize(size_t width, size_t height = 0, size_t depth = 0);
                void updateData(size_t offset, const void *data, size_t size);

                void *map(OpenGLSandbox::Common::AccessType accessType, size_t offset, size_t size);
                bool unmap();

            protected:
                

            private:
                std::unique_ptr<OpenGLSandbox::GLWrapper::BufferGL> buffer_;
                OpenGLSandbox::Common::BufferFormat format_;
                GLenum usageHint_;
                size_t width_;
                size_t height_;
                size_t depth_;
                OpenGLSandbox::Common::AccessType accessType_;
                bool managesData_;
            };
        }; // namespace GL
    };     // namespace Common
};         // namespace OpenGLSandbox
