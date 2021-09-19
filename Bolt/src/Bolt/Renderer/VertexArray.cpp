#include "blpch.h"
#include "Bolt/Renderer/VertexArray.h"
#include "Bolt/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Bolt {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
	}
}