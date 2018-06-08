#pragma once

#include "Config.hpp"
#include <bitset>

namespace nexc {

	class World;
	class Entity;
	class AnyComponentStorage;

	class QueryIterator {
	public:
		inline void operator++();
		inline Entity operator*();

		bool operator!=(const QueryIterator& o) {
			return iid != o.iid;
		}

	private:
		friend class QueryList;
		QueryIterator(World* world, AnyComponentStorage* storage, uint32_t iid, std::bitset<maxComponentTypesNum> mask)
				: world(world),
				  storage(storage),
				  iid(iid),
				  mask(mask) {}
		World* world;
		AnyComponentStorage* storage;
		uint32_t iid;
		std::bitset<maxComponentTypesNum> mask;
	};

	class QueryList {
	public:
		inline QueryIterator begin();

		QueryIterator end() {
			return QueryIterator(world, storage, maxEntitiesNum, mask);
		}
	private:
		friend class World;

		QueryList(World* world, AnyComponentStorage* storage, std::bitset<maxComponentTypesNum> mask)
				: world(world),
				  storage(storage),
				  mask(mask) {}

		World* world;
		AnyComponentStorage* storage;
		std::bitset<maxComponentTypesNum> mask;
	};

}
