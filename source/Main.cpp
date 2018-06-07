#include "ecs/ecs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common/Transform2D.hpp"
#include "gfx/Rendering.hpp"
#include "Engine.hpp"

using namespace nexc;


int main() {

	World world;

	Engine engine;

	world.addSystem(&engine);

	auto sprite = std::make_shared<Sprite>();
	sprite->texture = engine.getAssetsManager()->getTexture("data/test.jpg");
	sprite->textureSize = glm::vec2(656, 657);
	sprite->pixelsInUnit = 100;

	auto obj = world.createEntity();
	SpriteRenderer sr;
	sr.sprite = sprite;
	obj.set(sr);
	obj.set(Transform2D());

	while (true) {
		world.update();
	}

	return 0;
}