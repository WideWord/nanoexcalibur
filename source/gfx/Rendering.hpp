#pragma once

#include "../ecs/ecs.hpp"

namespace nexc {

	class Rendering : public System<Rendering> {
	public:
		Rendering();
		void run() override;
	};

}
