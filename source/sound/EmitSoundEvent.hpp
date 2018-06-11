#pragma once

#include "../util/Memory.hpp"
#include "../util/Math.hpp"

namespace nexc {

	class Sound;

	struct EmitSoundEvent {
		Ref<Sound> sound;
	};

}

