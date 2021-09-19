#pragma once

#include "Bolt/Renderer/VertexArray.h"
#include <glm/glm.hpp>

namespace Bolt {
	class RendererAPI {
	public:
		enum class API { None = 0, OpenGL = 1 };

		static API s_API;
		inline static API GetAPI() { return s_API; }

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray) = 0;
	};
}