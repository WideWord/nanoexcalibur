#pragma once

#include "System.hpp"
#include "World.hpp"

namespace nexc {

	template<typename T>
	inline void System::subscribe(std::function<void(const T&)> callback) {
		world->eventsManager.subscribe(this, callback);
	}

	inline void System::addChildSystem(System* system, int32_t queue) {
		world->addSystem(system, queue);
		children.push_back(system);
	}

}
