#pragma once
#include <nexc/nexc.hpp>
using namespace nexc;

struct Collider {
	Vec2 size;
	bool dynamic;

	explicit Collider(Vec2 size = Vec2(), bool dynamic = false) : size(size), dynamic(dynamic) {}
};
