#pragma once

#include <string>

#include <vector>

#include <memory>

#include <Common.h>

#include <CommonGL.h>

#include "Renderer.h"

namespace OpenGLSandbox
{
    namespace Common
    {
        class RendererGL : public OpenGLSandbox::Common::Renderer
        {
        protected:
            RendererGL();

        public:
            virtual ~RendererGL() { ; };
            virtual void update();
            virtual void render(const std::string &groupId, const RenderOptions &renderOptions = RenderOptions());

            virtual std::unique_ptr<IVertexInputAttribute> createVertexInputAttribute(const VertexInputAttributeCreateInfo &desc);
            virtual std::unique_ptr<IBuffer> createBuffer(const BufferCreateInfo &desc);
            virtual std::unique_ptr<IVertexInputBinding> createVertexData(const VertexInputBindingCreateInfo &desc);
            virtual std::unique_ptr<IPipelineVertexInputState> createPipelineVertexInputState(const PipelineVertexInputStateCreateInfo &desc);

            virtual std::unique_ptr<IIndexBuffer> createIndexBuffer(const IndexBufferCreateInfo &desc);

             virtual std::unique_ptr<ITexture *> createTexture(const TextureCreateInfo &desc);
        };
    }; // namespace Common
};     // namespace OpenGLSandbox
