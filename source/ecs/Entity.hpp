#pragma once

#include <stdint.h>

namespace nexc {

	class World;

	class Entity {
	public:
		inline bool isAlive() const;

		template<typename T>
		inline void set(const T& value);

		template<typename T>
		inline T get();

		template<typename T>
		inline void remove();

	private:
		friend class World;
		friend class QueryIterator;
		uint32_t id;
		uint32_t generation;
		World* world;
	};

}
