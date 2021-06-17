//
// Created by Louis Auzuret 06/03/21
//

#include <algorithm>
#include "Component/Button/ButtonComponent.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"
#include "Drawables/Texture.hpp"
#include "Drawables/2D/Text.hpp"
#include "Controllers/Mouse.hpp"

namespace RAYControl = RAY::Controller;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	MenuControllableSystem::MenuControllableSystem(WAL::Wal &wal)
		: System(wal),
		_currentButton()
	{}

	void MenuControllableSystem::_updateCurrentButton(bool selected, Vector2f move)
	{
		auto &buttonComponent = this->_currentButton->getComponent<OnClickComponent>();
		WAL::Entity *newButton = nullptr; 

		if (move.y > 0 && buttonComponent._up)
			newButton = buttonComponent._up;
		if (move.y < 0 && buttonComponent._down)
			newButton = buttonComponent._down;
		if (move.x < 0 && buttonComponent._right)
			newButton = buttonComponent._right;
		if (move.x > 0 && buttonComponent._left)
			newButton = buttonComponent._left;

		if (newButton || selected) {
			auto lastTick = std::chrono::steady_clock::now();
			if (lastTick - this->now < std::chrono::milliseconds(150))
				return;
			this->now = lastTick;
		}

		if (newButton) {
			this->_currentButton->getComponent<OnIdleComponent>().onEvent(*this->_currentButton, this->_wal);
			this->_currentButton = newButton;
			this->_currentButton->getComponent<OnHoverComponent>().onEvent(*this->_currentButton, this->_wal);
		}
		if (selected)
		    this->_currentButton->getComponent<OnClickComponent>().onEvent(*this->_currentButton, this->_wal);
	}

	bool MenuControllableSystem::_mouseOnButton(WAL::ViewEntity<OnClickComponent, OnHoverComponent, OnIdleComponent, PositionComponent, Drawable2DComponent> &entity) const
	{
		auto &positionComponent = entity.get<PositionComponent>();
		RAY::Vector2 rayMousePos = RAYControl::Mouse::getCursorPosition();
		RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.get<Drawable2DComponent>().drawable.get());
		RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(entity.get<Drawable2DComponent>().drawable.get());
		Vector2f buttonPos(positionComponent.getX(), positionComponent.getY());
		Vector2f mousePos(rayMousePos.x, rayMousePos.y);
		Vector2f dimensions;

		WAL::Entity *newButton = nullptr; 

		if (texture) {
			dimensions.x = texture->getDimensions().x;
			dimensions.y = texture->getDimensions().y;
		} else if (text) {
			dimensions.y = text->getFontSize();
			dimensions.x = text->getString().size() * (text->getLetterSpacing() + text->getFontSize());
		} else
			return false;
		return ((buttonPos.x <= mousePos.x && mousePos.x <= buttonPos.x + dimensions.x)
		&& (buttonPos.y <= mousePos.y && mousePos.y <= buttonPos.y + dimensions.y));
	}

	void MenuControllableSystem::onSelfUpdate()
	{

		auto &controllableView = this->_wal.getScene()->view<ControllableComponent>();
		auto &buttons = _wal.getScene()->view<OnClickComponent, OnHoverComponent, OnIdleComponent, PositionComponent, Drawable2DComponent>();


		if (this->_currentButton && this->_currentButton->_scene.getID() != this->_wal.getScene()->getID()) {
			this->_currentButton->getComponent<OnIdleComponent>().onEvent(*this->_currentButton, this->_wal);
			this->_currentButton = nullptr;
			return;
		}
		if (this->_currentButton == nullptr && buttons.size()) {
			this->_currentButton = &(*buttons.front());
			this->_currentButton->getComponent<OnHoverComponent>().onEvent(*this->_currentButton, this->_wal);
		}
		if (!this->_currentButton)
			return;
		for (auto &[_, controllable]: controllableView)
			if (controllable.move.x || controllable.move.y || controllable.select) {
				this->_updateCurrentButton(controllable.select, controllable.move);
				return;
			}
		for (auto &entity:  buttons) {
			if (_mouseOnButton(entity)) {
				if (this->_currentButton)
					this->_currentButton->getComponent<OnIdleComponent>().onEvent(*this->_currentButton, this->_wal);
				this->_currentButton = &(*entity);
				this->_currentButton->getComponent<OnHoverComponent>().onEvent(*this->_currentButton, this->_wal);
				if (RAYControl::Mouse::isPressed(RAYControl::Mouse::Button::MOUSE_BUTTON_LEFT))
					this->_currentButton->getComponent<OnClickComponent>().onEvent(*this->_currentButton, this->_wal);
			}
		}
	}
}