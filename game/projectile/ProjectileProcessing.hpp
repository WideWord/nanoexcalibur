#pragma once
#include <nexc/nexc.hpp>
#include "Projectile.hpp"

using namespace nexc;

class ProjectileProcessing : public System<ProjectileProcessing> {
public:


	void run() override {
		auto engine = getWorld()->getSystem<Engine>();

		/// движение снарядов
		for (auto e : getWorld()->getEntitiesWith<Transform2D, Projectile>()) {
			auto tr = e.get<Transform2D>();
			auto dir = e.get<Projectile>().direction;
			tr.position += glm::normalize(dir) * engine->getDeltaTime() * 4.0f;
			e.set(tr);
		}

	}


};