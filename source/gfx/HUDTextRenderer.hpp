#pragma once

#include <string>
#include "../util/Math.hpp"

namespace nexc {

	class Font;

	struct HUDTextRenderer {
		std::string text;
		std::shared_ptr<Font> font;
		uint32_t size = 30;
		IVec2 position;
		int16_t layer = 0;
	};

}
