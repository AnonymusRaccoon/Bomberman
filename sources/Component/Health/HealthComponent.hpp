//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#pragma once

#include <Models/Callback.hpp>
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	class HealthComponent : public WAL::Component
	{

		private:
			//! @brief life of an entity
			unsigned int _healthPoint;

		public:
			//! @brief The callback invoked on this entity's death.
			WAL::Callback<WAL::Entity &> onDeath;

			//! @brief add health to the entity
			void addHealthPoint(unsigned int healthPoint);
			
			//! @brief reduce health
			void takeDmg(unsigned int damage);

			//! @brief return health point of the entity
			unsigned int getHealthPoint(void) const;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
			
			//! @brief A Health component can't be instantiated, it should be derived.
			explicit HealthComponent(WAL::Entity &entity);

			//! @brief Constructor
			HealthComponent(WAL::Entity &entity, unsigned int healthPoint, WAL::Callback<WAL::Entity &> onDeath = WAL::Callback<WAL::Entity &>());

			//! @brief A Health component can't be instantiated, it should be derived.
			HealthComponent(const HealthComponent &) = default;

			//! @brief default destructor
			~HealthComponent() override = default;

			//! @brief A Health component can't be assigned
			HealthComponent &operator=(const HealthComponent &) = delete;
	};
}