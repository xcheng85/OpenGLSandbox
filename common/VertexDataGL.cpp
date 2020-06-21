#include <assert.h>

#include <VertexDataGL.h>

using namespace OpenGLSandbox::Common;
using namespace OpenGLSandbox::Common::GL;

VertexDataGL::VertexDataGL(const VertexDataCreateInfo &desc)
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

VertexDataGL::~VertexDataGL()
{
}

std::unique_ptr<IVertexData> VertexDataGL::create(const VertexDataCreateInfo &desc)
{
    return std::make_unique<VertexDataGL>(desc);
}