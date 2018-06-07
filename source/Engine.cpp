#include "Engine.hpp"

namespace nexc {

	void Engine::configure() {
		addChildSystem(&windowEventsProcessing, beginFrameQueue);

		addChildSystem(&rendering, endFrameQueue);
	}

}
