#pragma once

#include "Entity.hpp"
#include "World.hpp"

namespace nexc {

	bool Entity::isAlive() const {
		return world->generation[id] == generation;
	}

}
