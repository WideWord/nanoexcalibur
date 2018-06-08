#include "ecs/ecs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common/Transform2D.hpp"
#include "gfx/Rendering.hpp"
#include "gfx/Camera2D.hpp"
#include "gfx/HUDTextRenderer.hpp"
#include "gfx/SpriteRenderer.hpp"
#include "Engine.hpp"

using namespace nexc;


int main() {

	World world;

	Engine engine;

	world.addSystem(&engine);

	auto sprite = std::make_shared<Sprite>();
	sprite->texture = engine.getAssetsManager()->getTexture("data/test.jpg");
	sprite->textureSize = glm::vec2(656, 657);
	sprite->pixelsInUnit = 656;
	sprite->origin = glm::vec2(0.5f, 0.5f);

	world.createEntity().set(Transform2D()).set(SpriteRenderer(sprite));

	world.createEntity().set(Transform2D()).set(Camera2D());

	HUDTextRenderer tr;
	tr.font = engine.getAssetsManager()->getFont("data/Arial.ttf");
	tr.text = "ABC ДЕФ";

	world.createEntity().set(tr);

	while (true) {
		world.update();
	}

	return 0;
}