#include <iostream>
#include <assert.h>

#include "RendererGL.h"
#include "VertexInputStateGL.h"
#include "BufferGL.h"
#include "VertexDataGL.h"

using namespace OpenGLSandbox::Common;
using namespace OpenGLSandbox::Common::GL;

RendererGL::RendererGL()
{
}

void RendererGL::update()
{
}

void RendererGL::render(const std::string &groupId, const RenderOptions &renderOptions)
{
}

std::unique_ptr<IVertexInputState> RendererGL::createVertexInputState(const VertexInputStateCreateInfo &desc)
{
    return VertexInputStateGL::create(desc);
}

std::unique_ptr<IBuffer> RendererGL::createBuffer(const BufferCreateInfo &desc)
{
    return BufferGL::create(desc);
}

std::unique_ptr<IVertexData> RendererGL::createVertexData(const VertexDataCreateInfo& desc)
{
    return VertexDataGL::create(desc);
}