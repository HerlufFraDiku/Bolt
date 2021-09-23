#pragma once
#include <glm/glm.hpp>
#include "Bolt/Renderer/OrthographicCamera.h"
#include "Bolt/Renderer/Texture.h"

namespace Bolt {

	struct Quad {
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec2 Size = glm::vec2(1.0f, 1.0f);
		float Rotation = 0.0f;
		glm::vec4 Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Ref<Texture2D> Texture = nullptr;

		Quad(glm::vec2 position)																		  : Position(glm::vec3(position.x, position.y, 0.0f)) {}
		Quad(glm::vec3 position)																		  : Position(position) {}
		Quad(glm::vec2 position, glm::vec2 size)														  : Position(glm::vec3(position.x, position.y, 0.0f)), Size(size) {}
		Quad(glm::vec3 position, glm::vec2 size)														  : Position(position), Size(size) {}
		Quad(glm::vec2 position, glm::vec2 size, float rotation)										  : Position(glm::vec3(position.x, position.y, 0.0f)), Size(size), Rotation(rotation) {}
		Quad(glm::vec3 position, glm::vec2 size, float rotation)										  : Position(position), Size(size), Rotation(rotation) {}
		Quad(glm::vec2 position, glm::vec4 color)														  : Position(glm::vec3(position.x, position.y, 0.0f)), Tint(color) {}
		Quad(glm::vec3 position, glm::vec4 color)														  : Position(position), Tint(color) {}
		Quad(glm::vec2 position, glm::vec2 size, glm::vec4 color)										  : Position(glm::vec3(position.x, position.y, 0.0f)), Size(size), Tint(color) {}
		Quad(glm::vec3 position, glm::vec2 size, glm::vec4 color)										  : Position(position), Size(size), Tint(color) {}
		Quad(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color)						  : Position(glm::vec3(position.x, position.y, 0.0f)), Size(size), Tint(color), Rotation(rotation) {}
		Quad(glm::vec3 position, glm::vec2 size, float rotation, glm::vec4 color)						  : Position(position), Size(size), Tint(color), Rotation(rotation) {}
		Quad(glm::vec2 position, Ref<Texture2D> texture)												  : Position(glm::vec3(position.x, position.y, 0.0f)), Texture(texture) {}
		Quad(glm::vec3 position, Ref<Texture2D> texture)												  : Position(position), Texture(texture) {}
		Quad(glm::vec2 position, glm::vec2 size, Ref<Texture2D> texture)								  : Position(glm::vec3(position.x, position.y, 0.0f)), Size(size), Texture(texture) {}
		Quad(glm::vec3 position, glm::vec2 size, Ref<Texture2D> texture)								  : Position(position), Size(size), Texture(texture) {}
		Quad(glm::vec2 position, glm::vec2 size, float rotation, Ref<Texture2D> texture)				  : Position(glm::vec3(position.x, position.y, 0.0f)), Size(size), Texture(texture), Rotation(rotation) {}
		Quad(glm::vec3 position, glm::vec2 size, float rotation, Ref<Texture2D> texture)				  : Position(position), Size(size), Texture(texture), Rotation(rotation) {}
		Quad(glm::vec2 position, Ref<Texture2D> texture, glm::vec4 color)								  : Position(glm::vec3(position.x, position.y, 0.0f)), Tint(color), Texture(texture) {}
		Quad(glm::vec3 position, Ref<Texture2D> texture, glm::vec4 color)								  : Position(position), Tint(color), Texture(texture) {}
		Quad(glm::vec2 position, glm::vec2 size, Ref<Texture2D> texture, glm::vec4 color)				  : Position(glm::vec3(position.x, position.y, 0.0f)), Size(size), Tint(color), Texture(texture) {}
		Quad(glm::vec3 position, glm::vec2 size, Ref<Texture2D> texture, glm::vec4 color)				  : Position(position), Size(size), Texture(texture), Tint(color) {}
		Quad(glm::vec2 position, glm::vec2 size, float rotation, Ref<Texture2D> texture, glm::vec4 color) : Position(glm::vec3(position.x, position.y, 0.0f)), Size(size), Rotation(rotation), Tint(color), Texture(texture) {}
		Quad(glm::vec3 position, glm::vec2 size, float rotation, Ref<Texture2D> texture, glm::vec4 color) : Position(position), Size(size), Rotation(rotation), Tint(color), Texture(texture) {}
	};

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const Quad& quad);
	};
}

