#pragma once

#include "Config.hpp"

namespace nexc {

	class AnyComponentStorage {
	public:
		AnyComponentStorage() {
			aliveNum = 0;
			for (uint32_t i = 0; i < maxEntitiesNum; ++i) {
				internalId[i] = maxEntitiesNum;
			}
		}

		virtual ~AnyComponentStorage() {};

	protected:
		void* data;
		uint32_t aliveNum;
		uint32_t internalId[maxEntitiesNum];
		uint32_t entityId[maxEntitiesNum];

		static uint32_t newFamily() {
			static uint32_t family = 0;
			return family++;
		}
	};

	template<typename T>
	class ComponentStorage : public AnyComponentStorage {
	public:
		ComponentStorage() {
			data = (void*)new T[maxEntitiesNum];
		}

		~ComponentStorage() final {
			delete[] (T*)data;
		}

		bool set(uint32_t entity, const T& value) {
			auto iid = internalId[entity];
			bool created = false;
			if (iid == maxEntitiesNum) {
				iid = aliveNum;
				aliveNum += 1;
				entityId[iid] = entity;
				internalId[entity] = iid;
				created = true;
			}
			((T*)data)[iid] = value;
			return created;
		}

		T get(uint32_t entity) {
			auto iid = internalId[entity];
			return ((T*)data)[iid];
		}

		void remove(uint32_t entity) {
			auto iid = internalId[entity];
			if (iid != aliveNum - 1) {
				auto swap = aliveNum - 1;
				((T*)data)[iid] = ((T*)data)[swap];
				entityId[iid] = entityId[swap];
				internalId[entityId[iid]] = iid;
			}
			aliveNum -= 1;
		}

		static uint32_t getFamily() {
			static uint32_t family = newFamily();
			return family;
		}
	};

}
