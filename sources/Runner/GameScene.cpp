#include <memory>
#include <Wal.hpp>
#include "Runner.hpp"
#include <map>
#include <Component/Bonus/PlayerBonusComponent.hpp>
#include "Component/Music/MusicComponent.hpp"
#include "Component/Sound/SoundComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Animator/AnimatorComponent.hpp"
#include "Component/Animation/AnimationsComponent.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Collision/CollisionComponent.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Component/BombHolder/BombHolderComponent.hpp"
#include "Component/Tag/TagComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include <Drawables/Image.hpp>
#include "Component/Gravity/GravityComponent.hpp"
#include "Component/BumperTimer/BumperTimerComponent.hpp"
#include "Component/Timer/TimerComponent.hpp"
#include "Model/Model.hpp"
#include "Map/Map.hpp"
#include "Component/Score/ScoreComponent.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	std::shared_ptr<WAL::Scene> Runner::loadGameScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		scene->addEntity("camera")
			.addComponent<PositionComponent>(8, 0, -5)
			.addComponent<CameraComponent>(Vector3f(8, 0, 8));
		scene->addEntity("background image")
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/map/breakable_wall.obj", true, std::make_pair(MAP_DIFFUSE, "assets/backgrounds/game.png"), Vector3f(50, 1, 50))
			.addComponent<PositionComponent>(5, -2, 0);
		scene->addEntity("background image")
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/map/breakable_wall.obj", true, std::make_pair(MAP_DIFFUSE, "assets/backgrounds/gameWall.png"), Vector3f(50, 1, 50), -90, Vector3f(), Vector3f(1, 0, 0))
			.addComponent<PositionComponent>(5, 14, 22);
		MapGenerator::loadMap(16, 16, MapGenerator::createMap(16, 16, hasHeights), scene);
		return scene;
	}

	WAL::Entity &Runner::createPlayer(WAL::Scene &scene)
	{
		std::map<SoundComponent::SoundIndex, std::string> soundPath ={
			{SoundComponent::JUMP, "assets/sounds/jump.wav"},
			{SoundComponent::MOVE, "assets/sounds/move.ogg"},
			{SoundComponent::BOMB, "assets/sounds/bomb_drop.ogg"},
			//{SoundComponent::DEATH, "assets/sounds/death.ogg"}
		};

		return scene.addEntity("player")
			.addComponent<PositionComponent>()
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/player/player.iqm", true)
			.addComponent<ScoreComponent>()
			.addComponent<AnimatorComponent>()
		    .addComponent<GravityComponent>()
	        .addComponent<BumperTimerComponent>()
			.addComponent<ControllableComponent>(true)
			.addComponent<TagComponent<BlowablePass>>()
			.addComponent<TagComponent<Player>>()
			.addComponent<AnimationsComponent>("assets/player/player.iqm", 3)
			.addComponent<CollisionComponent>(BBM::Vector3f{0.25, 0, 0.25}, BBM::Vector3f{.75, 2, .75})
			.addComponent<MovableComponent>()
			.addComponent<SoundComponent>(soundPath)
			.addComponent<MusicComponent>("assets/musics/music_battle.ogg")
			.addComponent<BombHolderComponent>()
			.addComponent<PlayerBonusComponent>()
			.addComponent<HealthComponent>(1, [](WAL::Entity &entity, WAL::Wal &) {
				auto &animation = entity.getComponent<AnimationsComponent>();
				
				animation.setAnimIndex(5);
				if (entity.hasComponent<AnimatorComponent>())
					entity.removeComponent<AnimatorComponent>();
				if (entity.hasComponent<TimerComponent>())
					return;
				entity.getComponent<ControllableComponent>().disabled = true;
				entity.addComponent<TimerComponent>(1s, [](WAL::Entity &ent, WAL::Wal &wal) {
					ent.scheduleDeletion();
				});
			});
	}
}