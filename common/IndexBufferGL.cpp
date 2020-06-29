#include <assert.h>
#include <IndexBufferGL.h>
#include <BufferGL.h>

using namespace OpenGLSandbox::Common;
using namespace OpenGLSandbox::Common::GL;

IndexBufferGL::IndexBufferGL(const IndexBufferCreateInfo &desc)
{
    indexType_ = desc.indexType;
    pBuffer_ = dynamic_cast<BufferGL*>(desc.buffer);
    assert(pBuffer_);
    offset_ = desc.offset;
    count_ = desc.count;
}

IndexBufferGL::~IndexBufferGL()
{
}

std::unique_ptr<IIndexBuffer> IndexBufferGL::create(const IndexBufferCreateInfo &desc)
{
    return std::make_unique<IndexBufferGL>(desc);
}