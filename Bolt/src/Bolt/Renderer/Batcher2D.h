#pragma once
#include <glm/glm.hpp>
#include "Bolt/Renderer/Renderer2D.h"
#include "Bolt/Renderer/Buffer.h"
#include "Bolt/Renderer/VertexArray.h"
#include "Bolt/Renderer/Texture.h"

namespace Bolt {
	struct Vertex { float position[3]; float tint[4]; float texcoords[2]; float texid; };

	class Batch2D {
	public:
		Batch2D(uint32_t maxQuads = 1024);
		~Batch2D() = default;

		bool HasSpace() { return m_MaxQuads < m_Count; }
		void AddQuad(const Quad& quad);
		void Flush();

	private:
		uint32_t m_MaxQuads, m_Count;
		Ref<VertexArray> m_VA;
		std::vector<Vertex> m_Verts;
	};
}

