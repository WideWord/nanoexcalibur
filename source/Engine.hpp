#pragma once

#include "ecs/ecs.hpp"
#include <SFML/Graphics.hpp>
#include "gfx/Rendering.hpp"
#include "util/WindowEventsProcessing.hpp"
#include "util/AssetsManager.hpp"

namespace nexc {

	class Engine : public System {
	public:
		Engine() : window(sf::VideoMode(800 * 3, 600 * 3), "nano excalibur"), rendering(window), windowEventsProcessing(window) {}

		void configure() override;

		static constexpr int32_t beginFrameQueue = -1000000;
		static constexpr int32_t endFrameQueue = 1000000;

		AssetsManager* getAssetsManager() {
			return &assetsManager;
		}
	private:
		sf::RenderWindow window;
		Rendering rendering;
		WindowEventsProcessing windowEventsProcessing;
		AssetsManager assetsManager;
	};

}

