//
// Created by Zoe Roux on 6/11/21.
//

#pragma once

#include <Component/Component.hpp>
#include <Entity/Entity.hpp>
#include <Color.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include <chrono>

namespace BBM
{
	class LobbyComponent : public WAL::Component
	{
	public:
		//! @brief The layout used for this player.
		ControllableComponent::Layout layout = ControllableComponent::NONE;
		//! @brief The ID of the lobby player (from 0 to 3)
		int playerID;
		//! @brief The color of the player (as an index)
		int color;
		//! @brief Is this player ready
		bool ready = false;
		//! @brief The entity containing the ready display.
		WAL::Entity &readyButton;
		//! @brief The time of last input that this lobby player has made.
		std::chrono::time_point<std::chrono::steady_clock> lastInput;

		Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new lobby component.
		explicit LobbyComponent(WAL::Entity &entity, int playerID, WAL::Entity &readyButton);
		//! @brief A lobby component is copyable.
		LobbyComponent(const LobbyComponent &) = default;
		//! @brief A default destructor
		~LobbyComponent() override = default;
		//! @brief A lobby component is not assignable.
		LobbyComponent &operator=(const LobbyComponent &) = delete;
	};
}
