#include "blpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Bolt/Renderer/Renderer2D.h"
#include "Bolt/Renderer/RenderCommand.h"
#include "Bolt/Renderer/VertexArray.h"
#include "Bolt/Renderer/Shader.h"

namespace Bolt {
	struct Renderer2DStorage {
		Ref<VertexArray> VA;
		Ref<Shader> Shader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Storage;

	void Renderer2D::Init() {
		BL_PROFILE_FUNCTION();

		s_Storage = new Renderer2DStorage();
		s_Storage->VA = VertexArray::Create();

		float unitQuadVerticies[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Ref<VertexBuffer> VB = VertexBuffer::Create(sizeof(unitQuadVerticies), unitQuadVerticies);
		VB->SetLayout({
			{ ShaderElementType::Float3, "a_Position" },
			{ ShaderElementType::Float2, "a_TexCoord" }
		});
		s_Storage->VA->AddVertexBuffer(VB);

		uint32_t unitQuadIndecies[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> IB = IndexBuffer::Create(sizeof(unitQuadIndecies), unitQuadIndecies);
		s_Storage->VA->SetIndexBuffer(IB);

		s_Storage->Shader = Shader::Create("assets/shaders/Flat.glsl");

		s_Storage->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteColor = 0xFFFFFFFF;
		s_Storage->WhiteTexture->SetData(&whiteColor, sizeof(uint32_t));
	}

	void Renderer2D::Shutdown() {
		delete s_Storage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		BL_PROFILE_FUNCTION();

		s_Storage->Shader->Bind();
		s_Storage->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		
		// TODO: REMOVE
		s_Storage->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteColor = 0xFFFFFFFF;
		s_Storage->WhiteTexture->SetData(&whiteColor, sizeof(uint32_t));

		s_Storage->WhiteTexture->Bind();
		int samplerIds[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
		s_Storage->Shader->SetIntVector("u_Textures", 32, samplerIds);
	}

	void Renderer2D::EndScene() {
		s_Storage->Shader->Unbind();
	}

	void Renderer2D::DrawQuad(const Quad& quad) {
		BL_PROFILE_FUNCTION();

		s_Storage->Shader->Bind();
		// If quad has no texture use the default 1x1 white texture
		quad.Texture == nullptr ? s_Storage->WhiteTexture->Bind() : quad.Texture->Bind();

		glm::mat4 identity = glm::mat4(1.0f);
		glm::mat4 transform = glm::translate(identity, quad.Position) * glm::rotate(identity, quad.Rotation, glm::vec3(0, 0, 1)) * glm::scale(identity, glm::vec3(quad.Size.x, quad.Size.y, 1.0f));

		s_Storage->Shader->SetMat4("u_Transform", transform);
		s_Storage->Shader->SetFloat4("u_Color", quad.Tint);

		s_Storage->VA->Bind();
		RenderCommand::DrawIndexed(s_Storage->VA);
	}
}