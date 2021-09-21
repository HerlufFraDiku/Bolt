#include "blpch.h"

#include "Bolt/Renderer/Renderer.h"
#include "Bolt/Renderer/Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Bolt {
	
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}
}