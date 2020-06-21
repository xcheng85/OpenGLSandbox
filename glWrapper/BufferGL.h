#pragma once

#include <assert.h>
#include <string>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include "ObjectGL.h"

namespace OpenGLSandbox
{
    namespace GLWrapper
    {
        class BufferGL : public ObjectGL
        {
        public:
            enum class ModeCore
            {
                Core
            };
            enum class ModePersistentBuffer
            {
                PersistentBuffer
            };
            static std::unique_ptr<BufferGL> create(ModeCore, GLenum usage, GLenum defaultTarget = GL_UNIFORM_BUFFER);
            static std::unique_ptr<BufferGL> create(ModePersistentBuffer, GLbitfield modeBits);
            virtual ~BufferGL();

            virtual void update(void const *dataSrc, size_t offset, size_t length){
                assert(false);
            };
            virtual void *map(GLbitfield access, size_t offset, size_t length){
                assert(false);
            };
            virtual GLboolean unmap(){
                assert(false);
            };

            void *getMappedAddress() const;
            bool isMapped() const;
            virtual void setSize(size_t size){
                assert(false);
            };
            size_t getSize() const;
            virtual void invalidate(){
                assert(false);
            };

            virtual void makeResident()
            {
                assert(false);
            };
            virtual void makeNonResident(){
                assert(false);
            };
            GLuint64EXT getAddress(); // be careful of order glfw and glew.h
            bool isResident() const;

        protected:
            BufferGL();                   //
            mutable GLuint64EXT address_; // 64-bit bindless address
            size_t size_;
            void *mappedAddress_;

        private:
        };
    }; // namespace GLWrapper
};     // namespace OpenGLSandbox
