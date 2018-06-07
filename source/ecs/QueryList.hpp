#pragma once

#include "Config.hpp"
#include <bitset>

namespace nexc {

	class World;
	class Entity;

	class QueryIterator {
	public:
		inline void operator++();
		inline Entity operator*();

		bool operator!=(const QueryIterator& o) {
			return entity != o.entity;
		}

	private:
		friend class QueryList;
		QueryIterator(World* world, uint32_t entity, std::bitset<maxComponentTypesNum> mask) : world(world), entity(entity), mask(mask) {}
		World* world;
		uint32_t entity;
		std::bitset<maxComponentTypesNum> mask;
	};

	class QueryList {
	public:
		inline QueryIterator begin();

		QueryIterator end() {
			return QueryIterator(world, maxEntitiesNum, mask);
		}
	private:
		friend class World;
		QueryList(World* world, std::bitset<maxComponentTypesNum> mask) : world(world), mask(mask) {}
		World* world;
		std::bitset<maxComponentTypesNum> mask;
	};

}
