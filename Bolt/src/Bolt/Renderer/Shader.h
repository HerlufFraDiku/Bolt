#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Bolt {
	class Shader {
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const = 0;

		static Shader* Create(std::string& vertexSrc, std::string& fragmentSrc);
	};
}