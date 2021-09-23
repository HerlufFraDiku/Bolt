#include "blpch.h"
#include "Bolt/Renderer/Renderer.h"
#include "Bolt/Renderer/Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Bolt {
	
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}
}