//
// Created by Zoe Roux on 6/11/21.
//

#include <Component/Animation/AnimationsComponent.hpp>
#include <System/Event/EventSystem.hpp>
#include <Component/Renderer/Drawable2DComponent.hpp>
#include "System/Lobby/LobbySystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include <algorithm>

namespace BBM
{
	LobbySystem::LobbySystem(WAL::Wal &wal)
		: System(wal)
	{}

	void LobbySystem::onUpdate(WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &lobby = entity.get<LobbyComponent>();
		if (lobby.layout == ControllableComponent::NONE) {
			for (auto &[_, controller] : this->_wal.getScene()->view<ControllableComponent>()) {
				if (controller.jump) {
					if (std::any_of(this->getView().begin(), this->getView().end(), [&controller](WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &view) {
						return view.get<LobbyComponent>().layout == controller.layout;
					}))
						return;
					lobby.layout = controller.layout;
					entity.get<Drawable2DComponent>().drawable = std::make_shared<RAY::Texture>("assets/player/icons/blue.png");
					return;
				}
			}
		}
		for (auto &[_, controller] : this->_wal.getScene()->view<ControllableComponent>()) {
			if (controller.layout == lobby.layout && controller.jump) {
				lobby.ready = !lobby.ready;
				if (lobby.ready) {
				}
			}
		}
	}

	//void LobbySystem::updateEntityConnectedUser(WAL::Entity &entity)
	//{
	//	RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
	//	texture->use("assets/player/icons/blue.png");
	//}
}