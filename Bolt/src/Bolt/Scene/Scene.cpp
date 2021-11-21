#include "blpch.h"
#include "Bolt/Scene/Scene.h"
#include "Bolt/Scene/Entity.h"
#include "Bolt/Scene/Components.h"
#include "Bolt/Renderer/Renderer2D.h"

namespace Bolt {
	void Scene::OnUpdate(Timestep dt) {
		
		// Find the main camera in the scene
		Camera* mainCamera = nullptr;
		glm::mat4* mainCameraTransform = nullptr;

		auto view = m_Registry.view<Transform, CameraComponent>();
		for (auto entity : view) {
			auto [transform, camera] = view.get<Transform, CameraComponent>(entity);
			if (camera.isPrimary) {
				mainCamera = &camera.Camera;
				mainCameraTransform = &transform.GetTransform();
				break;
			}
		}
		
		// If a camera was found we can begin a scene
		if (mainCamera) {
			Renderer2D::BeginScene(*mainCamera, *mainCameraTransform);

			// Render sprites
			auto group = m_Registry.group<Transform>(entt::get<SpriteRenderer>);
			for (auto entity : group) {
				auto& [transform, sprite] = group.get<Transform, SpriteRenderer>(entity);
				auto quad = Quad(
					transform.Translation,
					glm::vec2(transform.Scale.x, transform.Scale.y),
					transform.Rotation.z,
					sprite.Texture,
					sprite.Color
				);
				Renderer2D::DrawQuad(quad);
			}
			
			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height) {
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize non-fixed cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			auto& cameraComp = view.get<CameraComponent>(entity);
			BL_CORE_INFO("Camera is found");
			if (!cameraComp.isFixedAspectRatio) {
				BL_CORE_INFO("Camera is not fixed");
				cameraComp.Camera.SetViewportSize(width, height);
			}
		}
	}

	Entity Scene::CreateEntity(const std::string& tag) {
		Entity entity{ m_Registry.create(), this };
		entity.Add<Tag>(tag.empty() ? "Entity" : tag);
		entity.Add<Transform>();
		return entity;
	}

	void Scene::DestroyEntity(Entity entity) {
		m_Registry.destroy(entity);
	}
}