#pragma once

#include "Config.hpp"
#include <bitset>
#include "ComponentStorage.hpp"
#include <list>
#include "EventsManager.hpp"

namespace nexc {

	class Entity;
	class QueryList;
	class System;

	class World {
	public:
		inline World();
		inline ~World();
		inline Entity createEntity();
		inline void destroyEntity(const Entity& e);

		template<typename... T>
		inline QueryList getEntitiesWith();

		inline void addSystem(System* s, int32_t queue = 0);
		inline void removeSystem(System* s);
		inline void update();

		template<typename T>
		inline void emitEvent(const T&);
	private:
		friend class Entity;
		friend class QueryList;
		friend class QueryIterator;
		friend class System;

		uint32_t firstFree;
		uint32_t nextFree[maxEntitiesNum];
		uint32_t generation[maxEntitiesNum];

		std::bitset<maxComponentTypesNum> mask[maxEntitiesNum];

		AnyComponentStorage* componentStorages[maxComponentTypesNum];

		template<typename T> ComponentStorage<T>& getComponentStorage();

		template<typename... T> struct Dummy {};

		template<typename H, typename... T> std::bitset<maxComponentTypesNum> getMask(Dummy<H, T...>) {
			auto bs = getMask(Dummy<T...>());
			bs.set(ComponentStorage<H>::getFamily(), true);
			return bs;
		}

		std::bitset<maxComponentTypesNum> getMask(Dummy<>) {
			return std::bitset<maxComponentTypesNum>();
		}

		std::list<System*> systems;

		EventsManager eventsManager;

	};

}
