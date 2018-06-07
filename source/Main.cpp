#include "ecs/World.inl"
#include "ecs/Entity.inl"
#include "ecs/QueryList.inl"
#include <iostream>

using namespace nexc;

struct Position {
	float x, y;
	Position(float x, float y) : x(x), y(y) {}
	Position() : x(0), y(0) {}
};

struct Rotation {
	float a;
	Rotation(float a) : a(a) {}
	Rotation() : a(0) {}
};

int main() {

	World world;

	auto a = world.createEntity();
	auto b = world.createEntity();
	auto c = world.createEntity();

	a.set(Position(1, 2));
	b.set(Position(3, 4));
	b.set(Rotation(-1));
	c.set(Rotation(-2));

	for (auto e : world.getEntitiesWith<Position, Rotation>()) {
		std::cout << e.get<Rotation>().a;
	}

	return 0;
}