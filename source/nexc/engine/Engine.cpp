#include "Engine.hpp"

namespace nexc {

	Engine::Engine(const Config& config) : window(config) {}

	void Engine::configure() {
		addChildSystem(&window, beginFrameQueue);
		addChildSystem(&rendering, endFrameQueue);
	}

	IVec2 Engine::getScreenSize() {
		return window.getSize();
	}

	Vec2 Engine::getMousePosition() {
		return window.getMousePosition();
	}

	bool Engine::getKey(int key) {
		return window.getKey(key);
	}

	bool Engine::getMouseButton(int button) {
		return window.getMouseButton(button);
	}

}
