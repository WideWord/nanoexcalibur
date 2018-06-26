#pragma once

#include "../ecs/ecs.hpp"
#include <bgfx/bgfx.h>

namespace nexc {

	class Rendering : public System<Rendering> {
	public:
		void run() override;
	private:
	};

}
