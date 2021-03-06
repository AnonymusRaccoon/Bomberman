//
// Created by Louis Auzuret on 2021-05-20.
//

#pragma once

#include "Models/Callback.hpp"
#include "Models/Vector3.hpp"
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	class CollisionComponent : public WAL::Component
	{
	public:
		//! @brief Used to tell the collided axis
		//! @note Usage: (collidedAxis (int given by callback)) & CollidedAxis::X
		enum CollidedAxis {
			NONE = 0,
			X = 1,
			Y = 2,
			Z = 4,
			ALL = 7
		};

		//! @brief onCollide functions to be called
		//! @param first self
		//! @param second the entity you collided
		//! @param third the collision axis (to know which axis collided)
		WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> onCollide;
		//! @brief onCollided functions to be called
		//! @param first the entity that collided you
		//! @param second self
		//! @param third the collision axis (to know which axis collided)
		WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> onCollided;
		//! @brief Bound size on all axis
		Vector3f bound;
		//! @brief Offset from the position component
		Vector3f positionOffset;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief A component can't be instantiated, it should be derived.
		explicit CollisionComponent(WAL::Entity &entity);

		//! @brief Constructor with a WAL::Callback
		CollisionComponent(WAL::Entity &entity,
		                   const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollide,
		                   const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollided,
		                   Vector3f positionOffset,
		                   Vector3f bound);

		//! @brief Constructor with a WAL::Callback, same boundSize for all axis
		CollisionComponent(WAL::Entity &entity,
		                   const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollide,
		                   const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollided,
		                   float positionOffset,
		                   float boundSize);

		//! @brief Constructor of collider with no callback
		CollisionComponent(WAL::Entity &entity, Vector3f positionOffset, Vector3f bound);

		//! @brief Constructor no callback, same boundSize & positionOffset for all axis
		CollisionComponent(WAL::Entity &entity, float positionOffset, float boundSize);

		//! @brief Default copy constructor
		CollisionComponent(const CollisionComponent &) = default;

		//! @brief default destructor
		~CollisionComponent() override = default;

		//! @brief A component can't be assigned
		CollisionComponent &operator=(const CollisionComponent &) = delete;
	};

	CollisionComponent::CollidedAxis operator|(CollisionComponent::CollidedAxis first, CollisionComponent::CollidedAxis second);
	CollisionComponent::CollidedAxis &operator|=(CollisionComponent::CollidedAxis &self, CollisionComponent::CollidedAxis other);
}