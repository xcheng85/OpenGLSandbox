#include <assert.h>

#include <BufferGL.h>

using namespace OpenGLSandbox::Common;
using namespace OpenGLSandbox::Common::GL;

BufferGL::BufferGL(const BufferCreateInfo &info) : format_(BufferFormat::UNKNOWN),
                                                   usageHint_(GL_STATIC_DRAW),
                                                   width_(0),
                                                   height_(0),
                                                   depth_(0),
                                                   accessType_(AccessType::NONE)
{
    if (info.type == BufferCreateInfoType::GL)
    {
        assert(dynamic_cast<const BufferCreateInfoGL *>(&info) != nullptr);
        const BufferCreateInfoGL &bd = static_cast<const BufferCreateInfoGL &>(info);
        usageHint_ = getGLUsage(bd.usageHint);
        auto t = OpenGLSandbox::GLWrapper::BufferGL::create(OpenGLSandbox::GLWrapper::BufferGL::ModeCore::Core, usageHint_);
        assert(buffer_);
        managesData_ = true;
    }
}

BufferGL::~BufferGL()
{
}

std::unique_ptr<IBuffer> BufferGL::create(const OpenGLSandbox::Common::BufferCreateInfo &info)
{
    return std::make_unique<BufferGL>(info);
}

void BufferGL::setSize(size_t width, size_t height, size_t depth)
{
    // make sure buffer is not mapped when doing resize
    assert(accessType_ == AccessType::NONE);

    width_ = width;
    height_ = height;
    depth_ = depth;

    // Calculate the size in bytes to verify later setData() calls.
    size_t size = width_;
    if (height_ > 1)
    {
        size *= height_;
        if (depth_ > 1)
        {
            size *= depth_;
        }
    }

    if (size != buffer_->getSize())
    {
        buffer_->setSize(size);
        //notify(Event(this, Event::Type::DATA_AND_SIZE_CHANGED)); // Data is undefined after glBufferData with nullptr.
    }
}

void BufferGL::updateData(size_t offset, const void *data, size_t size)
{
    assert(accessType_ == AccessType::NONE);
    assert(offset + size <= buffer_->getSize());
    assert(managesData_);

    buffer_->update(data, offset, size);
    //notify(Event(this, Event::Type::DATA_CHANGED));
}

void *BufferGL::map(AccessType accessType, size_t offset, size_t size)
{
    assert(buffer_->getGLId());
    assert(accessType_ == AccessType::NONE);
    accessType_ = accessType;
    return buffer_->map(getGLAccessBitField(accessType), offset, size);
}

bool BufferGL::unmap()
{
    assert(buffer_->getGLId());
    assert(accessType_ != AccessType::NONE);
    bool success = buffer_->unmap();
    accessType_ = AccessType::NONE;
    return success;
}
