#pragma once

#include "Config.hpp"
#include <bitset>
#include "ComponentStorage.hpp"
#include <list>
#include "EventsManager.hpp"

namespace nexc {

	class Entity;
	class QueryList;
	class AnySystem;

	class World {
	public:
		inline World();
		inline ~World();
		inline Entity createEntity();
		inline void destroyEntity(const Entity& e);

		template<typename... T>
		inline QueryList getEntitiesWith();

		template<typename... T>
		inline Entity getAnyEntityWith();

		inline void addSystem(AnySystem* s, int32_t queue = 0);
		inline void removeSystem(AnySystem* s);
		inline void update();

		template<typename T>
		inline T* getSystem();

		template<typename T>
		inline void emitEvent(const T&);
	private:
		friend class Entity;
		friend class QueryList;
		friend class QueryIterator;
		friend class AnySystem;

		uint32_t firstFree;
		uint32_t nextFree[maxEntitiesNum];
		uint32_t generation[maxEntitiesNum];

		std::bitset<maxComponentTypesNum> mask[maxEntitiesNum];

		AnyComponentStorage* componentStorages[maxComponentTypesNum];

		template<typename T> ComponentStorage<T>* getComponentStorage();

		template<typename... T> struct Dummy {};

		template<typename H, typename... T> void getQueryParams(Dummy<H, T...>, std::bitset<maxComponentTypesNum>& mask, uint32_t& minAliveNum, AnyComponentStorage*& storage) {
			mask.set(ComponentStorage<H>::getFamily(), true);
			auto curStorage = getComponentStorage<H>();
			if (curStorage->getAliveNum() < minAliveNum) {
				minAliveNum = curStorage->getAliveNum();
				storage = curStorage;
			}
			getQueryParams(Dummy<T...>(), mask, minAliveNum, storage);
		}

		void getQueryParams(Dummy<>, std::bitset<maxComponentTypesNum>& mask, uint32_t& minAliveNum, AnyComponentStorage*& storage) {}

		std::list<AnySystem*> systems;
		AnySystem* systemsByFamily[maxSystemTypesNum];

		EventsManager eventsManager;

	};

}
