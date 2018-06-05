#pragma once

#include "PoorEntity.hpp"
#include "ComponentHelper.hpp"
#include <stdlib.h>
#include <functional>

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

		class PoorQueryIterator {
		public:
			bool operator!=(const PoorQueryIterator& o) {
				if (end) {
					return !o.end;
				} else {
					return o.end || o.id != id;
				}
			}

			PoorEntity operator*() {
				return PoorEntity(id, world.generation[id]);
			}

			void operator++() {
				while (id != maxEntitiesNum) {
					id += 1;
					if ((world.componentsMask[id] & mask) == mask) {
						break;
					}
				}
				if (id == maxEntitiesNum) {
					end = true;
				}
			}

			explicit PoorQueryIterator(PoorWorld& world, uint64_t mask) : world(world), mask(mask) {
				id = 0;
				end = false;
				while (id != maxEntitiesNum) {
					if ((world.componentsMask[id] & mask) == mask) {
						break;
					}
					id += 1;
				}
				if (id == maxEntitiesNum) {
					end = true;
				}
			}

			PoorQueryIterator(PoorWorld& world) : world(world), mask(0) {
				end = true;
			}
		private:
			PoorWorld& world;
			uint64_t mask;
			uint32_t id;
			bool end;
		};

		class PoorQueryList {
		public:
			PoorQueryList(PoorWorld& world, uint64_t mask) : world(world), mask(mask) {}
			PoorQueryIterator begin() {
				return PoorQueryIterator(world, mask);
			}
			PoorQueryIterator end() {
				return PoorQueryIterator(world);
			}
		private:
			PoorWorld& world;
			uint64_t mask;
		};

		template<typename ...T>
		struct Dummy {};

		template<typename T, typename... Tail>
		uint64_t getQueryMask(Dummy<T, Tail...>) {
			return getQueryMask(Dummy<Tail...>()) | ((uint64_t)1 << ComponentHelper<T>::getFamily());
		}

		uint64_t getQueryMask(Dummy<>) {
			return 0;
		}

		template<typename... T>
		PoorQueryList queryComponents() {
			auto mask = getQueryMask(Dummy<T...>());
			return PoorQueryList(*this, mask);
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
