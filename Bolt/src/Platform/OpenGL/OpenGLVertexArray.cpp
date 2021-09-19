#include "blpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Bolt {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderElementType type) {
		switch (type)
		{
			case Bolt::ShaderElementType::None:   return GL_NONE;
			case Bolt::ShaderElementType::Float:  return GL_FLOAT;
			case Bolt::ShaderElementType::Float2: return GL_FLOAT;
			case Bolt::ShaderElementType::Float3: return GL_FLOAT;
			case Bolt::ShaderElementType::Float4: return GL_FLOAT;
			case Bolt::ShaderElementType::Int:    return GL_INT;
			case Bolt::ShaderElementType::Int2:   return GL_INT;
			case Bolt::ShaderElementType::Int3:   return GL_INT;
			case Bolt::ShaderElementType::Int4:   return GL_INT;
			case Bolt::ShaderElementType::Mat3:   return GL_FLOAT;
			case Bolt::ShaderElementType::Mat4:   return GL_FLOAT;
			case Bolt::ShaderElementType::Bool:   return GL_BOOL;

			default: {
				BL_CORE_ASSERT("Unknown ShaderElementType!");
				return 0;
			}
		}
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() {
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() {
		glBindVertexArray(0);

	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		BL_CORE_ASSERT(vertexBuffer->GetLayout()->GetSize(), "VertexBuffer has no layout");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		BufferLayout layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		for (auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}