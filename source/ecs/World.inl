#pragma once

#include "World.hpp"
#include "Entity.hpp"
#include "QueryList.hpp"
#include "System.hpp"

namespace nexc {

	World::World() {
		firstFree = 0;
		for (uint32_t i = 0; i < maxEntitiesNum; ++i) {
			nextFree[i] = i + 1;
			generation[i] = 0;
			mask[i] &= 0;
		}
		for (uint32_t j = 0; j < maxComponentTypesNum; ++j) {
			componentStorages[j] = nullptr;
		}
	}

	World::~World() {
		for (uint32_t j = 0; j < maxComponentTypesNum; ++j) {
			if (componentStorages[j] != nullptr) {
				delete componentStorages[j];
			}
		}
	}

	Entity World::createEntity() {
		Entity e;
		e.world = this;
		e.id = firstFree;
		firstFree = nextFree[firstFree];
		e.generation = generation[e.id];
		return e;
	}

	void World::destroyEntity(const Entity& e) {
		if (!e.isAlive()) return;
		for (uint32_t i = 0; i < maxComponentTypesNum; ++i) {
			componentStorages[i]->remove(e.id);
		}
		nextFree[e.id] = firstFree;
		firstFree = e.id;
		generation[e.id] += 1;
		mask[e.id] = std::bitset<maxComponentTypesNum>();
	}

	template<typename... T>
	inline QueryList World::getEntitiesWith() {
		return QueryList(this, getMask(Dummy<T...>()));
	}

	template<typename T>
	ComponentStorage<T>& World::getComponentStorage() {
		auto family = ComponentStorage<T>::getFamily();
		if (componentStorages[family] == nullptr) {
			componentStorages[family] = new ComponentStorage<T>();
		}
		return *((ComponentStorage<T>*)componentStorages[family]);
	}


	void World::addSystem(System* s, int32_t queue) {

		bool inserted = false;
		for (auto it = systems.begin(); it != systems.end(); ++it) {
			if ((*it)->queue > queue) {
				systems.insert(it, s);
				inserted = true;
				break;
			}
		}
		if (!inserted) {
			systems.push_back(s);
		}


		s->world = this;
		s->queue = queue;
		s->configure();
	}

	void World::removeSystem(System* s) {
		for (auto child : s->children) {
			removeSystem(child);
		}
		s->children.clear();
		s->shutdown();
		eventsManager.unsubscribe(s);
		s->world = nullptr;
		systems.remove(s);
	}

	void World::update() {
		for (auto it = systems.begin(); it != systems.end(); ++it) {
			(*it)->run();
		}
	}

	template<typename T>
	inline void World::emitEvent(const T& ev) {
		eventsManager.emit(ev);
	}

}
