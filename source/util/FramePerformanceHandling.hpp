#pragma once

#include "../ecs/ecs.hpp"
#include "../gfx/HUDTextRenderer.hpp"
#include "../Engine.hpp"
#include "../util/MakeString.hpp"

namespace nexc {

	class FramePerformanceHandling : public System {
	public:
		explicit FramePerformanceHandling(Engine& engine) : engine(engine) {}

		void configure() override {
			statsText = getWorld()->createEntity();
			HUDTextRenderer text;
			text.font = engine.getAssetsManager().getFont("data/Arial.ttf");
			statsText.set(text);
		}

		void shutdown() override {
			getWorld()->destroyEntity(statsText);
		}

		void run() override {
			auto deltaTime = engine.getTimeManager().getDeltaTime();

			dropPeakTime -= deltaTime;
			if (dropPeakTime <= 0) {
				dropPeakTime = 3.0f;
				peakTime = 0.0f;
			}

			if (deltaTime > peakTime) peakTime = deltaTime;

			auto text = statsText.get<HUDTextRenderer>();
			text.text = MakeString() << "Frame time: " << std::ceil(deltaTime * 1000.0f) << " ms\n"
				<< "Peak frame time: " << std::ceil(peakTime * 1000.0f) << " ms";

			statsText.set(text);
		}
	private:
		Engine& engine;
		Entity statsText;
		float peakTime = 0;
		float dropPeakTime = 3;
	};

}
