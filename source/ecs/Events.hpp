#pragma once

#include <stdint.h>
#include <list>
#include <functional>

namespace nanoecs {

	class EventHelperResolver {
	public:
		static uint32_t newFamily() {
			static uint32_t family = 0;
			auto result = family;
			family += 1;
			return result;
		}
	};

	template<typename T>
	class EventHelper {
	public:
		static uint32_t getFamily() {
			static uint32_t family = 64;
			if (family == 64) {
				family = EventHelperResolver::newFamily();
			}
			return family;
		}
	};

	class EventsManager {
	public:
		template<typename T>
		void emit(const T& event) {
			auto family = EventHelper<T>::getFamily();
			for (auto it = observers[family].begin(); it != observers[family].end(); ++it) {
				it->second((void*)(&event));
			}
		}

		template<typename T>
		void observe(void* observer, std::function<void(const T&)> callback) {
			auto family = EventHelper<T>::getFamily();
			observers[family].push_back([=](void* ev) {
				auto typedEvent = (T*)ev;
				callback(*typedEvent);
			});
		}

		void removeObserver(void* observer) {
			for (uint32_t i = 0; i < 64; ++i) {
				observers->remove_if([=](const std::pair<void*, std::function<void(void*)>>& elem) {
					return elem.first == observer;
				});
			}
		}
	private:
		std::list<std::pair<void*, std::function<void(void*)>>> observers[64];
	};

}
