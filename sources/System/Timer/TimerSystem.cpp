//
// Created by Zoe Roux on 5/31/21.
//

#include "TimerSystem.hpp"
#include "Component/Timer/TimerComponent.hpp"

using namespace std::chrono_literals;

namespace BBM
{
	TimerSystem::TimerSystem()
		: WAL::System({
			typeid(TimerComponent)
		})
	{}

	void TimerSystem::onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime)
	{
		auto &timer = entity.getComponent<TimerComponent>();
		timer.ringIn -= dtime;
		if (timer.ringIn <= 0ns) {
			timer.setDisable(true);
			timer.callback(entity);
		}
	}
}