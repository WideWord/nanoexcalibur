#pragma once

#include "../util/Memory.hpp"
#include "../util/Math.hpp"

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
