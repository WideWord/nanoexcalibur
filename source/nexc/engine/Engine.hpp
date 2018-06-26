#pragma once

#include "../ecs/ecs.hpp"
#include "../util/Memory.hpp"
#include "../util/Math.hpp"
#include "AssetsManager.hpp"
#include "Window.hpp"
#include "../gfx/Rendering.hpp"

namespace nexc {

	class Rendering;
	class Window;
	class AssetsManager;

	class Engine : public System<Engine> {
	public:
		using Config = Window::Config;

		explicit Engine(const Config& config = Config());
		void configure() override;

		AssetsManager& getAssetsManager() {
			return assetsManager;
		}


		IVec2 getScreenSize();
		Vec2 getMousePosition();
		bool getKey(int key);
		bool getMouseButton(int button);
		void play(const Ref<Sound>& sound) {
			sf::Sound s(sound->internal);
			s.play();
		}
		float getDeltaTime() {
			return window.getDeltaTime();
		}

		static constexpr int32_t beginFrameQueue = -1000000;
		static constexpr int32_t endFrameQueue = 1000000;
	private:
		Window window;
		Rendering rendering;
		AssetsManager assetsManager;
	};

}
