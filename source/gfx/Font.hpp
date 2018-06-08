#pragma once

#include <SFML/Graphics/Font.hpp>

namespace nexc {

	class Font {
	public:
		void loadFromFile(const std::string& filename) {
			internal.loadFromFile(filename);
		}
	private:
		friend class Rendering;
		sf::Font internal;
	};

}