//
// Created by Zoe Roux on 5/24/21.
//


#pragma once

#include <unordered_map>
#include <Scene/Scene.hpp>


namespace BBM
{
	//! @brief A class representing the current game state. This allow one to retain information between update calls.
	class GameState
	{
		//! @brief The list of scenes available.
		enum SceneID
		{
			MainMenuScene,
			GameScene,
			SettingsScene,
			PauseMenuScene,
			LobbyScene,

		};


		//! @brief The currently loaded scene
		SceneID currentScene = MainMenu;

		//! @brief The list of loaded scenes.
		std::unordered_map<SceneID, WAL::Scene> _loadedScenes = {};
	};
}