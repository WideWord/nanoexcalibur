#pragma once

#include "World.hpp"
#include "Entity.hpp"

namespace nexc {

	World::World() {
		firstFree = 0;
		for (uint32_t i = 0; i < maxEntitiesNum; ++i) {
			nextFree[i] = i + 1;
			generation[i] = 0;
			mask[i] &= 0;
		}
	}

	Entity World::createEntity() {
		Entity e;
		e.world = this;
		e.id = firstFree;
		firstFree = nextFree[firstFree];
		e.generation = generation[e.id];
		return e;
	}

	void World::destroyEntity(const Entity& e) {
		if (!e.isAlive()) return;
		nextFree[e.id] = firstFree;
		firstFree = e.id;
		generation[e.id] += 1;
	}

}
