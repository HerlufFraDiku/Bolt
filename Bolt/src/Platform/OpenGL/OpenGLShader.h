#pragma once

#include "Bolt/Renderer/Shader.h"

namespace Bolt {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererID;
	};
}