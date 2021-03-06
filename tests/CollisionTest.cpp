
// Created by Louis Auzuret on 5/31/21.
//

#include <catch2/catch.hpp>
#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Wal.hpp"

#define private public

#include "System/Collision/CollisionSystem.hpp"
#include "System/Movable/MovableSystem.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Component/Collision/CollisionComponent.hpp"

using namespace WAL;
using namespace BBM;

// WARN THE COLLISION SYSTEM IS ONLY CHECKING/LOOPING ON MOVABLE ENTITIES


TEST_CASE("Collision test", "[Component][System]")
{
	Wal wal;
	CollisionSystem collision(wal);
	wal.changeScene(std::make_shared<Scene>());
	wal.getScene()->addEntity("player")
		.addComponent<PositionComponent>()
	    .addComponent<MovableComponent>()
		.addComponent<CollisionComponent>([](Entity &actual, const Entity &, int _) {
			try {
				auto &pos = actual.getComponent<PositionComponent>();
				pos.position.x = 1;
				pos.position.y = 1;
				pos.position.z = 1;
			} catch (std::exception &e) {};
		}, [](Entity &, const Entity &, int) {}, 0, 5.0);
	Entity &entity = wal.getScene()->getEntities().front();
	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());

	entity.getComponent<CollisionComponent>().bound.x = 5;
	entity.getComponent<CollisionComponent>().bound.y = 5;
	entity.getComponent<CollisionComponent>().bound.z = 5;

	collision.update(std::chrono::nanoseconds(1));
	collision.fixedUpdate();
	REQUIRE(entity.getComponent<PositionComponent>().position.x == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.y == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.z == 0.0);

	wal.getScene()->addEntity("block")
		.addComponent<PositionComponent>(2, 2, 2)
		.addComponent<CollisionComponent>(0, 1);
	Entity &player = wal.getScene()->getEntities().front();
	collision.update(std::chrono::nanoseconds(1));
	REQUIRE(player.hasComponent(typeid(PositionComponent)));
	collision.fixedUpdate();
	REQUIRE(wal.getScene()->getEntities().size() == 2);
	REQUIRE(player.hasComponent(typeid(PositionComponent)));
	REQUIRE(player.getComponent<PositionComponent>().position.x == 1.0);
	REQUIRE(player.getComponent<PositionComponent>().position.y == 1);
	REQUIRE(player.getComponent<PositionComponent>().position.z == 1);
}


TEST_CASE("Collision test with movable", "[Component][System]")
{
	Wal wal;
	CollisionSystem collision(wal);
	MovableSystem movable(wal);
	wal.changeScene(std::make_shared<Scene>());
	wal.getScene()->addEntity("player")
		.addComponent<PositionComponent>()
		.addComponent<CollisionComponent>([](Entity &actual, const Entity &, int) {},
		                                  [](Entity &actual, const Entity &, int) {}, 0, 5.0)
		.addComponent<MovableComponent>();

	wal.getScene()->addEntity("block")
		.addComponent<PositionComponent>(0, 0, 0)
		.addComponent<CollisionComponent>([](Entity &actual, const Entity &, int) {},
		                                  [](Entity &actual, const Entity &, int) {
			                                  try {
				                                  auto &mov = actual.getComponent<MovableComponent>();
				                                  mov._velocity = Vector3f();
			                                  } catch (std::exception &e) {};
		                                  }, 0, 1);
	Entity &entity = wal.getScene()->getEntities().front();
	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());

	entity.getComponent<CollisionComponent>().bound.x = 5;
	entity.getComponent<CollisionComponent>().bound.y = 5;
	entity.getComponent<CollisionComponent>().bound.z = 5;

	entity.getComponent<MovableComponent>().addForce({1, 1, 1});
	collision.update(std::chrono::nanoseconds(1));
	collision.fixedUpdate();
	movable.update(std::chrono::nanoseconds(1));
	movable.fixedUpdate();
	REQUIRE(entity.getComponent<PositionComponent>().position.x == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.y == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.z == 0.0);
}


TEST_CASE("Collision test callbacks calls", "[Component][System]")
{
	int nbCallbacksCalled = 0;
	Wal wal;
	CollisionSystem collision(wal);
	MovableSystem movable(wal);

	wal.changeScene(std::make_shared<Scene>());

	wal.getScene()->addEntity("player")
		.addComponent<PositionComponent>()
		.addComponent<CollisionComponent>(
			[&nbCallbacksCalled](Entity &actual, const Entity &, int) { nbCallbacksCalled++; },
			[&nbCallbacksCalled](Entity &actual, const Entity &, int) { nbCallbacksCalled++; }, 0, 5.0)
		.addComponent<MovableComponent>();

	wal.getScene()->addEntity("block")
		.addComponent<PositionComponent>(0, 0, 0)
	    .addComponent<MovableComponent>()
		.addComponent<CollisionComponent>(
			[&nbCallbacksCalled](Entity &actual, const Entity &, int) { nbCallbacksCalled++; },
			[&nbCallbacksCalled](Entity &actual, const Entity &, int) {
				nbCallbacksCalled++;
				try {
					auto &mov = actual.getComponent<MovableComponent>();
					mov._velocity = Vector3f();
				} catch (std::exception &e) {};
			}, 0, 1);
	Entity &entity = wal.getScene()->getEntities().front();
	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());

	entity.getComponent<CollisionComponent>().bound.x = 5;
	entity.getComponent<CollisionComponent>().bound.y = 5;
	entity.getComponent<CollisionComponent>().bound.z = 5;

	entity.getComponent<MovableComponent>().addForce({1, 1, 1});
	collision.update(std::chrono::nanoseconds(1));
	collision.fixedUpdate();
	movable.update(std::chrono::nanoseconds(1));
	movable.fixedUpdate();
	REQUIRE(nbCallbacksCalled == 4);
	REQUIRE(entity.getComponent<PositionComponent>().position.x == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.y == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.z == 0.0);
}

