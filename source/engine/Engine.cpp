#include "Engine.hpp"
#include "../gfx/Rendering.hpp"
#include "Window.hpp"
#include "AssetsManager.hpp"
#include "../common/GUI.hpp"

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
		gui = New<GUI>();
	}

	void Engine::configure() {
		addChildSystem(window.get(), beginFrameQueue);
		addChildSystem(gui.get(), endFrameQueue);
		addChildSystem(rendering.get(), endFrameQueue);
	}

	IVec2 Engine::getScreenSize() {
		return window->getSize();
	}

	Vec2 Engine::getMousePosition() {
		return window->getMousePosition();
	}

	bool Engine::getKey(KeyCode key) {
		return window->getKey(key);
	}

	bool Engine::getMouseButton(int button) {
		return window->getMouseButton(button);
	}

}
