#include <assert.h>
#include <BufferGL.h>

using namespace OpenGLSandbox::GLWrapper;

// no need to expose.
class BufferGLCore : public BufferGL
{
public:
    BufferGLCore(GLenum usage, GLenum defaultTarget);
    virtual ~BufferGLCore();

    virtual void update(void const *data, size_t offset, size_t size);
    virtual void *map(GLbitfield access, size_t offset, size_t length);
    virtual GLboolean unmap();
    virtual void setSize(size_t size);
    virtual void invalidate();
    virtual void makeResident();
    virtual void makeNonResident();

private:
    GLenum target_;
    GLenum usage_;
};

BufferGLCore::BufferGLCore(GLenum usage, GLenum defaultTarget)
    : target_(defaultTarget), usage_(usage)
{
    glGenBuffers(1, &id_);
}

BufferGLCore::~BufferGLCore()
{
    if (address_)
    {
        makeNonResident();
    }

    if (mappedAddress_)
    {
        unmap();
    }

    if (id_)
    {
        glDeleteBuffers(1, &id_);
    }
}

inline void checkAndUpdateRange(size_t offset, size_t &length, size_t maxLength)
{
    if (length > 0)
    {
        if (offset + length > maxLength)
        {
            throw std::runtime_error("offset + size out of range");
        }

        if (offset >= maxLength)
        {
            throw std::runtime_error("offset out of range");
        }
    }
}

void BufferGLCore::update(void const *data, size_t offset, size_t length)
{
    checkAndUpdateRange(offset, length, size_);

    if (length)
    {
        glBindBuffer(target_, id_);
        glBufferSubData(target_, offset, length, data);
    }
}

void *BufferGLCore::map(GLbitfield access, size_t offset, size_t length)
{
    checkAndUpdateRange(offset, length, size_);
    if (mappedAddress_)
    {
        throw std::runtime_error("Buffer is already mapped");
    }

    if (size_)
    {
        glBindBuffer(target_, id_);
        mappedAddress_ = glMapBufferRange(target_, offset, length, access);
    }
    else
    {
        mappedAddress_ = nullptr;
    }

    return mappedAddress_;
}

GLboolean BufferGLCore::unmap()
{
    if (!mappedAddress_)
    {
        throw std::runtime_error("Buffer is not mapped");
    }

    if (mappedAddress_ != nullptr)
    {
        mappedAddress_ = nullptr;
        glBindBuffer(target_, id_);
        return glUnmapBuffer(target_);
    }
    else
    {
        mappedAddress_ = 0;
        return GL_TRUE;
    }
}

void BufferGLCore::setSize(size_t size)
{
    if (size_ != size)
    {
        glBindBuffer(target_, id_);
        glBufferData(target_, size, nullptr, usage_);
        size_ = size;
    }
}

void BufferGLCore::invalidate()
{
    if (size_)
    {
        glInvalidateBufferData(id_);
    }
}

void BufferGLCore::makeResident()
{
    if (address_)
    {
        throw std::runtime_error("buffer is already resident");
    }

    if (size_)
    {
        glBindBuffer(target_, id_);
        glGetBufferParameterui64vNV(target_, GL_BUFFER_GPU_ADDRESS_NV, &address_);
        glMakeBufferResidentNV(target_, GL_READ_ONLY);
    }
    else
    {
        // ~0 is specifed as pointer to buffers with size 0
        address_ = 0;
    }
}

void BufferGLCore::makeNonResident()
{
    if (!address_)
    {
        throw std::runtime_error("buffer is not resident");
    }

    if (address_ != 0)
    {
        glBindBuffer(target_, id_);
        glMakeBufferNonResidentNV(target_);
    }
    address_ = 0;
}

#if defined(GL_VERSION_4_5)
// Direct Storage Access
class BufferGLCoreDSA : public BufferGL
{
public:
    BufferGLCoreDSA(GLenum usage);
    virtual ~BufferGLCoreDSA();

