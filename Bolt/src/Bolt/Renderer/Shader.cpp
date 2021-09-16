#include "blpch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Bolt {
	Shader* Shader::Create(std::string& vertexSrc, std::string& fragmentSrc)
	{
		switch (Renderer::GetApi()) {
			case RendererAPI::None: BL_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
	}
}