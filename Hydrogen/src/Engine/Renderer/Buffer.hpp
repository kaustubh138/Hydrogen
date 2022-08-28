#pragma once
#include "ShaderDataType.hpp"

namespace Hydrogen
{
	struct BufferElement
	{
		ShaderDataType Type;
		std::string Name;
		std::size_t Size;
		std::size_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool noramlized = false)
			: Type(type), Name(name), Size(0), Offset(0), Normalized(noramlized)
		{}
	
		std::size_t GetComponentCount() const;
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elems);

		const std::vector<BufferElement>& GetElements() { return m_Elements; }
		std::size_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	
	private:
		void calculateOffsetAndStride();
	
	private:
		std::vector<BufferElement> m_Elements;
		std::size_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() = 0;

		static VertexBuffer* Create(float* vertices, std::size_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, std::size_t size);
	};
}