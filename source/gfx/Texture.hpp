#pragma once

#include <SFML/Graphics.hpp>

namespace nexc {

	class Texture {
	public:
		void loadFromFile(const std::string& filename) {
			internal.loadFromFile(filename);
		}
	private:
		friend class Rendering;
		sf::Texture internal;
	};

}
