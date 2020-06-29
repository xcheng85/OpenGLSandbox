#pragma once

#include <string>
#include <vector>
#include <memory>
#include <Common.h>
#include <CommonGL.h>

namespace OpenGLSandbox
{
    namespace Common
    {
        namespace GL
        {
            class BufferGL;
            class IndexBufferGL : public IIndexBuffer
            {
            public:
                IndexBufferGL(const IndexBufferCreateInfo &desc);
                virtual ~IndexBufferGL();
                static std::unique_ptr<IIndexBuffer> create(const IndexBufferCreateInfo &desc);

            private:
                DataType indexType_; // vkIndexType
                BufferGL *pBuffer_;
                size_t offset_;
                size_t count_;
            };
        }; // namespace GL
    };     // namespace Common
};         // namespace OpenGLSandbox
