#pragma once

#include "Bolt/Scene/Scene.h"
#include "Bolt/Scene/Components.h"

#include <entt.hpp>

namespace Bolt {
	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene) : m_Scene(scene), m_Handle(handle) {};

		template<typename T>
		bool Has() { return m_Scene->m_Registry.all_of<T>(m_Handle); }

		template<typename T, typename... Args>
		T& Add(Args&&... args) { 
			BL_CORE_ASSERT(Has<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& Get() { 
			BL_CORE_ASSERT(!Has<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_Handle);
		}

		template<typename T>
		void Remove() { 
			BL_CORE_ASSERT(!Has<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.remove<T>(m_Handle);
		}

		operator bool() { return m_Handle != entt::null; }
		operator entt::entity() { return m_Handle; }
		operator uint32_t() { return (uint32_t)m_Handle; }

		const Transform& transform() { return Get<Transform>(); }
		const std::string& tag() { return Get<Tag>().tag; }


	private:
		entt::entity m_Handle = entt::null;
		Scene* m_Scene = nullptr;
	};
}