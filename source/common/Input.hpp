#pragma once

#include "../ecs/ecs.hpp"

namespace nexc {

	class Input : public System<Input> {
	public:
		void run() override;
	};

}
