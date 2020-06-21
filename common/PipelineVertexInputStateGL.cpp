#include <assert.h>
#include "PipelineVertexInputStateGL.h"

using namespace OpenGLSandbox::Common;
using namespace OpenGLSandbox::Common::GL;

PipelineVertexInputStateGL::PipelineVertexInputStateGL(const PipelineVertexInputStateCreateInfo &desc)
{
    vertexInputAttribute_ = dynamic_cast<VertexInputAttributeGL *>(desc.pVertexInputAttribute);
    vertexInputBinding_ = dynamic_cast<VertexInputBindingGL *>(desc.pVertexInputBinding);
}

PipelineVertexInputStateGL::~PipelineVertexInputStateGL()
{
}

std::unique_ptr<IPipelineVertexInputState> PipelineVertexInputStateGL::create(const PipelineVertexInputStateCreateInfo &desc)
{
    return std::make_unique<PipelineVertexInputStateGL>(desc);
}