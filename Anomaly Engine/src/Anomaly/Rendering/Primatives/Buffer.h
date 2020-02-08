#pragma once
#include <glm/vec3.hpp>

namespace Anomaly
{
	struct Vertex;

	enum class ShaderDataType : uint8_t
	{
		None = 0,
		
		Vec,
		Vec2,
		Vec3,
		Vec4,
		
		Mat3,
		Mat4,
		
		Int,
		Int2,
		Int3,
		Int4,

		Bool
		
	};	
	//Returns the number of bytes based on the type given
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch(type)
		{
			case ShaderDataType::Vec:	return 4;
			case ShaderDataType::Vec2:	return 8;
			case ShaderDataType::Vec3:	return 12;
			case ShaderDataType::Vec4:	return 16;
				
			case ShaderDataType::Mat3:	return 36;
			case ShaderDataType::Mat4:	return 64;
				
			case ShaderDataType::Int:	return 4;
			case ShaderDataType::Int2:	return 8;
			case ShaderDataType::Int3:	return 12;
			case ShaderDataType::Int4:	return 16;
				
			case ShaderDataType::Bool:	return 1;
		}

		AE_CORE_ASSERT(false, "Unknown shader data type!")
		return 0;
	}
	
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;
	
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{			
		}
		BufferElement(): Type(), Size(0), Offset(0), Normalized(false)
		{
		} ;
		
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Vec:	return 1;
				case ShaderDataType::Vec2:	return 2;
				case ShaderDataType::Vec3:	return 3;
				case ShaderDataType::Vec4:	return 4;

				case ShaderDataType::Int:	return 1;
				case ShaderDataType::Int2:	return 2;
				case ShaderDataType::Int3:	return 3;
				case ShaderDataType::Int4:	return 4;
				
				case ShaderDataType::Mat3:	return 9;
				case ShaderDataType::Mat4:	return 16;
				
				case ShaderDataType::Bool:	return 1;
			}
			
			AE_CORE_ASSERT(false, "Unknown shader data type!")
			return 0;
		}
	};	
	class BufferLayout
	{
	public:	
		BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
		{
			CalculateOffsetsAndStrides();
		};
		BufferLayout(): m_Stride(0)
		{
		} ;
		
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; };
		inline uint32_t GetStride() const { return m_Stride; };
		
		std::vector<BufferElement>::iterator begin()				{ return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end()					{ return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const	{ return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const		{ return m_Elements.end(); }
	
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

	private:
		void CalculateOffsetsAndStrides()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
			
		};
	};
	
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};
		
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexBuffer* Create(Vertex vertices[], uint32_t size);
		static VertexBuffer* Create(float* vertices, uint32_t size);

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
	};
	
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
	
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() {};
	
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	
		static FrameBuffer* Create();
	
		virtual void UpdateBuffer(unsigned int textureBuffer) = 0;
		virtual unsigned int ReturnFrameBuffer(float Width, float Height) = 0;
	};
}
