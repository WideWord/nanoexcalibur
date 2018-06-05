#pragma once

#include <stdint.h>

namespace nanoecs {

	class PoorEntity {
	protected:
		friend class PoorWorld;
		uint32_t id;
		uint32_t generation;
	};

}
