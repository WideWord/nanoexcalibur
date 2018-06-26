#pragma once

#include <SFML/Graphics.hpp>
#include "../util/Memory.hpp"

namespace nexc {

	class AssetsManager;

	class Font {
	private:
		friend class AssetsManager;
		friend class Rendering;

		sf::Font internal;

		void loadFromFile(AssetsManager& assets, const std::string& filename) {
			internal.loadFromFile(filename);
		}
	};

	struct TextRenderer {
		Ref<Font> font;
		std::string text;
		float size;
		bool guiSpace;

		TextRenderer(Ref<Font> font = nullptr, std::string text = "", float size = 30) : font(font), text(text), size(size), guiSpace(false) {}
	};

}
