#pragma once

#include <nexc/nexc.hpp>

using namespace nexc;

struct Projectile {
	Vec2 direction;

	explicit Projectile(Vec2 dir = Vec2()) : direction(dir) {}
};
