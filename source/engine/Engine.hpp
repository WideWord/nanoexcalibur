#pragma once

#include "../ecs/ecs.hpp"
#include "../util/Memory.hpp"

namespace nexc {

	class Rendering;
	class Window;
	class AssetsManager;

	class Engine : public System<Engine> {
	public:
		struct Config {
			uint32_t width;
			uint32_t height;
			bool fullscreen;
			std::string title;

			Config() {
				width = 800;
				height = 600;
				fullscreen = false;
				title = "nexc";
			}
		};

		explicit Engine(const Config& config = Config());
		void configure() override;

		AssetsManager& getAssetsManager() {
			return *(assetsManager.get());
		}

		static constexpr int32_t beginFrameQueue = -1000000;
		static constexpr int32_t endFrameQueue = 1000000;
	private:
		Ref<Window> window;
		Ref<Rendering> rendering;
		Ref<AssetsManager> assetsManager;
	};

}
