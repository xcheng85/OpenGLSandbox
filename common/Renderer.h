#pragma once

#include <string>

#include <vector>

#include <memory>

#include "Common.h"

namespace OpenGLSandbox
{
    namespace Common
    {

        /*
        // vertex attribute includes two things: format and data
        class IVertexAttribute
        {
        public:
        private:
            IVertexData *vertexData_;
            IVertexFormat *vertexFormat;
        };

        class IBufferDesc
        {
            // enum bufferDescType
        };

        class IBuffer
        {
            // event observer to do
        public:
            virtual void setSize(size_t width, size_t height, size_t depth) = 0;
            virtual void updateData(size_t offset, const void *data, size_t size) = 0;
            //virtual void *map(enum accessType) = 0;
            virtual bool unmap() = 0;
        };

        class IIndices
        {
            virtual void setData(
                enum dataType,
                IBuffer *buffer, //index buffer
                size_t offset,
                size_t count) = 0;

        private:
            //enum type;
            // index buffer address
            size_t offset_;
            size_t count_;
        };

        class ITextureDesc
        {

        public:
            //enum TextureType type;
            //enum TextureFormat format;
            //enum pixelFormat
            //enum dataType
            size_t width_;
            size_t height_;
            size_t depth_;
            size_t layer_;
            bool mipmap_;
        };

        class ITextureData
        {
        public:
            //enum TextureDataType type;  pointer, buffer, native
        };

        class ISamplerState;
        class ITexture
        {
        public:
            virtual void setData(ITextureData &data) = 0;
            virtual void setDefaultSampleState(const ISamplerState &samplerState) = 0;
        };

        class ISamplerStateDesc // abstraction of opengl/vulkan
        {
            //eunm SamplerStateDataType
        };

        // Texture sampler State
        class ISamplerState
        {
        };

        class ISampler
        {
        public:
            virtual void setSamplerState(ISamplerState *state) = 0;
            virtual void setTexture(ITexture *texture) = 0;
        };*/

        struct RenderOptions
        {
            size_t numInstances_;
        };
        /*
        class IGeometryDesc
        {
            virtual void setPrimitive() = 0;
            virtual void setBaseVertex() = 0;
            virtual void setIndex() = 0;

            // primitiveType
            unsigned int primitiveRestartIndex_;
            unsigned int baseVertex_;
            unsigned int indexFirst_;
            unsigned int indexCount_;
        };

        class IGeomtry
        {
            IGeometryDesc *geometryDesc_;
            IVertexAttribute *vertexAttributes_; // vb is included here + vb format
            IIndices *indices_;                  // indice buffer is here
        };

        class IGeometryInstance
        {
            virtual void setGeometry(IGeomtry *) = 0;
            virtual void setVisible(bool) = 0;
            virtual void setProgramPipeline() = 0;
        };

        // shader program
        // separate program
        class IShaderProgram
        {
            // enum program type
        };

        class IProgramDesc
        {
            // how to describe a shader program 

            // 1. shader programs 
            // 2. each program has input and out put:
        };

        class IProgram
        {
        };

        class IProgramPipeline
        {
        };

        class IProgramParameter // one parameter
        {
        public:
            IProgramParameter(const std::string &name, type, unsigned int arraySize);
            std::string name_;
            // type; // vec4, mat4
            unsigned int arraySize_; // mat4[2]
        };
        // all the parameters in the programe
        // including parameter and also the data

        class IDescriptorSetLayoutDesc
        {
        public:
            IDescriptorSetLayoutDesc(IProgramParameter *parameters, size_t numParameters);
            IProgramParameter *prameters_;
            size_t numParameters_;

            //  bool multicast;//  some nvidia extension
        };

        // Vulkan
        class IDescriptorSetLayout
        {
            public: 
            unsigned int getNum() const; // number of shader parameters
            // virtual ContainerEntry getEntryByName(const std::string& para) const = 0; 
        };

        class IDescriptorSet
        {
            // have the resource
            public: 
            //virtual setData()
        };

        class IRenderGroup
        {
            // a rendergroup care about a few things: 
            // 1. geometry to draw 
            // 2. shader pipeline
            // 3. binding 
            virtual void addGeometryInstance(IGeometryInstance*) = 0; 
            virtual void removeGeometryInstance(IGeometryInstance*) = 0;
            virtual void setProgramPipeline(IProgramPipeline*) = 0; 
            virtual void bindDescriptorSet(IDescriptorSet*) = 0;
        };*/

        class Renderer
        {
        public:
            virtual ~Renderer();
            virtual void update() = 0; // all kinds of optimization
            // groupdId: opaque, transparent, depth
            virtual void render(const std::string &groupId, const RenderOptions &renderOptions = RenderOptions()) = 0;

            // Vertex Format
            // Due to different combination, a renderer may have a few general vertex input state
            // see vkVertexInputAttributeDescription
            virtual std::unique_ptr<IVertexInputAttribute> createVertexInputAttribute(const VertexInputAttributeCreateInfo &desc) = 0;

            // buffer
            // see vkVertexInputBinding
            virtual std::unique_ptr<IBuffer> createBuffer(const BufferCreateInfo &desc) = 0;

            // vertex binding the buffer
            virtual std::unique_ptr<IVertexInputBinding> createVertexInputBinding(const VertexInputBindingCreateInfo &desc) = 0;

            // VkPipelineVertexInputStateCreateInfo
            // binding buffers, and binding vertexattributes how to read the buffer so that vertex shader can understand
            virtual std::unique_ptr<IPipelineVertexInputState> createPipelineVertexInputState(const PipelineVertexInputStateCreateInfo &desc) = 0;

            virtual std::unique_ptr<IIndexBuffer> createIndexBuffer(const IndexBufferCreateInfo &desc) = 0;
            virtual std::unique_ptr<ITexture *> createTexture(const TextureCreateInfo &desc) = 0;
            /*


            // sampler state
            virtual std::unique_ptr<ISamplerState *> createSamplerState(const ISamplerStateDesc &desc) = 0;
            // sampler
            virtual std::unique_ptr<ISampler *> createSampler() = 0;

            // geometry desc
            virtual std::unique_ptr<IGeometryDesc *> createGeometryDesc() = 0;

            // geometry has 3 deps
            virtual std::unique_ptr<IGeomtry *> createGeometry(const IGeometryDesc &desc, const IVertexAttribute *va, const IIndices *indices) = 0;

            // geometry instances
            virtual std::unique_ptr<IGeometryInstance *> createGeometryInstance() = 0;

            // shader program separate
            virtual std::unique_ptr<IProgram *> createProgram(const IProgramDesc &desc) = 0;
            // pipeline
            virtual std::unique_ptr<IProgramPipeline *> createProgramPipeline(const IProgram const *program, unsigned int numPrograms) = 0;
            
            
            // shader input
            virtual std::unique_ptr<IDescriptorSet*> createDescriptorSet(IDescriptorSetLayout*) = 0;
            virtual std::unique_ptr<IDescriptorSetLayout*> createDescriptorSetLayout(const IDescriptorSetLayoutDesc& desc) = 0;

            // render group
            */

        protected:
        private:
        };
    } // namespace Common
} // namespace OpenGLSandbox
