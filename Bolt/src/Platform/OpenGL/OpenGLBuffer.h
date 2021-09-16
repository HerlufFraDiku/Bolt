#pragma once

#include "Bolt/Renderer/Buffer.h"

namespace Bolt {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indicies, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual inline uint32_t GetCount() override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count = 0;
	};
}