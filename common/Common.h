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
            
        };
    }; // namespace Common
};     // namespace OpenGLSandbox