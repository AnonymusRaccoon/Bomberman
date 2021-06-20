//
// Created by Zoe Roux on 6/11/21.
//

#pragma once

#include "System/System.hpp"
#include "Component/Lobby/LobbyComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"
#include <array>
#include <string>

namespace BBM
{
	//! @brief A system to handle Health entities.
	class LobbySystem : public WAL::System<LobbyComponent, Drawable2DComponent>
	{
	private:

		bool _canJoin();

		void _nextColor(WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &entity);


		static std::array<RAY::Color, 4> _rayColors;

		std::array<bool, 4> _colorTaken = {};
	public:
		static std::array<std::string, 4> colors;

		//! @brief Add a controller for the player.
		static void addController(WAL::Entity &player, ControllableComponent::Layout layout);

		//! @brief Create ingame tile
		static void createTile(const std::shared_ptr<WAL::Scene>& drawable, WAL::Entity &player, int color, int playerCount);

		//! @inherit
		void onUpdate(WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &entity, std::chrono::nanoseconds dtime) override;

		//! @inherit
		void onSelfUpdate(std::chrono::nanoseconds dtime) override;

		//! @brief Check if every player is ready.
		//! @param scene The lobby scene containing lobby players.
		static bool playersAreReady(WAL::Scene &scene);

		//! @brief Inform the engine that the next scene should be the game scene and load it.
		//! @param wal The engine.
		static void switchToGame(WAL::Wal &wal);

		//! @brief Reset the lobby scene to it's default state.
		void unloadLobby();

		//! @brief Add an AI to the game.
		void addAI();

		//! @brief Remove an AI from the game.
		void removeAI();

		//! @brief A default constructor
		explicit LobbySystem(WAL::Wal &wal);
		//! @brief A Lobby system is copy constructable
		LobbySystem(const LobbySystem &) = default;
		//! @brief A default destructor
		~LobbySystem() override = default;
		//! @brief A system is not assignable.
		LobbySystem &operator=(const LobbySystem &) = delete;
	};
}