#pragma once
#include "Renderer/Buffer.hpp"

namespace Hydrogen
{
	class OpenGLVertexBuffer
		: public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, std::size_t size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;

		virtual void Unbind() const override;
	
	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer
		: public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, std::size_t size);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;

		virtual void Unbind() const override;
	
		virtual uint32_t GetCount() const override { return m_Count; };

	private:
		uint32_t m_RendererID;
		std::size_t m_Count;

	};
}