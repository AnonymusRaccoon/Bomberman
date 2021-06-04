//
// Created by Zoe Roux on 5/27/21.
//

#include <Component/Renderer/Drawable3DComponent.hpp>
#include "Models/Vector2.hpp"
#include "RenderSystem.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Drawables/ADrawable2D.hpp"
#include "Drawables/ADrawable3D.hpp"

namespace BBM
{
	RenderSystem::RenderSystem(WAL::Wal &wal, RAY::Window &window)
		: WAL::System({
			typeid(CameraComponent),
			typeid(PositionComponent)
		}),
		_wal(wal),
		_window(window),
		_camera(Vector3f(), Vector3f(), Vector3f(0, 1, 0), 50, CAMERA_PERSPECTIVE),
		_debugMode(true)
	{
		this->_window.setFPS(this->FPS);
	}

	void RenderSystem::onSelfUpdate()
	{
		this->_camera.update();
		this->_window.beginDrawing();
		this->_window.clear();

		this->_window.useCamera(this->_camera);
		for (auto &entity : this->_wal.scene->getEntities()) {
			if (!entity.hasComponent<Drawable3DComponent>()
			    || !entity.hasComponent<PositionComponent>())
				continue;
			auto &drawable = entity.getComponent<Drawable3DComponent>();
			auto &pos = entity.getComponent<PositionComponent>();

			drawable.drawable->setPosition(pos.position);
			drawable.drawable->drawOn(this->_window);
		}
		this->_window.unuseCamera();

		// TODO sort entities based on the Z axis
		for (auto &entity : this->_wal.scene->getEntities()) {
			if (!entity.hasComponent<Drawable2DComponent>()
		    || !entity.hasComponent<PositionComponent>())
				continue;
			auto &drawable = entity.getComponent<Drawable2DComponent>();
			auto &pos = entity.getComponent<PositionComponent>();

			drawable.drawable->setPosition(Vector2f(pos.position.x, pos.position.y));
			drawable.drawable->drawOn(this->_window);
		}
		if (this->_debugMode)
			this->_window.drawFPS(Vector2f());
		this->_window.endDrawing();
	}

	void RenderSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime)
	{
		const auto &pos = entity.getComponent<PositionComponent>();
		const auto &cam = entity.getComponent<CameraComponent>();
		_camera.setPosition(pos.position);
		_camera.setTarget(cam.target);
	}
}