//
// Created by Louis Auzuret on 5/20/21
//

#pragma once

#include "System/System.hpp"

namespace BBM
{
    //! @brief A system to handle collisions.
    class CollisionSystem : public WAL::System
    {
    public:
        //! @inherit
        void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		CollisionSystem() = default;
		//! @brief A movable system is copy constructable
		CollisionSystem(const CollisionSystem &) = default;
		//! @brief A default destructor
		~CollisionSystem() override = default;
		//! @brief A movable system is assignable.
		CollisionSystem &operator=(const CollisionSystem &) = default;
    };
}