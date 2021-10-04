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
		Entity CreateEntity(const std::string& tag = std::string());
		void DestroyEntity(Entity entity);

	private:
		entt::registry m_Registry;
	};
}