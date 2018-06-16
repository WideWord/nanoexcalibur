#include "ecs/ecs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common/Transform2D.hpp"
#include "engine/Engine.hpp"
#include "engine/AssetsManager.hpp"
#include "gfx/Sprite.hpp"
#include "gfx/SpriteRenderer.hpp"
#include "gfx/Camera2D.hpp"

using namespace nexc;



int main() {

	World world;

	Engine engine;

	world.addSystem(&engine);


	auto sprite = New<Sprite>();

	float vertices[] = {
			0, 0, 0, 0,
			1, 0, 1, 0,
			0, 1, 0, 1
	};

	uint16_t indices[] = { 0, 1, 2 };

	sprite->setMesh(bgfx::makeRef(vertices, sizeof(vertices)), bgfx::makeRef(indices, sizeof(indices)));
	sprite->setTexture(engine.getAssetsManager().getTexture("data/test.jpg"));


	world.createEntity().set(Transform2D()).set(SpriteRenderer(sprite));

	world.createEntity().set(Transform2D()).set(Camera2D());

	while (true) {
		world.update();
	}

	return 0;
}