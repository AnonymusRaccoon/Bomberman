//
// Created by Louis Auzuret on 5/31/21.
//

#include <catch2/catch.hpp>
#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "System/Collision/CollisionSystem.hpp"
#include "Wal.hpp"

#define private public
#include "Component/Collision/CollisionComponent.hpp"

using namespace WAL;
using namespace BBM;


TEST_CASE("Collsion test", "[Component][System]")
{
	Wal wal;
	wal.scene->addEntity("player")
		.addComponent<PositionComponent>();
	//	.addComponent<CollisionComponent>([](Entity &actual, const Entity &) {
	//		auto &pos = actual.getComponent<PositionComponent>();
	//		pos.position.x = 1;
	//		pos.position.y = 1;
	//		pos.position.z = 1;
	//	}, 5.0);
	//Entity &entity = wal.scene->getEntities()[0];
//
	//REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());
//
	//entity.getComponent<CollisionComponent>()._bound.x = 5;
	//entity.getComponent<CollisionComponent>()._bound.y = 5;
	//entity.getComponent<CollisionComponent>()._bound.z = 5;
//
	//CollisionSystem collision(wal);
	//collision.onUpdate(entity, std::chrono::nanoseconds(1));
	//collision.onFixedUpdate(entity);
	//REQUIRE(entity.getComponent<PositionComponent>().position.x == 0);
	//REQUIRE(entity.getComponent<PositionComponent>().position.y == 0);
	//REQUIRE(entity.getComponent<PositionComponent>().position.z == 0);
//
//
	//wal.scene->addEntity("block")
	//	.addComponent<PositionComponent>()
	//	.addComponent<CollisionComponent>([](Entity &, const Entity &){}, 1);
	//collision.onUpdate(entity, std::chrono::nanoseconds(1));
	//collision.onFixedUpdate(entity);
	//REQUIRE(entity.getComponent<PositionComponent>().position.x == 1);
	//REQUIRE(entity.getComponent<PositionComponent>().position.y == 1);
	//REQUIRE(entity.getComponent<PositionComponent>().position.z == 1);
} 