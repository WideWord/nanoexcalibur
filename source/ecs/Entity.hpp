#pragma once

#include <stdint.h>

namespace nexc {

	class World;

	class Entity {
	public:
		inline bool isAlive() const;
	private:
		friend class World;
		uint32_t id;
		uint32_t generation;
		World* world;
	};

}
