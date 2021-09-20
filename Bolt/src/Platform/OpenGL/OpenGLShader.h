#pragma once

#include "Bolt/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Bolt {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;

	private:
		uint32_t m_RendererID;
	};
}