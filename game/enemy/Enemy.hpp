#pragma once

class Path;

struct Enemy {
	bool isRed;
	int hits;
	float speed;
	Path* path;
	float pathTween;
};