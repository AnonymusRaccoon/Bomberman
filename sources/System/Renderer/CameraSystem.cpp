//
// Created by Tom Augier on 05/06/2021
//

#include "CameraSystem.hpp"
#include "Entity/Entity.hpp"
#include "Component/Tag/TagComponent.hpp"

namespace BBM
{
	CameraSystem::CameraSystem(WAL::Wal &wal)
		: System(wal)
	{}

	bool CameraSystem::introAnimation(WAL::ViewEntity<CameraComponent, PositionComponent> &entity, bool restart)
	{	
		auto &pos = entity.get<PositionComponent>();
		static Vector3f posTarget(8, 25, 7);
		static bool hasEnded = false;

		if (restart) {
			hasEnded = false;
			return (false);
		}
		if (pos.position.distance(posTarget) < 4 || hasEnded) {
			hasEnded = true;
			return (true);
		}

		auto &cam = entity.get<CameraComponent>();

		pos.position += (posTarget - pos.position) / 100;
		return (false);
	}

	void CameraSystem::onUpdate(WAL::ViewEntity<CameraComponent, PositionComponent> &entity,
	                            std::chrono::nanoseconds dtime)
	{
		if (!introAnimation(entity))
			return;
		auto &pos = entity.get<PositionComponent>();
		auto &cam = entity.get<CameraComponent>();
		Vector3f newCameraPos = Vector3f(-1, -1, -1);
		std::vector<Vector3f> playerPos;
		float maxDist = 0;
		float lowerXDist = 0;
		float lowerZDist = 0;

		for (auto &[entity, pos, _] : this->_wal.getScene()->view<PositionComponent, TagComponent<Player>>()) {
			if (!entity.hasComponent<ControllableComponent>())
				entity.addComponent<ControllableComponent>();
			playerPos.emplace_back(pos.position);
		}
		if (playerPos.size() == 0)
			introAnimation(entity, true);
		if (playerPos.size() == 1)
			newCameraPos = playerPos[0];
		for (int i = 0; i < playerPos.size(); i++)
			for (int j = 0; j < playerPos.size(); j++) {
				if (maxDist < playerPos[i].distance(playerPos[j])) {
					maxDist = playerPos[i].distance(playerPos[j]);
					newCameraPos = (playerPos[i] + playerPos[j]) / 2;
				}
				if (lowerXDist < std::abs((playerPos[i].x - playerPos[j].x)))
					lowerXDist = std::abs((playerPos[i].x - playerPos[j].x));
				if (lowerZDist < std::abs((playerPos[i].z - playerPos[j].z)))
					lowerZDist = std::abs((playerPos[i].z - playerPos[j].z));
			}
		maxDist += (lowerXDist  + lowerZDist) / 2;
		if (maxDist < 14)
			maxDist = 14;
		if (maxDist > 25)
			maxDist = 25;
		cam.target += (newCameraPos.abs() - pos.position.abs()) / 10;
		newCameraPos.y = maxDist;
		newCameraPos.z -= 1;
		Vector3f pos2d(pos.position.abs().x,0, pos.position.abs().z);
		Vector3f newPos2d(newCameraPos.abs().x, 0, pos.position.abs().z);
		for (auto &[entity, backPos, _] : this->_wal.getScene()->view<PositionComponent, TagComponent<Background>>()) {
			backPos.position -= (newPos2d - pos2d) / 10;
		}
		pos.position += (newCameraPos.abs() - pos.position.abs()) / 10;

	}
}