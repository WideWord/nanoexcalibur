#include "ecs/ecs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common/Transform2D.hpp"
#include "gfx/Rendering.hpp"
#include "gfx/Camera2D.hpp"
#include "gfx/HUDTextRenderer.hpp"
#include "gfx/SpriteRenderer.hpp"
#include "engine/Engine.hpp"
#include "util/PerformanceMeasurement.hpp"

using namespace nexc;


struct Player {};

class PlayerMovement : public System {
public:
	explicit PlayerMovement(Engine& engine) : engine(engine) {}

	void run() override {
		for (auto e : getWorld()->getEntitiesWith<Player, Transform2D>()) {

			auto transform = e.get<Transform2D>();

			Vec2 movement;

			if (engine.getInputManager().getKey(KeyCode::A)) {
				movement.x -= 1;
			}

			if (engine.getInputManager().getKey(KeyCode::D)) {
				movement.x += 1;
			}

			if (engine.getInputManager().getKey(KeyCode::W)) {
				movement.y -= 1;
			}

			if (engine.getInputManager().getKey(KeyCode::S)) {
				movement.y += 1;
			}

			transform.position += movement * engine.getTimeManager().getDeltaTime();

			e.set(transform);
		}
	}

private:
	Engine& engine;
};

int main() {

	World world;

	Engine engine;

	PlayerMovement playerMovement(engine);
	PerformanceMeasurement framePerformanceHandling(engine);

	world.addSystem(&engine);
	world.addSystem(&playerMovement);
	world.addSystem(&framePerformanceHandling);

	auto sprite = std::make_shared<Sprite>();
	sprite->texture = engine.getAssetsManager().getTexture("data/test.jpg");
	sprite->rect = IRect(0, 0, 300, 300);
	sprite->pivot = Vec2(328, 328);

	sprite->pixelsInUnit = 656;

	world.createEntity()
			.set(Transform2D())
			.set(SpriteRenderer(sprite))
			.set(Player());

	world.createEntity()
			.set(Transform2D())
			.set(Camera2D());

	while (true) {
		world.update();
	}

	return 0;
}