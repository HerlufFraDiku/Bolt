#include "blpch.h"
#include "Bolt/Renderer/Batcher2D.h"
#include "Bolt/Renderer/RenderCommand.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Bolt {

	Batch2D::Batch2D(uint32_t maxQuads) : m_MaxQuads(maxQuads), m_Count(0), m_VA(VertexArray::Create()), m_Verts(maxQuads * 4) {
		BL_PROFILE_FUNCTION();

		// Generate vertex buffer with space for all our verts
		auto vb = VertexBuffer::CreateDynamic(maxQuads * sizeof(Vertex));
		vb->SetLayout({
			{ ShaderElementType::Float3, "a_Position"},
			{ ShaderElementType::Float4, "a_Tint"},
			{ ShaderElementType::Float2, "a_TexCoords"},
			{ ShaderElementType::Float,  "a_TexId"},
		});
		m_VA->AddVertexBuffer(vb);

		// Generate index buffer, since its static for the whole batch
		int numIndicies = maxQuads * 6; // We need 6 indicies per quad
		std::vector<uint32_t> indicies(numIndicies);

		for (uint32_t i = 0; i < maxQuads; i += 1) {
			indicies[i * 6]     = i * 4 + 0;
			indicies[i * 6 + 1] = i * 4 + 1;
			indicies[i * 6 + 2] = i * 4 + 2;
			indicies[i * 6 + 3] = i * 4 + 2;
			indicies[i * 6 + 4] = i * 4 + 3;
			indicies[i * 6 + 5] = i * 4 + 0;
		}

		m_VA->SetIndexBuffer(IndexBuffer::Create(numIndicies * sizeof(uint32_t), indicies.data()));
	}

	void Batch2D::AddQuad(const Quad& quad) {
		BL_PROFILE_FUNCTION();

		// Translate, rotate and scale the unit quad
		glm::mat4 identity = glm::mat4(1.0f);
		glm::mat4 transform = glm::translate(identity, quad.Position) * glm::rotate(identity, quad.Rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(identity, glm::vec3(quad.Size.x, quad.Size.y, 1.0f));
		glm::vec3 positions[4] = {
			transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
			transform * glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f),
			transform * glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f),
			transform * glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f),
		};

		// Push the 4 verts to m_Verts
		m_Verts[m_Count * 4]     = { positions[0].x, positions[0].y, positions[0].z, quad.Tint.r, quad.Tint.g, quad.Tint.b, quad.Tint.a, 0.0f, 0.0f, 0.0f }; // TODO: Tex id
		m_Verts[m_Count * 4 + 1] = { positions[1].x, positions[1].y, positions[1].z, quad.Tint.r, quad.Tint.g, quad.Tint.b, quad.Tint.a, 1.0f, 0.0f, 0.0f }; // TODO: Tex id
		m_Verts[m_Count * 4 + 2] = { positions[2].x, positions[2].y, positions[2].z, quad.Tint.r, quad.Tint.g, quad.Tint.b, quad.Tint.a, 1.0f, 1.0f, 0.0f }; // TODO: Tex id
		m_Verts[m_Count * 4 + 3] = { positions[3].x, positions[3].y, positions[3].z, quad.Tint.r, quad.Tint.g, quad.Tint.b, quad.Tint.a, 0.0f, 1.0f, 0.0f }; // TODO: Tex id

		m_Count++;
	}

	void Batch2D::Flush() {
		BL_PROFILE_FUNCTION();
		
		// TODO: Bind textures

		m_VA->Bind();
		m_VA->GetIndexBuffer()->Bind();

		auto vertexBuffer = m_VA->GetVertexBuffers()[0];
		vertexBuffer->Load(m_Verts.size() * sizeof(Vertex), m_Verts.data());
		vertexBuffer->Bind();

		m_Count = 0;
		
		RenderCommand::DrawIndexed(m_VA);
	}
}