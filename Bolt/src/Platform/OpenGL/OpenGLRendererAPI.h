#pragma once

#include "Bolt/Renderer/RendererAPI.h"

namespace Bolt {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}