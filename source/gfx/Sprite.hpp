#pragma once

#include <memory>
#include "../util/Math.hpp"

namespace nexc {

	class Texture;

	class Sprite {
	public:
		std::shared_ptr<Texture> texture;
		float pixelsInUnit;
		IRect rect;
		Vec2 pivot;
	};

}
