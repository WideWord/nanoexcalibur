#pragma once

#include <stdint.h>

namespace nanoecs {

	class PoorEntity {
	protected:
		friend class PoorWorld;
		PoorEntity() : id(0), generation(0) {}
		PoorEntity(uint32_t id, uint32_t generation) : id(id), generation(generation) {}
		uint32_t id;
		uint32_t generation;
	};

}
