//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#include "HealthComponent.hpp"

#include <utility>

namespace BBM
{
	HealthComponent::HealthComponent(WAL::Entity &entity, unsigned int healthPoint, std::function<void (WAL::Entity &)> callback)
			: WAL::Component(entity),
			  _healthPoint(healthPoint),
			  onDeath(std::move(callback))
	{}

	WAL::Component *HealthComponent::clone(WAL::Entity &entity) const
	{
		return new HealthComponent(entity);
	}

	void HealthComponent::addHealthPoint(unsigned int healthPoint)
	{
		this->_healthPoint += healthPoint;
	}

	void HealthComponent::takeDmg(unsigned int damage)
	{
		if (damage >= this->_healthPoint) {
			this->_healthPoint = 0;
 		} else
			this->_healthPoint -= damage;
	}

	unsigned int HealthComponent::getHealthPoint(void) const
	{
		return (this->_healthPoint);
	}
}