    virtual void update(void const *data, size_t offset, size_t size);
    virtual void *map(GLbitfield access, size_t offset, size_t length);
    virtual GLboolean unmap();
    virtual void setSize(size_t size);
    virtual void invalidate();
    virtual void makeResident();
    virtual void makeNonResident();

private:
    GLenum usage_;
};

BufferGLCoreDSA::BufferGLCoreDSA(GLenum usage)
    : usage_(usage)
{
    glCreateBuffers(1, &id_);
}

BufferGLCoreDSA::~BufferGLCoreDSA()
{
    if (address_)
    {
        makeNonResident();
    }

    if (mappedAddress_)
    {
        unmap();
    }

    if (id_)
    {
        glDeleteBuffers(1, &id_);
    }
}

void BufferGLCoreDSA::update(void const *data, size_t offset, size_t length)
{
    checkAndUpdateRange(offset, length, size_);

    glNamedBufferSubData(id_, offset, length, data);
}

void *BufferGLCoreDSA::map(GLbitfield access, size_t offset, size_t length)
{
    checkAndUpdateRange(offset, length, size_);
    if (mappedAddress_)
    {
        throw std::runtime_error("Buffer is already mapped");
    }

    if (size_)
    {
        mappedAddress_ = glMapNamedBufferRange(id_, offset, length, access);
    }
    else
    {
        mappedAddress_ = nullptr;
    }

    return mappedAddress_;
}

GLboolean BufferGLCoreDSA::unmap()
{
    if (!mappedAddress_)
    {
        throw std::runtime_error("Buffer is not mapped");
    }

    if (mappedAddress_ != nullptr)
    {
        mappedAddress_ = nullptr;
        return glUnmapNamedBuffer(id_);
    }
    else
    {
        return GL_TRUE;
    }
}

void BufferGLCoreDSA::setSize(size_t size)
{
    if (size_ != size)
    {
        glNamedBufferData(id_, size, nullptr, usage_);
        size_ = size;
    }
}

void BufferGLCoreDSA::invalidate()
{
    if (size_)
    {
        glInvalidateBufferData(id_);
    }
}

void BufferGLCoreDSA::makeResident()
{
    if (address_)
    {
        throw std::runtime_error("buffer is already resident");
    }

    if (size_)
    {
        glGetNamedBufferParameterui64vNV(id_, GL_BUFFER_GPU_ADDRESS_NV, &address_);
        glMakeNamedBufferResidentNV(id_, GL_READ_ONLY);
    }
    else
    {
        // ~0 is specifed as pointer to buffers with size 0
        address_ = 0;
    }
}

void BufferGLCoreDSA::makeNonResident()
{
    if (!address_)
    {
        throw std::runtime_error("buffer is not resident");
    }

    // ~0 is the pointer to a zero-sized buffer
    if (address_ != 0)
    {
        glMakeNamedBufferNonResidentNV(id_);
    }
    address_ = 0;
}

class BufferGLPersistentDSA : public BufferGL
{
public:
    BufferGLPersistentDSA(GLenum usage);
    virtual ~BufferGLPersistentDSA();

    virtual void update(void const *data, size_t offset, size_t size);
    virtual void *map(GLbitfield access, size_t offset, size_t length);
    virtual GLboolean unmap();
    virtual void setSize(size_t size);
    virtual void invalidate();
    virtual void makeResident();
    virtual void makeNonResident();

private:
    GLenum usageBits_;
};

BufferGLPersistentDSA::BufferGLPersistentDSA(GLbitfield usageBits)
    : usageBits_(usageBits)
{
    glGenBuffers(1, &id_);
}

BufferGLPersistentDSA::~BufferGLPersistentDSA()
{
    if (address_)
    {
        makeNonResident();
    }

    if (mappedAddress_)
    {
        unmap();
    }

    if (id_)
    {
        glDeleteBuffers(1, &id_);
    }
}

void BufferGLPersistentDSA::update(void const *data, size_t offset, size_t length)
{
    checkAndUpdateRange(offset, length, size_);

    glNamedBufferSubData(id_, offset, length, data);
}

