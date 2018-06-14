#include "ecs/ecs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common/Transform2D.hpp"
#include "engine/Engine.hpp"

using namespace nexc;



int main() {

	World world;

	Engine engine;

	world.addSystem(&engine);

	while (true) {
		world.update();
	}

	return 0;
}