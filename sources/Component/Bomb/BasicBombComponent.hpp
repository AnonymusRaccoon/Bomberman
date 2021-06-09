//
// Created by Utilisateur on 08/06/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class BasicBombComponent : public WAL::Component
	{
	public:
		//! @brief The radius of the explosion.
		const float explosionRadius = 3;
		//! @brief The damage made by the explosion on an entity
		const int damage = 1;
		//! @brief The ID of the owner.
		int ownerID;
		//! @brief Should collisions with the owner be disabled.²
		bool ignoreOwner = true;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief A component can't be instantiated, it should be derived.
		explicit BasicBombComponent(WAL::Entity &entity, int damage, float explosionRadius, int ownerID);

		//! @brief A component can't be instantiated, it should be derived.
		BasicBombComponent(const BasicBombComponent &) = default;

		//! @brief default destructor
		~BasicBombComponent() override = default;

		//! @brief A component can't be assigned
		BasicBombComponent &operator=(const BasicBombComponent &) = delete;
	};
}