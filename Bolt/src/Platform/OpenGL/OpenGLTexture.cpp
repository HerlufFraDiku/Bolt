#include "blpch.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "stb_image.h"

namespace Bolt {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) {
		BL_PROFILE_FUNCTION();

		// Use stb_image to load the image at path
		int height, width, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		BL_CORE_ASSERT(data, "Could not load image!");
		m_Width = width;
		m_Height = height;

		// Move the texture to GPU
		if (channels == 4) { m_InternalFormat = GL_RGBA8; m_DataFormat = GL_RGBA; }
		if (channels == 3) { m_InternalFormat = GL_RGB8; m_DataFormat = GL_RGB; }
		BL_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data); // free the image on the CPU
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height): m_Width(width), m_Height(height), m_Slot(0) {
		BL_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8; 
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		BL_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		BL_PROFILE_FUNCTION();

		BL_CORE_ASSERT(size == (m_DataFormat == GL_RGBA ? 4 : 3) * m_Width * m_Height, "Texture data must match texture size!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) {
		BL_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererID);
		m_Slot = slot;
	}

	uint32_t OpenGLTexture2D::GetSlot() const {
		return m_Slot;
	}
}