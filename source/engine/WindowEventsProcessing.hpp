#pragma once

#include "../ecs/ecs.hpp"
#include <SFML/Window.hpp>

namespace nexc {

	class WindowEventsProcessing : public System {
	public:
		explicit WindowEventsProcessing(sf::Window& window) : window(window) {}

		void run() override {
			sf::Event e;
			while (window.pollEvent(e)) {

			}
		}

	private:
		sf::Window& window;
	};

}
