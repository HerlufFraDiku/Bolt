#include "blpch.h"
#include <filesystem>
#include "Bolt/Renderer/Shader.h"
#include "Bolt/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Bolt {
	Ref<Shader> Shader::Create(const std::string& filepath) {
		std::string name = std::filesystem::path(filepath).stem().string();

		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::API::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, filepath);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& filepath) {
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::API::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, filepath);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetApi()) {
			case RendererAPI::API::None: BL_CORE_ASSERT(false, "RendererAPI::API::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		BL_CORE_ASSERT(false, "Unknown RendererAPI is not supported");
		return nullptr;
	}

	void ShaderLibrary::Add(Ref<Shader> shader) {
		auto name = shader->GetName();
		BL_CORE_ASSERT(!Has(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::Create(name, filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		BL_CORE_ASSERT(Has(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Has(const std::string& name) {
		return m_Shaders.find(name) != m_Shaders.end();
	}
}