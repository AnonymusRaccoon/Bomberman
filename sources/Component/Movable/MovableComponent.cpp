//
// Created by Zoe Roux on 5/17/21.
//

#include "MovableComponent.hpp"

namespace BBM
{
	MovableComponent::MovableComponent(WAL::Entity &entity)
		: Component(entity)
	{}

	WAL::Component *MovableComponent::clone(WAL::Entity &entity) const
	{
		return new MovableComponent(entity);
	}

	void MovableComponent::addForce(Vector3f force)
	{
		this->_acceleration += force;
	}

	void MovableComponent::resetVelocity(void)
	{
		this->_velocity = {0, 0, 0};
	}

	const Vector3f &MovableComponent::getVelocity(void) const
	{
		return _velocity;
	}

} // namespace WAL