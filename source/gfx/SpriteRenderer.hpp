#pragma once

#include <memory>

namespace nexc {

	class Sprite;

	struct SpriteRenderer {
		std::shared_ptr<Sprite> sprite;
		int16_t layer = 0;

		SpriteRenderer() = default;
		explicit SpriteRenderer(std::shared_ptr<Sprite> sprite, int16_t layer = 0) : sprite(std::move(sprite)), layer(layer) {}
	};

}