#include "blpch.h"
#include "Bolt/Renderer/Framebuffer.h"
#include "Bolt/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Bolt {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpec& spec) {
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported");
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}
}