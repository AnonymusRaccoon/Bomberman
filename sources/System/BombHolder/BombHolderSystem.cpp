//
// Created by Zoe Roux on 5/31/21.
//

#include "Component/Timer/TimerComponent.hpp"
#include "System/Event/EventSystem.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "BombHolderSystem.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/BombHolder/BombHolderComponent.hpp"
#include "Component/Health/HealthComponent.hpp"

using namespace std::chrono_literals;
namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	std::chrono::nanoseconds BombHolderSystem::explosionTimer = 3s;
	float BombHolderSystem::explosionRadius = 3;

	BombHolderSystem::BombHolderSystem(WAL::Wal &wal)
		: WAL::System({
			typeid(PositionComponent),
			typeid(BombHolderComponent),
			typeid(ControllableComponent)
		}),
		_wal(wal)
	{}

	void BombHolderSystem::_bombExplosion(WAL::Entity &bomb, WAL::Wal &wal)
	{
		std::cout << "Boom" << std::endl;
		bomb.scheduleDeletion();
		auto &bombPosition = bomb.getComponent<PositionComponent>();
		wal.getSystem<EventSystem>().dispatchEvent([&bombPosition](WAL::Entity &entity){
			if (!entity.hasComponent<HealthComponent>() ||
			    !entity.hasComponent<PositionComponent>())
				return;
			auto &position = entity.getComponent<PositionComponent>();

			if (position.position.distance(bombPosition.position) <= BombHolderSystem::explosionRadius)
				entity.getComponent<HealthComponent>().takeDmg(1);
		});
	}

	void BombHolderSystem::_spawnBomb(Vector3f position)
	{
		std::cout << "Spawnned" << std::endl;
		this->_wal.scene->addEntity("Bomb")
			.addComponent<PositionComponent>(position)
			.addComponent<TimerComponent>(BombHolderSystem::explosionTimer, &BombHolderSystem::_bombExplosion)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/bombs/bomb.obj",
				std::make_pair(MAP_DIFFUSE, "assets/bombs/bomb_normal.png"));
	}

	void BombHolderSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime)
	{
		auto &holder = entity.getComponent<BombHolderComponent>();
		auto &position = entity.getComponent<PositionComponent>();
		auto &controllable = entity.getComponent<ControllableComponent>();

		if (controllable.bomb && holder.bombCount > 0) {
			holder.bombCount--;
			this->_spawnBomb(position.position);
		}
		if (holder.bombCount < holder.maxBombCount) {
			holder.nextBombRefill -= dtime;
			if (holder.nextBombRefill <= 0ns) {
				holder.nextBombRefill = holder.refillRate;
				holder.bombCount++;
			}
		}
	}
}