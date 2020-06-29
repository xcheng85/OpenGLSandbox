#pragma once

#include <assert.h>

#include <string>

#include <vector>

#include <memory>

namespace OpenGLSandbox
{
    namespace Common
    {
        inline static const unsigned int MAX_ATTRIBUTES = 16;
        enum class DataType
        {
            UNSIGNED_INT_8,
            UNSIGNED_INT_16,
            UNSIGNED_INT_32,
            UNSIGNED_INT_64,
            INT_8,
            INT_16,
            INT_32,
            INT_64,
            FLOAT_16,
            FLOAT_32,
            FLOAT_64,
            NUM_DATATYPES,
            UNKNOWN
        };

        inline size_t getSizeOf(DataType dataType)
        {
            switch (dataType)
            {
            case DataType::INT_8:
            case DataType::UNSIGNED_INT_8:
                return 1;
            case DataType::INT_16:
            case DataType::UNSIGNED_INT_16:
            case DataType::FLOAT_16:
                return 2;
            case DataType::INT_32:
            case DataType::UNSIGNED_INT_32:
            case DataType::FLOAT_32:
                return 4;
            case DataType::INT_64:
            case DataType::UNSIGNED_INT_64:
            case DataType::FLOAT_64:
                return 8;
            case DataType::UNKNOWN:
                return 0;
            default:
                assert(false);
                return 0;
            }
        };

        // VertexFormatInfo
        // represent one such as position or normal or tex
        struct VertexInputAttributeDescription
        {
            uint8_t bindingIndex;  // layout = 0, 1, 2
            uint8_t streamId;      // 8 bit is enough, position and normal may be in different buffer
            size_t offset;         //
            size_t stride;         //
            bool normalized;       // ??
            DataType dataType;     //float, int,
            uint8_t numComponents; // ivec2, vec3, dvec4, etc.
        };

        struct VertexInputAttributeCreateInfo
        {
            std::vector<VertexInputAttributeDescription> vertexInputAttributes;
        };

        class IVertexInputAttribute
        {
        public:
            virtual ~IVertexInputAttribute(){};
        };

        enum class BufferFormat
        {
            UNKNOWN,
            FLOAT,
            FLOAT2,
            FLOAT3,
            FLOAT4,
            INT_8,
            INT2_8,
            INT3_8,
            INT4_8,
            INT_16,
            INT2_16,
            INT3_16,
            INT4_16,
            INT_32,
            INT2_32,
            INT3_32,
            INT4_32,
            UINT_8,
            UINT2_8,
            UINT3_8,
            UINT4_8,
            UINT_16,
            UINT2_16,
            UINT3_16,
            UINT4_16,
            UINT_32,
            UINT2_32,
            UINT3_32,
            UINT4_32,
            NATIVE,
            NUM_BUFFERFORMATS
        };

        enum class AccessType
        {
            NONE,
            READ_ONLY,
            WRITE_ONLY,
            READ_WRITE
        };

        enum class BufferCreateInfoType
        {
            GL,
            VULKAN,
            DX
        };

        struct BufferCreateInfo
        {
            BufferCreateInfo(BufferCreateInfoType type = BufferCreateInfoType::GL) : type(type)
            {
            }
            virtual ~BufferCreateInfo()
            {
            }
            BufferCreateInfoType type;
        };

        class IBuffer
        {
        public:
            virtual ~IBuffer(){};
        };

        // number of vertices
        // each vertices have different vertex attributes, they can come from different buffer, or come from same buffer with different offset
        // multiple buffers/streams
        // each has different offset in that stream could be different

        // buffer use as a source of vertex buffer,
        // reference vulkan vkCmdBindVertexBuffers
        struct VertexInputBindingCreateInfo
        {
            //binding slot, pBuffer and offset
            std::vector<std::tuple<size_t, IBuffer *, size_t>> bufferDescs;
            size_t numVertices;
        };

        class IVertexInputBinding
        {
        public:
            virtual ~IVertexInputBinding(){};
        };

        struct PipelineVertexInputStateCreateInfo
        {
            IVertexInputBinding *pVertexInputBinding;
            IVertexInputAttribute *pVertexInputAttribute;
        };

        class IPipelineVertexInputState
        {
        public:
            virtual ~IPipelineVertexInputState(){};
        };

        struct IndexBufferCreateInfo
        {
            IBuffer *buffer;
            size_t offset;
            size_t count;
            DataType indexType; // uint16, uint32
        };

        class IIndexBuffer
        {
        public:
            virtual ~IIndexBuffer(){};
        };

