#include "blpch.h"
#include "Bolt/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Bolt {
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::Init() {
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera) {
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() { }

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		BL_PROFILE_FUNCTION();

		vertexArray->Bind();

		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		RenderCommand::DrawIndexed(vertexArray);
	}
}