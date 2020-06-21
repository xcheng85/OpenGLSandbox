#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Common.h"
#include "CommonGL.h"

namespace OpenGLSandbox
{
    namespace Common
    {
        namespace GL
        {
            class VertexInputStateGL : public OpenGLSandbox::Common::IVertexInputState
            {
            public:
                struct VertexInputAttributeGL
                {
                    VertexInputAttributeGL() : enabled(false),
                                               streamId(0),
                                               dataType(DataType::UNSIGNED_INT_8),
                                               numComponents(0),
                                               normalized(false),
                                               offset(0),
                                               stride(0)
                    {
                    }

                    bool operator==(const VertexInputAttributeGL &rhs) const;

                    bool enabled;
                    unsigned int streamId;
                    DataType dataType;
                    unsigned int numComponents;
                    bool normalized;
                    unsigned int offset; // in this stream
                    unsigned int stride; // in this stream
                };

                VertexInputStateGL(const OpenGLSandbox::Common::VertexInputStateCreateInfo &desc);
                static std::unique_ptr<VertexInputStateGL> create(const OpenGLSandbox::Common::VertexInputStateCreateInfo &desc);
                virtual ~VertexInputStateGL(){

                };

                bool operator==(const VertexInputStateGL &rhs) const;

                size_t getSizeInByte(unsigned int vertexAttributeBindingIndex);

            private:
                // max vertex attributes num may vary from api, should define it in common gl
                VertexInputAttributeGL vertexInputAttributes_[GL_MAX_ATTRIBUTES];
            };
        }; // namespace GL
    };     // namespace Common
};         // namespace OpenGLSandbox
