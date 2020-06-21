#include <assert.h>
#include "VertexInputStateGL.h"

using namespace OpenGLSandbox::Common;
using namespace OpenGLSandbox::Common::GL;

bool VertexInputStateGL::VertexInputAttributeGL::operator==(const VertexInputStateGL::VertexInputAttributeGL &rhs) const
{
    if (enabled && rhs.enabled)
    {
        return (dataType == rhs.dataType) && (streamId == rhs.streamId) && (numComponents == rhs.numComponents) && (normalized == rhs.normalized) && (offset == rhs.offset) && (stride == rhs.stride);
    }
    else
    {
        return (enabled == rhs.enabled);
    }
}

VertexInputStateGL::VertexInputStateGL(const OpenGLSandbox::Common::VertexInputStateCreateInfo &desc)
{
    assert(desc.vertexInputAttributes.size() <= GL_MAX_ATTRIBUTES);
    for (const auto &via : desc.vertexInputAttributes)
    {
        auto &viaGL = vertexInputAttributes_[via.bindingIndex];

        viaGL.enabled = true;
        viaGL.streamId = via.streamId;
        viaGL.dataType = via.dataType;
        viaGL.numComponents = via.numComponents;
        viaGL.offset = via.offset;
        viaGL.stride = via.stride;
        viaGL.normalized = via.normalized;
    }
}

std::unique_ptr<VertexInputStateGL>
VertexInputStateGL::create(const OpenGLSandbox::Common::VertexInputStateCreateInfo &desc)
{
    return std::make_unique<VertexInputStateGL>(desc);
}

size_t VertexInputStateGL::getSizeInByte(unsigned int vertexAttributeBindingIndex)
{
    assert(vertexAttributeBindingIndex < GL_MAX_ATTRIBUTES);
    size_t size = 0;
    auto &via = vertexInputAttributes_[vertexAttributeBindingIndex];
    if (via.enabled)
    {
        size += getSizeOf(via.dataType) * via.numComponents;
    }

    return size;
}