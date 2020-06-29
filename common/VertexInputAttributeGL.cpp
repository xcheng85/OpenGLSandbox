#include <assert.h>
#include <VertexInputAttributeGL.h>

using namespace OpenGLSandbox::Common;
using namespace OpenGLSandbox::Common::GL;

bool VertexInputAttributeGL::VertexInputAttributeDescriptionGL::operator==(const VertexInputAttributeGL::VertexInputAttributeDescriptionGL &rhs) const
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

VertexInputAttributeGL::VertexInputAttributeGL(const OpenGLSandbox::Common::VertexInputAttributeCreateInfo &desc)
{
    assert(desc.vertexInputAttributes.size() <= GL_MAX_ATTRIBUTES);
    for (const auto &via : desc.vertexInputAttributes)
    {
        auto &viaGL = vertexInputAttributeDescriptions_[via.bindingIndex];

        viaGL.enabled = true;
        viaGL.streamId = via.streamId;
        viaGL.dataType = via.dataType;
        viaGL.numComponents = via.numComponents;
        viaGL.offset = via.offset;
        viaGL.stride = via.stride;
        viaGL.normalized = via.normalized;
    }
}

std::unique_ptr<VertexInputAttributeGL>
VertexInputAttributeGL::create(const OpenGLSandbox::Common::VertexInputAttributeCreateInfo &desc)
{
    return std::make_unique<VertexInputAttributeGL>(desc);
}

size_t VertexInputAttributeGL::getSizeInByte(unsigned int vertexAttributeBindingIndex)
{
    assert(vertexAttributeBindingIndex < GL_MAX_ATTRIBUTES);
    size_t size = 0;
    auto &via = vertexInputAttributeDescriptions_[vertexAttributeBindingIndex];
    if (via.enabled)
    {
        size += getSizeOf(via.dataType) * via.numComponents;
    }

    return size;
}