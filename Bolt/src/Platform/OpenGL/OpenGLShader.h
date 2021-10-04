#pragma once
#include "Bolt/Renderer/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

typedef std::unordered_map<GLenum, std::string> ShaderMap;

namespace Bolt {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& name, const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual const std::string& GetName() const override { return m_Name; }

		virtual void SetInt(const std::string& name, int value) const override;
		virtual void SetInts(const std::string& name, const uint32_t count, const int* value) const override;
		virtual void SetFloat(const std::string& name, float value) const override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& vector) const override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vector) const override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vector) const override;
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) const override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) const override;

		void UploadUniformInt(const std::string& name, int value) const;
		void UploadUniformIntArray(const std::string& name, const uint32_t count, const int* value) const;
		void UploadUniformFloat(const std::string& name, float value) const;
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) const;
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) const;
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) const;
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

	private:
		const std::string ReadFile(const std::string filepath);
		ShaderMap Preprocess(const std::string& source);
		void Compile(const ShaderMap&);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}