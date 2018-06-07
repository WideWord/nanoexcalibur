#pragma once

#include "Config.hpp"
#include <bitset>

namespace nexc {

	class Entity;

	class World {
	public:
		inline World();
		inline Entity createEntity();
		inline void destroyEntity(const Entity& e);
	private:
		friend class Entity;

		uint32_t firstFree;
		uint32_t nextFree[maxEntitiesNum];
		uint32_t generation[maxEntitiesNum];

		std::bitset<maxComponentTypesNum> mask[maxEntitiesNum];

	};

}
