#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Bolt {
	class Shader {
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) const = 0;
		virtual void SetIntVector(const std::string& name, const uint32_t count, const int* value) const = 0;
		virtual void SetFloat(const std::string& name, float value) const = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& vector) const = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vector) const = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vector) const = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) const = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary {
	public:
		void Add(Ref<Shader> shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Get(const std::string& name);
		bool Has(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}