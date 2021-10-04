#pragma once
#include "Bolt/Renderer/Framebuffer.h"

namespace Bolt {
	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(const FramebufferSpec& spec);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		void Invalidate();

		virtual uint32_t GetColorAttachmentRendererId() const override { return m_ColorAttachment; }
		virtual uint32_t GetDepthAttachmentRendererId() const override { return m_DepthAttachment; }

		virtual const FramebufferSpec& GetSpec() const override { return m_Spec; }

	private:
		uint32_t m_RendererID, m_ColorAttachment, m_DepthAttachment;
		FramebufferSpec m_Spec;
	};
}