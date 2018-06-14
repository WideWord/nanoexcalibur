#include "Engine.hpp"
#include "../gfx/Rendering.hpp"

namespace nexc {

	Engine::Engine(const Config& config) : window(config.windowConfig) {
		rendering = New<Rendering>();
	}

	void Engine::configure() {
		addChildSystem(&window, beginFrameQueue);
		addChildSystem(rendering.get(), endFrameQueue);
	}





}
