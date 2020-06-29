#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Common.h>
#include <CommonGL.h>

namespace OpenGLSandbox
{
    namespace Common
    {
        namespace GL
        {
            class VertexInputAttributeGL : public OpenGLSandbox::Common::IVertexInputAttribute
            {
            public:
                struct VertexInputAttributeDescriptionGL
                {
                    VertexInputAttributeDescriptionGL() : enabled(false),
                                                          streamId(0),
                                                          dataType(DataType::UNSIGNED_INT_8),
                                                          numComponents(0),
                                                          normalized(false),
                                                          offset(0),
                                                          stride(0)
                    {
                    }

                    bool operator==(const VertexInputAttributeDescriptionGL &rhs) const;

                    bool enabled;
                    unsigned int streamId;
                    DataType dataType;
                    unsigned int numComponents;
                    bool normalized;
                    unsigned int offset; // in this stream
                    unsigned int stride; // in this stream
                };

                VertexInputAttributeGL(const OpenGLSandbox::Common::VertexInputAttributeCreateInfo &desc);
                static std::unique_ptr<VertexInputAttributeGL> create(const OpenGLSandbox::Common::VertexInputAttributeCreateInfo &desc);
                virtual ~VertexInputAttributeGL(){

                };

                bool operator==(const VertexInputAttributeGL &rhs) const;

                size_t getSizeInByte(unsigned int vertexAttributeBindingIndex);

            private:
                VertexInputAttributeDescriptionGL vertexInputAttributeDescriptions_[GL_MAX_ATTRIBUTES];
            };
        }; // namespace GL
    };     // namespace Common
};         // namespace OpenGLSandbox
