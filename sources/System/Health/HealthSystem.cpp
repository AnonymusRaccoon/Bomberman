//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "HealthSystem.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	HealthSystem::HealthSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void HealthSystem::onFixedUpdate(WAL::ViewEntity<HealthComponent> &entity)
	{
		auto &health = entity.get<HealthComponent>();

		if (health.getHealthPoint() == 0)
			health.onDeath(entity);
	}
}