#pragma once

#include <memory>
#include "../util/Math.hpp"

namespace nexc {

	class Sprite;

	struct HUDImageRenderer {
		std::shared_ptr<Sprite> sprite;
		IRect frame;
		int16_t layer = 10000;

		HUDImageRenderer() = default;
	};

}
