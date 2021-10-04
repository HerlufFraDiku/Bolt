#include "blpch.h"
#include "Bolt/Scene/Scene.h"
#include "Bolt/Scene/Entity.h"
#include "Bolt/Scene/Components.h"
#include "Bolt/Renderer/Renderer2D.h"



namespace Bolt {
	void Scene::OnUpdate(Timestep dt) {
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