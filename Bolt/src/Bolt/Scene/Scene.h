#pragma once

#include "Bolt/Core/Core.h"
#include "Bolt/Core/Timestep.h"

#include <entt.hpp>

namespace Bolt {
	class Entity;

	class Scene {
		friend class Entity;

	public:
		Scene() = default;
		~Scene() = default;

		void OnUpdate(Timestep dt);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity CreateEntity(const std::string& tag = std::string());
		void DestroyEntity(Entity entity);

	private:
		entt::registry m_Registry;

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	};
}