TEST_CASE("Collision test callbacks args", "[Component][System]")
{
	int nbCallbacksCalled = 0;
	Wal wal;
	CollisionSystem collision(wal);
	MovableSystem movable(wal);

	wal.changeScene(std::make_shared<Scene>());

	wal.getScene()->addEntity("player")
		.addComponent<PositionComponent>()
	    .addComponent<MovableComponent>()
		.addComponent<CollisionComponent>(
			[&nbCallbacksCalled](Entity &actual, const Entity &other, int) {
				nbCallbacksCalled++;
				REQUIRE(actual.getName() == "player");
				REQUIRE(other.getName() == "block");
			},
			[&nbCallbacksCalled](Entity &actual, const Entity &other, int) {
				nbCallbacksCalled++;
				REQUIRE(other.getName() == "player");
				REQUIRE(actual.getName() == "block");
			}, 0, 5.0);

	wal.getScene()->addEntity("block")
		.addComponent<PositionComponent>(0, 0, 0)
	    .addComponent<MovableComponent>()
		.addComponent<CollisionComponent>(
			[&nbCallbacksCalled](Entity &actual, const Entity &other, int) {
				nbCallbacksCalled++;
				REQUIRE(other.getName() == "player");
				REQUIRE(actual.getName() == "block");
			},
			[&nbCallbacksCalled](Entity &actual, const Entity &other, int) {
				nbCallbacksCalled++;
				REQUIRE(actual.getName() == "player");
				REQUIRE(other.getName() == "block");
			}, 0, 1);
	Entity &entity = wal.getScene()->getEntities().front();
	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());

	entity.getComponent<CollisionComponent>().bound.x = 5;
	entity.getComponent<CollisionComponent>().bound.y = 5;
	entity.getComponent<CollisionComponent>().bound.z = 5;

	collision.update(std::chrono::nanoseconds(1));
	collision.fixedUpdate();
	REQUIRE(nbCallbacksCalled == 4);
}

TEST_CASE("Collision test callbacks args with only one movable entity", "[Component][System]")
{
	int nbCallbacksCalled = 0;
	Wal wal;
	CollisionSystem collision(wal);
	MovableSystem movable(wal);

	wal.changeScene(std::make_shared<Scene>());

	wal.getScene()->addEntity("player")
		.addComponent<PositionComponent>()
		.addComponent<MovableComponent>()
		.addComponent<CollisionComponent>(
			[&nbCallbacksCalled](Entity &actual, const Entity &other, int) {
				nbCallbacksCalled++;
				REQUIRE(actual.getName() == "player");
				REQUIRE(other.getName() == "block");
			},
			[&nbCallbacksCalled](Entity &actual, const Entity &other, int) {
				// lambda should not be called
				nbCallbacksCalled++;
				REQUIRE(other.getName() == "plfayer");
				REQUIRE(actual.getName() == "blofck");
			}, 0, 5.0);

	wal.getScene()->addEntity("block")
		.addComponent<PositionComponent>(0, 0, 0)
		.addComponent<CollisionComponent>(
			[&nbCallbacksCalled](Entity &actual, const Entity &other, int) {
				// lambda should not be called
				nbCallbacksCalled++;
				REQUIRE(other.getName() == "playefr");
				REQUIRE(actual.getName() == "blocfk");
			},
			[&nbCallbacksCalled](Entity &actual, const Entity &other, int) {
				nbCallbacksCalled++;
				REQUIRE(actual.getName() == "player");
				REQUIRE(other.getName() == "block");
			}, 0, 1);
	Entity &entity = wal.getScene()->getEntities().front();
	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());

	entity.getComponent<CollisionComponent>().bound.x = 5;
	entity.getComponent<CollisionComponent>().bound.y = 5;
	entity.getComponent<CollisionComponent>().bound.z = 5;

	collision.update(std::chrono::nanoseconds(1));
	collision.fixedUpdate();
	REQUIRE(nbCallbacksCalled == 2);
}

TEST_CASE("Vector round", "[Vector]")
{
	Vector3f v(1.3, 1.5, 1.7);
	REQUIRE(v.round() == Vector3f(1, 2, 2));
}