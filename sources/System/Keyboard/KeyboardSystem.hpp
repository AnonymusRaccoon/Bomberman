//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/System/System.hpp"
#include <map>

namespace Bomberman
{
	//! @brief A system to handle keyboard entities.
	class KeyboardSystem : public WAL::System
	{
	public:
		//! @inherit
		const std::type_info &getComponent() const override;
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		KeyboardSystem() = default;
		//! @brief A keyboard system is copy constructable
		KeyboardSystem(const KeyboardSystem &) = default;
		//! @brief A default destructor
		~KeyboardSystem() override = default;
		//! @brief A keyboard system is assignable.
		KeyboardSystem &operator=(const KeyboardSystem &) = default;
	};
}
