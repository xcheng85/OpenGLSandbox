#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Common.h>
#include <CommonGL.h>
#include <BufferGL.h>

namespace OpenGLSandbox
{
    namespace Common
    {
        namespace GL
        {
            class VertexInputBindingGL : public IVertexInputBinding
            {
            public:
                VertexInputBindingGL(const VertexInputBindingCreateInfo &desc);
                virtual ~VertexInputBindingGL();
                // nothing needed now
                static std::unique_ptr<IVertexInputBinding> create(const VertexInputBindingCreateInfo &desc);

            private:
                OpenGLSandbox::Common::GL::BufferGL *buffer_[GL_MAX_ATTRIBUTES];
                size_t offset_[GL_MAX_ATTRIBUTES];
                size_t numVertices_;
            };
        }; // namespace GL
    };     // namespace Common
};         // namespace OpenGLSandbox
