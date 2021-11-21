#include "blpch.h"
#include "Entity.h"

namespace Bolt {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_Handle(handle), m_Scene(scene)
	{
	}

}