#pragma once
#include "Bolt/Core/Core.h"

namespace Bolt {
	struct FramebufferSpec {
		uint32_t Width, Height, Samples = 1;
		bool SwapChainTarget = false;

		// TODO: BL_ENUM Format...
	};

	class Framebuffer {
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererId() const = 0;
		virtual uint32_t GetDepthAttachmentRendererId() const = 0;

		virtual const FramebufferSpec& GetSpec() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpec& spec);
	};
}