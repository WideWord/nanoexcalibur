#pragma once

#include "../ecs/ecs.hpp"
#include <SFML/Graphics.hpp>
#include "../gfx/Rendering.hpp"
#include "WindowEventsProcessing.hpp"
#include "AssetsManager.hpp"
#include "InputManager.hpp"
#include "TimeManager.hpp"
#include "../3rdparty/glad/glad.h"
#include "../util/Memory.hpp"

namespace nexc {

	class Engine : public System {
	public:
		Engine() {

			window = URef<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800 * 3, 600 * 3), "nano excalibur", sf::Style::Default, sf::ContextSettings(24, 8, 4, 3, 3)));

			gladLoadGL();

			rendering = URef<Rendering>(new Rendering(*window));
			windowEventsProcessing = URef<WindowEventsProcessing>(new WindowEventsProcessing(*window));
			assetsManager = URef<AssetsManager>(new AssetsManager());
			inputManager = URef<InputManager>(new InputManager(*window));
			timeManager = URef<TimeManager>(new TimeManager());

		}

		static constexpr int32_t beginFrameQueue = -1000000;
		static constexpr int32_t endFrameQueue = 1000000;

		void configure() override {
			addChildSystem(windowEventsProcessing.get(), beginFrameQueue);
			addChildSystem(timeManager.get(), beginFrameQueue);

			addChildSystem(rendering.get(), endFrameQueue);
		}

		AssetsManager& getAssetsManager() {
			return *assetsManager;
		}

		InputManager& getInputManager() {
			return *inputManager;
		}

		TimeManager& getTimeManager() {
			return *timeManager;
		}
	private:
		std::unique_ptr<sf::RenderWindow> window;
		std::unique_ptr<Rendering> rendering;
		std::unique_ptr<WindowEventsProcessing> windowEventsProcessing;
		std::unique_ptr<AssetsManager> assetsManager;
		std::unique_ptr<InputManager> inputManager;
		std::unique_ptr<TimeManager> timeManager;
	};

}

