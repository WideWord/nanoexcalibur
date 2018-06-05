#pragma once

#include "PoorWorld.hpp"

namespace nanoecs {

	class Entity {
	protected:
		friend class World;
		Entity(PoorEntity self, PoorWorld& world) : self(self), world(world) {}
		PoorEntity self;
		PoorWorld& world;
	public:
		template<typename T>
		void set(const T& component) {
			world.getComponent<T>(self) = component;
		}

		template<typename T>
		const T& get() {
			world.getComponent<T>(self);
		}

		template<typename T>
		void remove() {
			world.removeComponent<T>(self);
		}
	};

	class World {
	public:
		Entity createEntity() {
			return Entity(self.createEntity(), self);
		}

		void destoryEntity(Entity e) {
			self.destroyEntity(e.self);
		}

		template<typename T>
		PoorWorld::ComponentList<T> queryComponents() {
			return self.queryComponents<T>();
		}
	private:
		PoorWorld self;
	};

}
