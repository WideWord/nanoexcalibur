#pragma once
#include <nexc/nexc.hpp>

using namespace nexc;

/// придётся в коде игры, потому что забыл добавить в движок

inline Transform2D makeTransform(Vec2 position = Vec2(), float rotation = 0) {
	Transform2D transform;
	transform.position = position;
	transform.rotation = rotation;
	return transform;
}
