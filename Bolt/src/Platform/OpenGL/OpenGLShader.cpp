#include "blpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <Glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Bolt {
	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment") return GL_FRAGMENT_SHADER;

		BL_ASSERT(false, "Unsupported shader type!");
		return GL_NONE;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& filepath): m_Name(name) {
		std::string fileData = ReadFile(filepath);
		auto shaderSources = Preprocess(fileData);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc): m_Name(name) {
		ShaderMap shaderSources(2);
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSources);
	}

	const std::string OpenGLShader::ReadFile(const std::string filepath) {
		std::string result; 
		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (!in) {
			BL_CORE_ERROR("Could not open file '{0}'", filepath);
			return result;
		}

		// Resize result string to size of file
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);

		// Read file
		in.read(&result[0], result.size());
		in.close();

		return result;
	}

	ShaderMap OpenGLShader::Preprocess(const std::string& source) {
		ShaderMap shaderMap;

		const char* token = "#type";
		size_t tokenLen = strlen(token);
		size_t position = source.find(token, 0);

		// Split the file using token. Add each part to shaderMap with the correct type.
		while (position != std::string::npos) {
			// Find the end of the type declaration line
			size_t typeDefEnd = source.find_first_of("\r\n", position);
			BL_CORE_ASSERT(typeDefEnd != std::string::npos, "Syntax error");
			// Read the shader type so we can validate it
			size_t typeDefStart = position + tokenLen + 1;
			std::string type = source.substr(position + tokenLen + 1, typeDefEnd - typeDefStart);
			// Move postition to the start of the next shader source
			size_t shaderSrcStart = source.find_first_not_of("\r\n", typeDefEnd);
			position = source.find(token, shaderSrcStart);
			// Copy the shader source into shaderMap
			size_t shaderSrcEnd = position - (shaderSrcStart == std::string::npos ? source.size() - 1 : shaderSrcStart);
			shaderMap[ShaderTypeFromString(type)] = source.substr(shaderSrcStart, shaderSrcEnd);
		}

		return shaderMap;
	}

	void OpenGLShader::Compile(const ShaderMap& shaderMap) {
		uint32_t programID = glCreateProgram();

		BL_CORE_ASSERT(shaderMap <= 2, "Extra shader detected")
		// Compile each shader in shader map
		std::array<GLenum, 2> ids; 
		int index = 0;
		for ( auto vk : shaderMap ) {
			auto type = vk.first;
			auto source = vk.second;

			// Compile shader
			GLuint shader = glCreateShader(type);
			const GLchar* sourceStr = source.c_str();
			glShaderSource(shader, 1, &sourceStr, 0);
			glCompileShader(shader);

			// Check compilation status
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);
				BL_CORE_ERROR("{0}", infoLog.data());
				BL_CORE_ASSERT(false, "Shader compilation failure");
				break;
			}

			ids[index++] = shader;
			glAttachShader(programID, shader);
		}

		// Link the shader program with all shaders attached
		glLinkProgram(programID);

		// Check that linking went well
		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(programID);
			for (auto id: ids) glDeleteShader(id);
			BL_CORE_ERROR("{0}", infoLog.data());
			BL_CORE_ASSERT(false, "Shader link failure");
			return;
		}

		// Linking went well. We can detach shaders (they now live in the program) and set m_RendererID to the good program.
		for (auto id : ids) glDetachShader(programID, id);
		m_RendererID = programID;

	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		BL_CORE_ASSERT(location != -1, "Uniform location not found. Is the uniform declared in the shader?");

		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		BL_CORE_ASSERT(location != -1, "Uniform location not found. Is the uniform declared in the shader?");

		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		BL_CORE_ASSERT(location != -1, "Uniform location not found. Is the uniform declared in the shader?");

		glUniform2f(location, vector.x, vector.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vector) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		BL_CORE_ASSERT(location != -1, "Uniform location not found. Is the uniform declared in the shader?");

		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vector) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		BL_CORE_ASSERT(location != -1, "Uniform location not found. Is the uniform declared in the shader?");

		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		BL_CORE_ASSERT(location != -1, "Uniform location not found. Is the uniform declared in the shader?");

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		BL_CORE_ASSERT(location != -1, "Uniform location not found. Is the uniform declared in the shader?");

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}