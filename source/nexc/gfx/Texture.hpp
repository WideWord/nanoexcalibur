#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace nexc {

	class AssetsManager;

	class Texture {
	private:
		friend class Rendering;
		friend class AssetsManager;

		sf::Texture internal;

		void loadFromFile(AssetsManager& assets, const std::string& filename) {
			internal.loadFromFile(filename);
		}

	};

}
