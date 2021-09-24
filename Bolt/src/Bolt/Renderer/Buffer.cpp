#include "blpch.h"
#include "Bolt/Renderer/Buffer.h"
#include "Bolt/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Bolt {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size, float* verticies) {
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(BL_STATIC, size, verticies);

		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::CreateDynamic(uint32_t size, float* verticies) {
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(BL_DYNAMIC, size, verticies);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t size, uint32_t* indicies) {
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(BL_STATIC, size, indicies);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::CreateDynamic(uint32_t size, uint32_t* indicies) {
		switch (Renderer::GetApi()) {
		case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(BL_DYNAMIC, size);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}
}