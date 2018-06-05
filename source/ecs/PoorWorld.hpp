#pragma once

#include "PoorEntity.hpp"
#include "ComponentHelper.hpp"
#include <stdlib.h>

namespace nanoecs {

	constexpr uint32_t maxEntitiesNum = 8 * 1024;

	class PoorWorld {
	public:
		PoorWorld() {
			firstFree = 0;
			for (uint32_t i = 0; i < maxEntitiesNum; ++i) {
				nextFree[i] = i + 1;
				generation[i] = 0;
				componentsMask[i] = 0;
				for (uint32_t j = 0; j < 64; ++j) {
					componentInternalId[i][j] = maxEntitiesNum;
				}
			}
			for (uint32_t j = 0; j < 64; ++j) {
				componentsAliveNum[j] = 0;
				componentsData[j] = nullptr;
			}
		}

		PoorEntity createEntity() {
			PoorEntity e;
			e.id = firstFree;
			e.generation = generation[e.id];
			firstFree = nextFree[e.id];
			return e;
		}

		void destroyEntity(PoorEntity e) {
			if (!isAlive(e)) return;
			generation[e.id] += 1;
			nextFree[e.id] = firstFree;
			firstFree = e.id;
		}

		bool isAlive(PoorEntity e) {
			return e.generation == generation[e.id];
		}

		template<typename T>
		T& getComponent(PoorEntity e) {
			auto family = ComponentHelper<T>::getFamily();
			auto mask = 1 << family;
			if ((componentsMask[e.id] & mask) == 0) {
				componentsMask[e.id] |= mask;
				auto ciid = componentsAliveNum[family];
				componentInternalId[e.id][family] = ciid;
				componentEntity[family][ciid] = e.id;
				componentsAliveNum[family] += 1;

				if (componentsData[family] == nullptr) {
					componentsData[family] = malloc(sizeof(T) * maxEntitiesNum);
				}

			}

			auto ciid = componentInternalId[e.id][family];
			auto data = (T*)componentsData[family];

			return data[ciid];
		}

		template<typename T>
		void removeComponent(PoorEntity e) {
			auto family = ComponentHelper<T>::getFamily();
			auto mask = 1 << family;
			if ((componentsMask[e.id] & mask) == 0) return;

			componentsMask[e.id] &= ~mask;

			auto ciid = componentInternalId[e.id][family];
			if (ciid != componentsAliveNum[family] - 1) {
				auto swap = componentsAliveNum[family] - 1;
				auto data = (T*)componentsData[family];
				data[ciid] = data[swap];
				componentEntity[family][ciid] = componentEntity[family][swap];
				componentInternalId[componentEntity[family][ciid]][family] = ciid;
			}

			componentsAliveNum[family] -= 1;
		}

		template<typename T>
		class ComponentListIterator {
		public:
			T& operator*() {
				return data[id];
			}

			void operator++() {
				id += 1;
			}

			bool operator!=(const ComponentListIterator& o) {
				return id != o.id;
			}

			ComponentListIterator(T* data, uint32_t id) : id(id), data(data) {}
		protected:
			uint32_t id;
			T* data;
		};

		template<typename T>
		class ComponentList {
		public:
			ComponentListIterator<T> begin() {
				return ComponentListIterator<T>(data, 0);
			}

			ComponentListIterator<T> end() {
				return ComponentListIterator<T>(data, count);
			}

		protected:
			friend class PoorWorld;
			ComponentList(T* data, uint32_t count) : data(data), count(count) {}
			T* data;
			uint32_t count;
		};

		template<typename T>
		ComponentList<T> queryComponents() {
			auto family = ComponentHelper<T>::getFamily();
			return ComponentList<T>((T*)componentsData[family], componentsAliveNum[family]);
		}
	private:
		uint32_t firstFree;
		uint32_t nextFree[maxEntitiesNum];
		uint32_t generation[maxEntitiesNum];

		uint64_t componentsMask[maxEntitiesNum];
		uint32_t componentInternalId[maxEntitiesNum][64];
		uint32_t componentsAliveNum[64];

		void* componentsData[64];
		uint32_t componentEntity[64][maxEntitiesNum];
	};

}
