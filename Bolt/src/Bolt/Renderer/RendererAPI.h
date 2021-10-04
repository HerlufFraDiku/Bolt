#pragma once
#include <glm/glm.hpp>
#include "Bolt/Renderer/VertexArray.h"

namespace Bolt {
	class RendererAPI {
	public:
		enum class API { None = 0, OpenGL = 1 };

		static API s_API;
		inline static API GetAPI() { return s_API; }

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t indexCount) = 0;
	};
}