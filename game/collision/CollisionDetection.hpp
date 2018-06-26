#pragma once
#include <nexc/nexc.hpp>
#include "Collider.hpp"

using namespace nexc;

class CollisionDetection : public System<CollisionDetection> {
public:

	void run() override {
		for (auto a : getWorld()->getEntitiesWith<Transform2D, Collider>()) {
			for (auto b : getWorld()->getEntitiesWith<Transform2D, Collider>()) {
				auto aCol = a.get<Collider>();
				auto bCol = b.get<Collider>();
				if (!aCol.dynamic && !bCol.dynamic) continue;

				auto aTr = a.get<Transform2D>();
				auto bTr = b.get<Transform2D>();

				auto aMin = aTr.position - aCol.size * 0.5f;
				auto aMax = aMin + aCol.size;

				auto bMin = bTr.position - bCol.size * 0.5f;
				auto bMax = bMin + bCol.size;

				Vec2 r;

				if (aMax.x > bMin.x && aMax.x < bMax.x) {
					r.x = bMin.x - aMax.x;
				} else if (aMin.x < bMax.x && aMin.x > bMin.x) {
					r.x = bMax.x - aMin.x;
				}

				if (aMax.y > bMin.y && aMax.y < bMax.y) {
					r.y = bMin.y - aMax.y;
				} else if (aMin.y < bMax.y && aMin.y > bMin.y) {
					r.y = bMax.y - aMin.y;
				}

				if (r.x != 0 && r.y != 0) {

					Vec2 resolution;

					if (abs(r.x) < abs(r.y)) {
						resolution.x = r.x;
					} else {
						resolution.y = r.y;
					}

					if (aCol.dynamic && bCol.dynamic) {
						auto halfResolution = resolution * 0.5f;
						aTr.position += halfResolution;
						bTr.position -= halfResolution;
						a.set(aTr);
						b.set(bTr);
					} else if (aCol.dynamic) {
						aTr.position += resolution;
						a.set(aTr);
					} else {
						bTr.position -= resolution;
						b.set(bTr);
					}

				}

			}
		}
	}

};
