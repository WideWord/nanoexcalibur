#include "QueryList.hpp"
#include "World.hpp"
#include "Entity.hpp"

namespace nexc {

	QueryIterator QueryList::begin() {
		for (uint32_t e = 0; e < maxEntitiesNum; ++e) {
			if ((mask & world->mask[e]) == mask) {
				return QueryIterator(world, e, mask);
			}
		}
		return QueryIterator(world, maxEntitiesNum, mask);
	}

	inline void QueryIterator::operator++() {
		while (true) {
			entity += 1;
			if (entity == maxEntitiesNum) break;
			if ((mask & world->mask[entity]) == mask) break;
		}
	}

	inline Entity QueryIterator::operator*() {
		Entity e;
		e.id = entity;
		e.generation = world->generation[e.id];
		e.world = world;
		return e;
	}

}
