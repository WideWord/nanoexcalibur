#pragma once

#include "../ecs/ecs.hpp"
#include <SFML/Window.hpp>

namespace nexc {

	class WindowEventsProcessing : public System {
	public:
		explicit WindowEventsProcessing(sf::Window& window) : window(window) {}

		void run() override;

	private:
		sf::Window& window;
	};

}
