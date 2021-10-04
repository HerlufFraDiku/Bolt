#include "blpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Bolt/Renderer/Renderer2D.h"
#include "Bolt/Renderer/RenderCommand.h"
#include "Bolt/Renderer/VertexArray.h"
#include "Bolt/Renderer/Shader.h"

namespace Bolt {
	struct QuadVertex { glm::vec3 Position; glm::vec4 Tint; glm::vec2 TexCoord; float TexIndex; };

	struct Renderer2DStorage {
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVerticies = MaxQuads * 4;
		static const uint32_t MaxIndicies = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: query GPU for this on Init

		Ref<VertexArray> VA;
		Ref<VertexBuffer> VB;
		Ref<Shader> Shader;
		Ref<Texture2D> DefaultTexture;

		uint32_t BatchIndexCount = 0;
		QuadVertex* BatchStart = nullptr;
		QuadVertex*	BatchOffset = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotCount = 1; // We always have the default texture added

		RenderStats Stats;
	};

	static Renderer2DStorage s_Data;

	void Renderer2D::Init() {
		BL_PROFILE_FUNCTION();

		// Create VertexArray to store Vertex and Index buffers in.
		s_Data.VA = VertexArray::Create();

		// Create Vertex Array and set the layout of vertex attributes
		s_Data.VB = VertexBuffer::Create(s_Data.MaxVerticies * sizeof(QuadVertex));
		s_Data.VB->SetLayout({
			{ ShaderElementType::Float3, "a_Position" },
			{ ShaderElementType::Float4, "a_Tint" },
			{ ShaderElementType::Float2, "a_TexCoord" },
			{ ShaderElementType::Float,  "a_TexIndex" }
		});
		s_Data.VA->AddVertexBuffer(s_Data.VB);

		// Generate indicies for all verticies.
		uint32_t* indicies = new uint32_t[s_Data.MaxIndicies];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndicies; i += 6) {
			indicies[i + 0] = offset + 0;
			indicies[i + 1] = offset + 1;
			indicies[i + 2] = offset + 2;
			indicies[i + 3] = offset + 2;
			indicies[i + 4] = offset + 3;
			indicies[i + 5] = offset + 0;
			offset += 4;
		}
		Ref<IndexBuffer> IB = IndexBuffer::Create(s_Data.MaxIndicies * sizeof(uint32_t), indicies);
		delete[] indicies;
		s_Data.VA->SetIndexBuffer(IB);

		// Create a buffer to batch verticies for rendering in.
		s_Data.BatchStart = new QuadVertex[s_Data.MaxVerticies];


		// Load the default flat shader and upload texture indicies to it
		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++) samplers[i] = i;
		s_Data.Shader = Shader::Create("assets/shaders/Flat.glsl");
		s_Data.Shader->Bind();
		s_Data.Shader->SetInts("u_Texture", s_Data.MaxTextureSlots, samplers);
		
		// Create a 1x1 white texture to use as the default texture
		s_Data.DefaultTexture = Texture2D::Create(1, 1);
		uint32_t whiteColor = 0xFFFFFFFF;
		s_Data.DefaultTexture->SetData(&whiteColor, sizeof(uint32_t));
		s_Data.TextureSlots[0] = s_Data.DefaultTexture;
	}

	void Renderer2D::Shutdown() { }

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		BL_PROFILE_FUNCTION();

		// Bind our shader and upload camera projection to it
		s_Data.Shader->Bind();
		s_Data.Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		// Start a new batch
		NewBatch();
	}

	void Renderer2D::EndScene() {
		BL_PROFILE_FUNCTION();
		Flush();
	}

	void Renderer2D::Flush() {
		BL_PROFILE_FUNCTION();
		// Compute the size of the batch and load it into the vertex buffer
		uint32_t size = (uint8_t*)s_Data.BatchOffset - (uint8_t*)s_Data.BatchStart;
		s_Data.VB->Load(size, s_Data.BatchStart);

		// Bind all our textures and lets do some drawing!
		for (uint32_t i = 0; i < s_Data.TextureSlotCount; i++) s_Data.TextureSlots[i]->Bind();
		RenderCommand::DrawIndexed(s_Data.VA, s_Data.BatchIndexCount);

		// Start a new batch
		NewBatch();

		s_Data.Stats.DrawCount += 1;
	}

	void Renderer2D::DrawQuad(const Quad& quad) {
		BL_PROFILE_FUNCTION();

		// If we are out of space for this batch flush the renderer
		if (s_Data.BatchIndexCount >= s_Data.MaxIndicies) Flush();

		float textureIndex = GetTextureIndex(quad);

		// Compute transformed quad positions (origin at center)
		glm::mat4 identity = glm::mat4(1.0f);
		glm::mat4 transform = 
			glm::translate(identity, quad.Position) * 
			glm::rotate(identity, quad.Rotation, glm::vec3(0, 0, 1)) * 
			glm::scale(identity, glm::vec3(quad.Size.x, quad.Size.y, 0.0f));

		glm::vec4 positions[4] = {
			transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
			transform * glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f),
			transform * glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f),
			transform * glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f),
		};

		// Add the 4 quad verticies to the batch
		s_Data.BatchOffset->Position = positions[0];
		s_Data.BatchOffset->Tint = quad.Tint;
		s_Data.BatchOffset->TexCoord = { 0.0f, 0.0f };
		s_Data.BatchOffset->TexIndex = textureIndex;
		s_Data.BatchOffset++;

		s_Data.BatchOffset->Position = positions[1];
		s_Data.BatchOffset->Tint = quad.Tint;
		s_Data.BatchOffset->TexCoord = { 1.0f, 0.0f };
		s_Data.BatchOffset->TexIndex = textureIndex;
		s_Data.BatchOffset++;

		s_Data.BatchOffset->Position = positions[2];
		s_Data.BatchOffset->Tint = quad.Tint;
		s_Data.BatchOffset->TexCoord = { 1.0f, 1.0f };
		s_Data.BatchOffset->TexIndex = textureIndex;
		s_Data.BatchOffset++;

		s_Data.BatchOffset->Position = positions[3];
		s_Data.BatchOffset->Tint = quad.Tint;
		s_Data.BatchOffset->TexCoord = { 0.0f, 1.0f };
		s_Data.BatchOffset->TexIndex = textureIndex;
		s_Data.BatchOffset++;

		s_Data.BatchIndexCount += 6;

		s_Data.Stats.QuadCount += 1;
	}

	void Renderer2D::NewBatch() {
		// Reset vertex batching buffer
		s_Data.BatchIndexCount = 0;
		s_Data.BatchOffset = s_Data.BatchStart;
		s_Data.TextureSlotCount = 1;
	}

	float Renderer2D::GetTextureIndex(const Quad& quad) {
		BL_PROFILE_FUNCTION();

		if (quad.Texture == nullptr) return 0.0f; // Use default white texture if quad has no texture

		// Otherwise look the quad texture in existing batch textures
		float texIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotCount; i++) {
			bool textureIsInBatch = *s_Data.TextureSlots[i].get() == *quad.Texture.get();
			if (textureIsInBatch) texIndex = (float)i; break;
		}

		// If it was found: Good!
		if (texIndex != 0.0f) return texIndex;

		// Otherwise we need to add it
		texIndex = s_Data.TextureSlotCount;
		s_Data.TextureSlots[s_Data.TextureSlotCount] = quad.Texture;
		s_Data.TextureSlotCount++;
	}

	void Renderer2D::ResetStats() {
		memset(&s_Data.Stats, 0, sizeof(RenderStats));
	}

	RenderStats Renderer2D::GetStats() {
		return s_Data.Stats;
	}

}