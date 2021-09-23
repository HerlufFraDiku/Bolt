#include "blpch.h"
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Bolt {
	void OpenGLRendererAPI::Init() {
		BL_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		BL_PROFILE_FUNCTION();

		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		BL_PROFILE_FUNCTION();

		glClearColor(color.r, color.b, color.g, color.a);
	}
	
	void OpenGLRendererAPI::Clear() {
		BL_PROFILE_FUNCTION();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::Draw(const Ref<VertexArray>& vertexArray) {
		BL_PROFILE_FUNCTION();

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}