#pragma once

#include <vector>
#include "../util/Math.hpp"
#include "../util/Memory.hpp"


namespace nexc {

	class Texture;
	class AssetsManager;

	class Sprite {
	private:
		friend class AssetsManager;
		friend class Rendering;
		Ref<Texture> texture;
		IRect rect;
		Vec2 origin;
		float pixelsInUnit;

		void loadFromFile(AssetsManager& assets, const std::string& filename);
	};

	struct SpriteRenderer {
		Ref<Sprite> sprite;
		int32_t layer;
		bool guiSpace;

		SpriteRenderer(Ref<Sprite> sprite = nullptr, int32_t layer = 0) : sprite(std::move(sprite)), layer(layer), guiSpace(false) {}
	};

}
