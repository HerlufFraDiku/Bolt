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

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t indexCount) {
		BL_PROFILE_FUNCTION();

		uint32_t count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}