#pragma once

#include "../ecs/ecs.hpp"
#include "Window.hpp"
#include "../util/Memory.hpp"

namespace nexc {

	class Rendering;

	class Engine : public System<Engine> {
	public:
		struct Config {
			Window::Config windowConfig;
		};

		explicit Engine(const Config& config = Config());
		void configure() override;

		static constexpr int32_t beginFrameQueue = -1000000;
		static constexpr int32_t endFrameQueue = 1000000;
	private:
		Window window;
		Ref<Rendering> rendering;
	};

}
