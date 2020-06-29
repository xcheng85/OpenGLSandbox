#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Common.h>
#include <CommonGL.h>
#include <VertexInputBindingGL.h>
#include <VertexInputAttributeGL.h>

namespace OpenGLSandbox
{
    namespace Common
    {
        namespace GL
        {
            class PipelineVertexInputStateGL : public IPipelineVertexInputState
            {
            public:
                PipelineVertexInputStateGL(const PipelineVertexInputStateCreateInfo &desc);
                virtual ~PipelineVertexInputStateGL();
                // nothing needed now
                static std::unique_ptr<IPipelineVertexInputState> create(const PipelineVertexInputStateCreateInfo &desc);

            private:
                VertexInputBindingGL* vertexInputBinding_;
                VertexInputAttributeGL* vertexInputAttribute_;
            };
        }; // namespace GL
    };     // namespace Common
};         // namespace OpenGLSandbox
