#include "QueryList.hpp"
#include "World.hpp"
#include "Entity.hpp"

namespace nexc {

	QueryIterator QueryList::begin() {
		for (uint32_t iid = 0; iid < storage->getAliveNum(); ++iid) {
			auto e = storage->entityId[iid];
			if (e == maxEntitiesNum) continue;

			if ((mask & world->mask[e]) == mask) {
				return QueryIterator(world, storage, iid, mask);
			}
		}
		return QueryIterator(world, storage, maxEntitiesNum, mask);
	}

	inline void QueryIterator::operator++() {
		while (true) {
			iid += 1;
			if (iid >= storage->getAliveNum() || iid == maxEntitiesNum) {
				iid = maxEntitiesNum;
				break;
			}
			auto e = storage->entityId[iid];
			if (e == maxEntitiesNum) continue;
			if ((mask & world->mask[e]) == mask) break;
		}
	}

	inline Entity QueryIterator::operator*() {
		Entity e;
		e.id = storage->entityId[iid];
		e.generation = world->generation[e.id];
		e.world = world;
		return e;
	}

}
