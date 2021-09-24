#include "blpch.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Bolt {
	GLenum MapBoltDrawMode(BLenum drawMode) {
		switch (drawMode) {
			case BL_STATIC: return GL_STATIC_DRAW;
			case BL_DYNAMIC: return GL_DYNAMIC_DRAW;
		}

		BL_CORE_ASSERT(false, "Unsupported drawmode!")
		return GL_NONE;
	}

	// ############### VERTEX BUFFER ###############

	OpenGLVertexBuffer::OpenGLVertexBuffer(BLenum drawMode, uint32_t size, float* verticies) : m_Size(size), m_DrawMode(MapBoltDrawMode(drawMode)) {
		BL_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, m_DrawMode);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		BL_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Load(uint32_t size, void* verticies) {
		BL_PROFILE_FUNCTION();
		BL_CORE_ASSERT(size == m_Size, "Data does not fit buffer!");

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Size, verticies);
	}

	void OpenGLVertexBuffer::Bind() {
		BL_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() {
		BL_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// ############### INDEX BUFFER ###############

	OpenGLIndexBuffer::OpenGLIndexBuffer(BLenum drawMode, uint32_t size, uint32_t* indicies): m_Size(size), m_DrawMode(MapBoltDrawMode(drawMode)) {
		BL_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, m_DrawMode);
	}
		
	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		BL_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Load(uint32_t size, void* indicies) {
		BL_PROFILE_FUNCTION();
		BL_CORE_ASSERT(size == m_Size, "Data does not fit buffer!");

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, indicies);
	}

	void OpenGLIndexBuffer::Bind() {
		BL_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	
	void OpenGLIndexBuffer::Unbind() {
		BL_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}