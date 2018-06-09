#pragma once

#include <memory>
#include "../util/Math.hpp"
#include "../util/Memory.hpp"

namespace nexc {

	class Texture;

	class Sprite {
	public:
		Ref<Texture> texture;
		float pixelsInUnit;
		IRect rect;
		Vec2 pivot;
	};

}
