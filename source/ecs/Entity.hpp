#pragma once

#include <stdint.h>
#include "Config.hpp"

namespace nexc {

	class World;

	class Entity {
	public:
		Entity() {
			id = maxEntitiesNum;
			generation = 0;
			world = nullptr;
		}

		inline bool isAlive() const;

		template<typename T>
		inline Entity& set(const T& value);

		template<typename T>
		inline T get();

		template<typename T>
		inline Entity& remove();

		template<typename T>
		inline bool has();

	private:
		friend class World;
		friend class QueryIterator;
		uint32_t id;
		uint32_t generation;
		World* world;
	};

}
