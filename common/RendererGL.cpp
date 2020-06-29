#include <iostream>
#include <assert.h>

#include <RendererGL.h>
#include <VertexInputAttributeGL.h>
#include <BufferGL.h>
#include <VertexInputBindingGL.h>
#include <PipelineVertexInputStateGL.h>

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

std::unique_ptr<IVertexInputAttribute> RendererGL::createVertexInputAttribute(const VertexInputAttributeCreateInfo &desc)
{
    return VertexInputAttributeGL::create(desc);
}

std::unique_ptr<IBuffer> RendererGL::createBuffer(const BufferCreateInfo &desc)
{
    return BufferGL::create(desc);
}

std::unique_ptr<IVertexInputBinding> RendererGL::createVertexData(const VertexInputBindingCreateInfo &desc)
{
    return VertexInputBindingGL::create(desc);
}

std::unique_ptr<IPipelineVertexInputState> RendererGL::createPipelineVertexInputState(const PipelineVertexInputStateCreateInfo &desc)
{
    return PipelineVertexInputStateGL::create(desc);
}

std::unique_ptr<IIndexBuffer> RendererGL::createIndexBuffer(const IndexBufferCreateInfo &desc)
{
}

std::unique_ptr<ITexture *> RendererGL::createTexture(const TextureCreateInfo &desc)
{
    
}