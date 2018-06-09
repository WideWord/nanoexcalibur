#pragma once

#include "../ecs/ecs.hpp"
#include <SFML/System.hpp>

namespace nexc {

	class TimeManager : public System {
	public:

		void configure() override {
			clock.restart();
		}

		void run() override {
			deltaTime = clock.getElapsedTime().asSeconds();
			clock.restart();
		}

		float getDeltaTime() {
			return deltaTime;
		}

	private:
		float deltaTime;
		sf::Clock clock;
	};

}
