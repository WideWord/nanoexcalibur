#pragma once

#include "../util/Memory.hpp"

namespace nexc {

	class Sprite;

	struct SpriteRenderer {
		Ref<Sprite> sprite;
		int32_t layer;

		SpriteRenderer(Ref<Sprite> sprite = nullptr, int32_t layer = 0) : sprite(std::move(sprite)), layer(layer) {}
	};

}
