#pragma once

#include "../ecs/ecs.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Sprite.hpp"

namespace nexc {

	class Rendering : public System {
	public:
		explicit Rendering(sf::RenderWindow& window) : window(window) {}

		void run() override;

	private:
		sf::RenderWindow& window;
	};

}
