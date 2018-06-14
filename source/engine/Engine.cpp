#include "Engine.hpp"
#include "../gfx/Rendering.hpp"
#include "Window.hpp"
#include "AssetsManager.hpp"

namespace nexc {

	Engine::Engine(const Config& config) {
		Window::Config windowConfig;
		windowConfig.width = config.width;
		windowConfig.height = config.height;
		windowConfig.fullscreen = config.fullscreen;
		windowConfig.title = config.title;
		window = New<Window>(windowConfig);
		rendering = New<Rendering>();
		assetsManager = New<AssetsManager>();
	}

	void Engine::configure() {
		addChildSystem(window.get(), beginFrameQueue);
		addChildSystem(rendering.get(), endFrameQueue);
	}

}
