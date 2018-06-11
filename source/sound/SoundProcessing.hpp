#pragma once

#include "../ecs/ecs.hpp"

namespace nexc {

	class SoundProcessing : public System {
	public:
		void configure() override;
	};

}
