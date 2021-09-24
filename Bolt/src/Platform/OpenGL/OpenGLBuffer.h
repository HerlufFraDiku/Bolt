#pragma once
#include <Glad/glad.h>
#include "Bolt/Renderer/Buffer.h"

namespace Bolt {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(BLenum drawMode, uint32_t size, float* vertices = nullptr);
		virtual ~OpenGLVertexBuffer();

		virtual void Load(uint32_t size, void* verticies) override;
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
		uint32_t m_Size;
		GLenum m_DrawMode;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(BLenum drawmode, uint32_t size, uint32_t* indicies = nullptr);
		virtual ~OpenGLIndexBuffer();

		virtual void Load(uint32_t size, void* indicies) override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual inline uint32_t GetCount() override { return m_Size / sizeof(uint32_t); }

	private:
		uint32_t m_RendererID;
		uint32_t m_Size;
		GLenum m_DrawMode;
	};
}