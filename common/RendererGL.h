#pragma once

#include <string>

#include <vector>

#include <memory>

#include "Common.h"

#include "CommonGL.h"

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

            virtual std::unique_ptr<IVertexInputState> createVertexInputState(const VertexInputStateCreateInfo &desc);
            virtual std::unique_ptr<IBuffer> createBuffer(const BufferCreateInfo &desc);
            virtual std::unique_ptr<IVertexData> createVertexData(const VertexDataCreateInfo& desc);
        };
    }; // namespace Common
};     // namespace OpenGLSandbox
