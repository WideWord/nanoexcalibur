#pragma once

#include <functional>
#include "Config.hpp"
#include <list>

namespace nexc {

	class EventsManager {
	private:

		struct AnyEventFamily {
			static uint32_t newFamily() {
				uint32_t family = 0;
				return family++;
			}
		};

		template<typename T>
		struct EventFamily : AnyEventFamily {
			static uint32_t getFamily(bool createNew = true) {
				static uint32_t family = maxEventTypesNum;
				if (family == maxEventTypesNum && createNew) {
					family = newFamily();
				}
				return family;
			}
		};

	public:
		template<typename T>
		void subscribe(void* observer, std::function<void(const T&)> callback) {
			Signal sig;
			sig.observer = observer;
			sig.callback = [=](const void* e) {
				callback(*((const T*)e));
			};
			signals[EventFamily<T>::getFamily()].push_back(sig);
		}

		void unsubscribe(void* observer) {
			for (uint32_t i = 0; i < maxEventTypesNum; ++i) {
				signals[i].remove_if([=](const Signal& sig) { return sig.observer == observer; });
			}
		}

		template<typename T>
		void emit(const T& e) {
			auto fam = EventFamily<T>::getFamily(false);
			if (fam == maxEventTypesNum) return;
			for (auto it = signals[fam].begin(); it != signals[fam].end(); ++it) {
				it->callback((const void*)(&e));
			}
		}
	private:
		struct Signal {
			void* observer;
			std::function<void(const void*)> callback;
		};
		std::list<Signal> signals[maxEventTypesNum];
	};

}
