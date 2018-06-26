#include <SFML/Audio.hpp>

namespace nexc {

	class AssetsManager;

	class Sound {
	private:
		friend class AssetsManager;
		friend class Engine;

		void loadFromFile(AssetsManager& assets, const std::string& filename) {
			internal.loadFromFile(filename);
		}

		sf::SoundBuffer internal;
	};

}
