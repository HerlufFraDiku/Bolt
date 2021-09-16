#include "blpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Bolt {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetApi()) {
			case RendererAPI::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indicies, uint32_t count) {
		switch (Renderer::GetApi()) {
			case RendererAPI::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indicies, count);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
	}
}