#include "ecs/ecs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common/Transform2D.hpp"
#include "gfx/Rendering.hpp"
#include "gfx/Camera2D.hpp"
#include "gfx/HUDTextRenderer.hpp"
#include "gfx/SpriteRenderer.hpp"
#include "engine/Engine.hpp"
#include "util/FramePerformanceHandling.hpp"
#include "gfx/Sprite.hpp"

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
				movement.y += 1;
			}

			if (engine.getInputManager().getKey(KeyCode::S)) {
				movement.y -= 1;
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
	FramePerformanceHandling framePerformanceHandling(engine);

	world.addSystem(&engine);
	world.addSystem(&playerMovement);
	world.addSystem(&framePerformanceHandling);

	auto sprite = std::make_shared<Sprite>();
	sprite->texture = engine.getAssetsManager().getTexture("data/test.jpg");
	sprite->rect = IRect(0, 0, 656, 656);
	sprite->pivot = Vec2(328, 328);

	sprite->pixelsInUnit = 656;

	world.createEntity()
			.set(Transform2D())
			.set(SpriteRenderer(sprite))
			.set(Player());

	auto hudImage = HUDImageRenderer();
	hudImage.sprite = sprite;
	hudImage.frame = IRect(0, 0, 50, 100);
	world.createEntity()
			.set(hudImage);

	auto sand = std::make_shared<Sprite>();
	sand->texture = engine.getAssetsManager().getTexture("data/sand.jpg");
	sand->rect = IRect(0, 0, 50, 50);
	sand->pixelsInUnit = 100;

	world.createEntity()
			.set(Transform2D())
			.set(SpriteRenderer(sand));

	/*for (int i = 0; i < 1000; ++i) {
		world.createEntity()
				.set(Transform2D())
				.set(SpriteRenderer(sprite));
	}*/

	world.createEntity()
			.set(Transform2D())
			.set(Camera2D());

	while (true) {
		world.update();
	}

	return 0;
}