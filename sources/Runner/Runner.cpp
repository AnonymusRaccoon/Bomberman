//
// Created by Zoe Roux on 5/24/21.
//

#include <Wal.hpp>
#include <iostream>
#include "System/Movable/MovableSystem.hpp"
#include "System/Renderer/RenderSystem.hpp"
#include <Model/Model.hpp>
#include <Drawables/2D/Rectangle.hpp>
#include <TraceLog.hpp>
#include "Component/Position/PositionComponent.hpp"
#include "Models/Vector2.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Runner.hpp"
#include "Models/GameState.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;
namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	void updateState(WAL::Wal &engine, GameState &state)
	{
		// You can change the scene here or update the game state based on entities values.

		// If you want to keep a scene loaded but not running, store it in the state.loadedScenes.
		//      If you don't need the scene anymore, remember to remove it from the loadedScene array.
		if (RAY::Window::getInstance().shouldClose())
			engine.shouldClose = true;
	}

	void enableRaylib(WAL::Wal &wal)
	{
		RAY::TraceLog::setLevel(LOG_WARNING);
		RAY::Window &window = RAY::Window::getInstance(600, 400, "Bomberman", FLAG_WINDOW_RESIZABLE);
		wal.addSystem<RenderSystem>(wal, window);
	}

	std::shared_ptr<WAL::Scene> loadGameScene()
	{
//		Drawable2DComponent cmp = Drawable2DComponent(Vector2f(), Vector2f(), RED);

		auto scene = std::make_shared<WAL::Scene>();
//		scene->addEntity("cube")
//			.addComponent<PositionComponent>()
//			.addComponent<Drawable2DComponent>(Vector2f(), Vector2f(10, 10), RED);
		scene->addEntity("player")
			.addComponent<PositionComponent>()
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/player/player.iqm", std::make_pair(MAP_DIFFUSE, "assets/player/blue.png"));
		scene->addEntity("camera")
			.addComponent<PositionComponent>(10, 10, 10)
			.addComponent<CameraComponent>();
		return scene;
	}

	int run()
	{
		WAL::Wal wal;
		wal.addSystem<MovableSystem>();
		enableRaylib(wal);
		wal.scene = loadGameScene();

		try {
			wal.run<GameState>(updateState);
			return 0;
		} catch (const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
			return 1;
		}
	}
}