#pragma once

#include "PoorWorld.hpp"

namespace nanoecs {

	class Entity {
	protected:
		friend class World;
		friend class QueryIterator;
		Entity(PoorEntity self, PoorWorld& world) : self(self), world(world) {}
		PoorEntity self;
		PoorWorld& world;
	public:
		template<typename T>
		Entity& set(const T& component) {
			world.getComponent<T>(self) = component;
			return *this;
		}

		template<typename T>
		const T& get() const {
			return world.getComponent<T>(self);
		}

		template<typename T>
		void remove() {
			world.removeComponent<T>(self);
		}
	};

	class QueryIterator {
	public:
		QueryIterator(PoorWorld::PoorQueryIterator self, PoorWorld& world) : self(self), world(world) {}

		Entity operator*() {
			return Entity(*self, world);
		}

		void operator++() {
			++self;
		}

		bool operator!=(const QueryIterator& o) {
			return self != o.self;
		}
	private:
		PoorWorld::PoorQueryIterator self;
		PoorWorld& world;
	};

	class QueryList {
	public:
		QueryList(PoorWorld::PoorQueryList self, PoorWorld& world) : self(self), world(world) {}

		QueryIterator begin() {
			return QueryIterator(self.begin(), world);
		}
		QueryIterator end() {
			return QueryIterator(self.end(), world);
		}
	protected:
	private:
		PoorWorld::PoorQueryList self;
		PoorWorld& world;
	};

	class World {
	public:
		Entity createEntity() {
			return Entity(self.createEntity(), self);
		}

		void destoryEntity(Entity e) {
			self.destroyEntity(e.self);
		}

		template<typename... T>
		QueryList query() {
			return QueryList(self.queryComponents<T...>(), self);
		}
	private:
		PoorWorld self;
	};

}
