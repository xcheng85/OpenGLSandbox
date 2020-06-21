#include <assert.h>

#include <VertexInputBindingGL.h>

using namespace OpenGLSandbox::Common;
using namespace OpenGLSandbox::Common::GL;

VertexInputBindingGL::VertexInputBindingGL(const VertexInputBindingCreateInfo &desc)
{
    numVertices_ = desc.numVertices;

    for (const auto &bufferDesc : desc.bufferDescs)
    {
        const auto binding = std::get<0>(bufferDesc);
        assert(binding < GL_MAX_ATTRIBUTES);

        auto bufferGL = dynamic_cast<BufferGL*>(std::get<1>(bufferDesc));
        assert(bufferGL);

        buffer_[binding] = bufferGL;
        offset_[binding] = std::get<2>(bufferDesc);
    }
}

VertexInputBindingGL::~VertexInputBindingGL()
{
}

std::unique_ptr<IVertexInputBinding> VertexInputBindingGL::create(const VertexInputBindingCreateInfo &desc)
{
    return std::make_unique<VertexInputBindingGL>(desc);
}