void *BufferGLPersistentDSA::map(GLbitfield access, size_t offset, size_t length)
{
    checkAndUpdateRange(offset, length, size_);
    if (mappedAddress_)
    {
        throw std::runtime_error("Buffer is already mapped");
    }

    if (size_)
    {
        mappedAddress_ = glMapNamedBufferRange(id_, offset, length, access);
    }
    else
    {
        mappedAddress_ = nullptr;
    }

    return mappedAddress_;
}

GLboolean BufferGLPersistentDSA::unmap()
{
    if (!mappedAddress_)
    {
        throw std::runtime_error("Buffer is not mapped");
    }

    if (mappedAddress_ != nullptr)
    {
        mappedAddress_ = nullptr;
        return glUnmapNamedBuffer(id_);
    }
    else
    {
        return GL_TRUE;
    }
}

void BufferGLPersistentDSA::setSize(size_t size)
{
    if (address_)
    {
        throw std::runtime_error("Buffer is resident while calling Buffer::setSize");
    }
    if (mappedAddress_)
    {
        throw std::runtime_error("Buffer is mapped while calling Buffer::operation");
    }
    if (size_ != size)
    {
        // A persistent storage buffer cannot be resized. Create a new buffer object.
        glDeleteBuffers(1, &id_);
        glCreateBuffers(1, &id_);
        glNamedBufferStorage(id_, size, nullptr, usageBits_);
        size_ = size;
    }
}

void BufferGLPersistentDSA::invalidate()
{
    if (size_)
    {
        glInvalidateBufferData(id_);
    }
}

void BufferGLPersistentDSA::makeResident()
{
    if (address_)
    {
        throw std::runtime_error("buffer is already resident");
    }

    if (size_)
    {
        glGetNamedBufferParameterui64vNV(id_, GL_BUFFER_GPU_ADDRESS_NV, &address_);
        glMakeNamedBufferResidentNV(id_, GL_READ_ONLY);
    }
    else
    {
        // ~0 is specifed as pointer to buffers with size 0
        address_ = 0;
    }
}

void BufferGLPersistentDSA::makeNonResident()
{
    if (!address_)
    {
        throw std::runtime_error("buffer is not resident");
    }

    // ~0 is the pointer to a zero-sized buffer
    if (address_ != 0)
    {
        glMakeNamedBufferNonResidentNV(id_);
    }
    address_ = 0;
}

#endif

BufferGL::BufferGL()
    : address_(0), size_(0), mappedAddress_(nullptr)
{
    GLuint id;
    glGenBuffers(1, &id);
    setGLId(id);
}

BufferGL::~BufferGL()
{
}

std::unique_ptr<BufferGL> BufferGL::create(ModeCore, GLenum mode, GLenum defaultTarget)
{
#if defined(GL_VERSION_4_5)
    if (GLEW_VERSION_4_5)
    {
        return std::make_unique<BufferGLCoreDSA>(mode);
    }
    else
    {
        return std::make_unique<BufferGLCore>(mode, defaultTarget);
    }
#else
    return std::make_unique<BufferGLCore>(mode, defaultTarget);
#endif
}

std::unique_ptr<BufferGL> BufferGL::create(ModePersistentBuffer, GLbitfield modeBits)
{
#if defined(GL_VERSION_4_5)
    if (!GLEW_ARB_buffer_storage)
    {
        throw std::runtime_error("ARB_buffer_storage not available");
    }
    return std::make_unique<BufferGLPersistentDSA>(modeBits);
#else
    throw std::runtime_error("GL 4.5 support not enabled");
#endif
}

size_t BufferGL::getSize() const
{
    return size_;
}

void *BufferGL::getMappedAddress() const
{
    if (!mappedAddress_)
    {
        throw std::runtime_error("buffer is not mapped");
    }
    return mappedAddress_;
}

bool BufferGL::isMapped() const
{
    return mappedAddress_ != nullptr;
}

GLuint64EXT BufferGL::getAddress()
{
    if (!address_)
    {
        makeResident();
    }
    assert(address_);
    return address_;
}

bool BufferGL::isResident() const
{
    return address_ != 0;
}