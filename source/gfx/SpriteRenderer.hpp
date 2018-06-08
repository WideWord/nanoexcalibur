#pragma once

#include <memory>

namespace nexc {

	class Sprite;

	struct SpriteRenderer {
		std::shared_ptr<Sprite> sprite;

		SpriteRenderer() = default;
		explicit SpriteRenderer(std::shared_ptr<Sprite> sprite) : sprite(std::move(sprite)) {}
	};

}
