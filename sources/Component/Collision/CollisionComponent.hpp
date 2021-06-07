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
		private:
		public:
			//! @brief onCollide functions to be called
			WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollide;
			//! @brief onCollided functions to be called
			WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollided;
			//! @brief Bound size on all axis
			Vector3f bound;
			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief A component can't be instantiated, it should be derived.
			explicit CollisionComponent(WAL::Entity &entity);

			//! @brief Constructor with a WAL::Callback
			CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollide, WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollided,Vector3f bound);

			//! @brief Constructor with a WAL::Callback, same boundSize for all axis
			CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollide, WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollided, float boundSize = 0);

			//! @brief Constructor of collider with no callback
			CollisionComponent(WAL::Entity &entity, Vector3f bound);

			//! @brief Constructor no callback, same boundSize for all axis
			CollisionComponent(WAL::Entity &entity, float boundSize);

			//! @brief Default copy constructor
			CollisionComponent(const CollisionComponent &) = default;

			//! @brief default destructor
			~CollisionComponent() override = default;

			//! @brief A component can't be assigned
			CollisionComponent &operator=(const CollisionComponent &) = delete;
	};
}