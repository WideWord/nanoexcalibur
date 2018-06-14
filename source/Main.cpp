#include "ecs/ecs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common/Transform2D.hpp"
#include "engine/Engine.hpp"
#include "gfx/Sprite.hpp"
#include "gfx/SpriteRenderer.hpp"

using namespace nexc;



int main() {

	World world;

	Engine engine;

	world.addSystem(&engine);


	auto sprite = New<Sprite>();

	float vertices[] = {
			0, 0, 1, 0, 0, 1
	};

	uint16_t indices[] = { 0, 1, 2 };

	sprite->setMesh(bgfx::makeRef(vertices, sizeof(vertices)), bgfx::makeRef(indices, sizeof(indices)));

	world.createEntity().set(Transform2D()).set(SpriteRenderer(sprite));

	while (true) {
		world.update();
	}

	return 0;
}