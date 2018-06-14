#pragma once

#include "System.hpp"
#include "World.hpp"

namespace nexc {

	template<typename T>
	inline void AnySystem::subscribe(std::function<void(const T&)> callback) {
		world->eventsManager.subscribe(this, callback);
	}

	inline void AnySystem::addChildSystem(AnySystem* system, int32_t queue) {
		world->addSystem(system, queue);
		children.push_back(system);
	}

	template<typename T>
	inline T* AnySystem::getSystem() {
		return world->getSystem<T>();
	}

}
