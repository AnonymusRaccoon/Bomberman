//
// Created by Louis Auzuret 06/03/21
//

#include <algorithm>
#include "Component/Button/ButtonComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	MenuControllableSystem::MenuControllableSystem(WAL::Wal &wal)
		: System(wal), wal(wal), currentButton()
	{}

	void MenuControllableSystem::updateCurrentButton()
	{
		auto buttonComponent = this->currentButton->getComponent<OnClickComponent>();
		if (move.y > 0 && buttonComponent._up)
			this->currentButton = buttonComponent._up;
		if (move.y < 0 && buttonComponent._down)
			this->currentButton = buttonComponent._down;
		if (move.x < 0 && buttonComponent._right)
			this->currentButton = buttonComponent._right;
		if (move.x > 0 && buttonComponent._left)
			this->currentButton = buttonComponent._left;
		
	}

	void MenuControllableSystem::onFixedUpdate(WAL::ViewEntity<ControllableComponent> &entity)
	{
		auto lastTick = std::chrono::steady_clock::now(); 
		auto &controllable = entity.get<ControllableComponent>();
		auto &buttons = _wal.scene->view<OnClickComponent, OnHoverComponent, OnIdleComponent>();
		
		if (lastTick - this->_now < std::chrono::milliseconds(100))
			return;
		this->_now = lastTick;

		move = controllable.move;
		select = controllable.jump;
		if (currentButton && currentButton->_scene.getID() != wal.scene->getID())
			currentButton = nullptr;
		if (currentButton == nullptr && buttons.size())
			currentButton = &(**buttons.begin());
		if (!currentButton)
			return;
		this->updateCurrentButton();
		for (auto &[buttonEntity, clickComponent, hoverComponent, idleComponent]: buttons) {
			if (buttonEntity == *currentButton) {
				hoverComponent.onEvent(buttonEntity, wal);
				if (select)
					clickComponent.onEvent(buttonEntity, wal);
				continue;
			}
			idleComponent.onEvent(buttonEntity, wal);
		}
	}

	void MenuControllableSystem::onSelfUpdate(void)
	{

	}
}