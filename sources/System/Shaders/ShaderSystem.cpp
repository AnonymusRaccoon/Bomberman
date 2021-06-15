//
// Created by cbihan on 15/06/2021.
//

#include "ShaderSystem.hpp"


namespace BBM
{
	ShaderSystem::ShaderSystem(WAL::Wal &wal)
		: System(wal)
	{
	}

	void ShaderSystem::onUpdate(WAL::ViewEntity<ShaderComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &shader = entity->getComponent<ShaderComponent>();

		shader.update(entity, this->_wal, dtime);
	}
}