        enum class InternalTextureFormat
        {
            R8,
            R16,
            RG8,
            RG16,
            RGB8,
            RGB16,
            RGBA8,
            RGBA16,
            R16F,
            RG16F,
            RGB16F,
            RGBA16F,
            R32F,
            RG32F,
            RGB32F,
            RGBA32F,
            R8I,
            R8UI,
            R16I,
            R16UI,
            R32I,
            R32UI,
            RG8I,
            RG8UI,
            RG16I,
            RG16UI,
            RG32I,
            RG32UI,
            RGB8I,
            RGB8UI,
            RGB16I,
            RGB16UI,
            RGB32I,
            RGB32UI,
            RGBA8I,
            RGBA8UI,
            RGBA16I,
            RGBA16UI,
            RGBA32I,
            RGBA32UI,
            COMPRESSED_R,
            COMPRESSED_RG,
            COMPRESSED_RGB,
            COMPRESSED_RGBA,
            COMPRESSED_SRGB,
            COMPRESSED_SRGB_ALPHA,
            ALPHA,
            LUMINANCE,
            LUMINANCE_ALPHA,
            RGB,
            RGBA,
            NATIVE,
            NUM_INTERNALTEXTUREFORMATS
        };

        // for cube maps, either use a native data type
        // or pass in the faces via TextureDataPtr
        // with 6 layers: +x,-x,+y,-y,+z,-z
        enum class TextureType
        {
            _1D,
            _1D_ARRAY,
            _2D,
            _2D_ARRAY,
            _3D,
            BUFFER,
            CUBEMAP,
            //CUBEMAP_ARRAY,
            NATIVE,
            NUM_TEXTURETYPES
        };

        enum class TextureDataType
        {
            POINTER,
            BUFFER,
            NATIVE, // shared resource coming from glWrapper
            NUM_TEXTUREDATATYPES
        };

        enum class PixelFormat
        {
            R,
            RG,
            RGB,
            RGBA,
            BGR,
            BGRA,
            LUMINANCE,
            ALPHA,
            LUMINANCE_ALPHA,
            DEPTH_COMPONENT,
            DEPTH_STENCIL,
            STENCIL_INDEX,
            NATIVE,
            NUM_PIXELFORMATS,
            UNKNOWN
        };

        struct TextureCreateInfo
        {
            virtual ~TextureCreateInfo(){};

            TextureType type;
            InternalTextureFormat internalFormat;
            PixelFormat pixelFormat;
            DataType dataType;
            size_t width;
            size_t height;
            size_t depth;
            size_t numLayers;
            bool useMipmaps;
        };

        class TextureData
        {
        public:
            TextureData(TextureDataType type);
            virtual ~TextureData();

            TextureDataType getTextureDataType() const { return type; }

        private:
            TextureDataType type;
        };

        class TextureDataBuffer : public TextureData
        {
        public:
            TextureDataBuffer(const std::shared_ptr<IBuffer> &buffer);

        private:
            std::shared_ptr<IBuffer> buffer_;
        };

        class TextureDataPtr : public TextureData
        {
        public:
            // real data
            TextureDataPtr(const void *data, PixelFormat pixelFormat, DataType pixelDataType);
            // 2d : mipmap0...n
            TextureDataPtr(const void *const *data, unsigned int numMipMapLevels, PixelFormat pixelFormat, DataType pixelDataType);
            // 2d : lay0: mimap0...n lay1: mimap0...n
            TextureDataPtr(const void *const *data, unsigned int numMipMapLevels, unsigned int numLayers, PixelFormat pixelFormat, DataType pixelDataType);

            inline auto getPixelFormat() const
            {
                return pixelFormat_;
            }

            inline auto getDataType() const
            {
                return dataType_;
            }

            inline auto getNumMipMapLevels() const
            {
                return numMipMapLevels_;
            }

            inline auto getNumLayers() const
            {
                return numLayers_;
            }
            // return raw ptr, could read/write
            auto getDataPtr() const
            {
                return pData_;
            };

        private:
            //
            //const void *pData_; // could be hetregenous vector to some pointer, float array
            void const *const *pData_; // vector of vector, 1darray, cubemap // array of pointer
            unsigned int numLayers_;
            unsigned int numMipMapLevels_;
            PixelFormat pixelFormat_;
            DataType dataType_;
        };

        class ITexture
        {
        public:
            virtual ~ITexture(){};
        };
    }; // namespace Common
};     // namespace OpenGLSandbox