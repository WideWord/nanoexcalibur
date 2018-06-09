#pragma once

#include "../ecs/ecs.hpp"
#include <SFML/Graphics.hpp>
#include "../gfx/Rendering.hpp"
#include "WindowEventsProcessing.hpp"
#include "AssetsManager.hpp"
#include "InputManager.hpp"
#include "TimeManager.hpp"

namespace nexc {

	class Engine : public System {
	public:
		Engine() : window(sf::VideoMode(800 * 3, 600 * 3), "nano excalibur"), rendering(window), windowEventsProcessing(window), inputManager(window) {}

		static constexpr int32_t beginFrameQueue = -1000000;
		static constexpr int32_t endFrameQueue = 1000000;

		void configure() override {
			addChildSystem(&windowEventsProcessing, beginFrameQueue);
			addChildSystem(&timeManager, beginFrameQueue);

			addChildSystem(&rendering, endFrameQueue);
		}

		AssetsManager& getAssetsManager() {
			return assetsManager;
		}

		InputManager& getInputManager() {
			return inputManager;
		}

		TimeManager& getTimeManager() {
			return timeManager;
		}
	private:
		sf::RenderWindow window;
		Rendering rendering;
		WindowEventsProcessing windowEventsProcessing;
		AssetsManager assetsManager;
		InputManager inputManager;
		TimeManager timeManager;
	};

}

