#pragma once
#include <glad/glad.h>
#include "Bolt/Renderer/Texture.h"

namespace Bolt {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) override;
		virtual uint32_t GetSlot() const override;

		virtual bool operator==(const Texture& other) const override {
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		uint32_t m_RendererID, m_Width, m_Height, m_Slot;
		GLenum m_InternalFormat, m_DataFormat;
	};
}

