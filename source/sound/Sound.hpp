#pragma once

#include <SFML/Audio.hpp>

namespace nexc {

	class Sound {
	public:
		void loadFromFile(const std::string& filename) {
			internal.loadFromFile(filename);
		}
	private:
		friend class SoundProcessing;
		sf::SoundBuffer internal;
	};

}
