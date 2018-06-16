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
		for (uint32_t i = 0; i < maxSystemTypesNum; ++i) {
			systemsByFamily[i] = nullptr;
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
		std::bitset<maxComponentTypesNum> mask;
		uint32_t minAliveNum = UINT32_MAX;
		AnyComponentStorage* storage = nullptr;
		getQueryParams(Dummy<T...>(), mask, minAliveNum, storage);
		return QueryList(this, storage, mask);
	}

	template<typename... T>
	inline Entity World::getAnyEntityWith() {
		auto list = getEntitiesWith<T...>();
		return *(list.begin());
	}

	template<typename T>
	ComponentStorage<T>* World::getComponentStorage() {
		auto family = ComponentStorage<T>::getFamily();
		if (componentStorages[family] == nullptr) {
			componentStorages[family] = new ComponentStorage<T>();
		}
		return (ComponentStorage<T>*)componentStorages[family];
	}


	void World::addSystem(AnySystem* s, int32_t queue) {

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

		systemsByFamily[s->getFamily()] = s;

		s->world = this;
		s->queue = queue;
		s->configure();
	}

	void World::removeSystem(AnySystem* s) {
		for (auto child : s->children) {
			removeSystem(child);
		}
		s->children.clear();
		s->shutdown();
		eventsManager.unsubscribe(s);
		s->world = nullptr;
		systems.remove(s);
		if (systemsByFamily[s->getFamily()] == s) {
			systemsByFamily[s->getFamily()] = nullptr;
		}
	}

	void World::update() {
		for (auto it = systems.begin(); it != systems.end(); ++it) {
			(*it)->run();
		}
		for (uint32_t i = 0; i < maxComponentTypesNum; ++i) {
			auto storage = componentStorages[i];
			if (storage != nullptr) {
				storage->pack();
			}
		}
	}

	template<typename T>
	inline T* World::getSystem() {
		return (T*)systemsByFamily[SystemFamily<T>::getFamily()];
	}

	template<typename T>
	inline void World::emitEvent(const T& ev) {
		eventsManager.emit(ev);
	}

}
