#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <string>
#include "Bolt/Core/Core.h"
#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include "Bolt/Renderer/Texture.h"

namespace Bolt {
	struct Tag {
		std::string tag;

		Tag() = default;
		Tag(const Tag&) = default;
		Tag(const std::string& tag) : tag(tag) {}
	};

	struct Transform {
		glm::vec3 Translation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale{ 1.0f, 1.0f, 1.0f };

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const glm::vec3& translation) : Translation(translation) {}

		glm::mat4 GetTransform() const {
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
			return glm::translate(glm::mat4{ 1.0f }, Translation) * rotation * glm::scale(glm::mat4{ 1.0f }, Scale);
		}
	};

	struct SpriteRenderer {
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture;
		float tilingFactor = 1.0f;

		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(const glm::vec4 & color) : Color(color) {}
	};

	struct CameraComponent {
		bool isPrimary = true;
		bool isFixedAspectRatio = false;
		SceneCamera Camera;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScript {
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScript*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScript* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}