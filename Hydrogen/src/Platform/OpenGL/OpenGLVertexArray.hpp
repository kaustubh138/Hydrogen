#pragma once

#include "Renderer/VertexArray.hpp"

namespace Hydrogen
{
	class OpenGLVertexArray
		: public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& idx_buffer) override;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() override;

	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

		// Inherited via VertexArray
	};
}

