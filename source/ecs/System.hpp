#pragma once

#include <functional>
#include <vector>

namespace nexc {

	class World;

	class System {
	public:
		virtual void configure();
		virtual void shutdown();
		virtual void run();

		World* getWorld() {
			return world;
		}

		int32_t getQueue() {
			return queue;
		}

		template<typename T>
		inline void subscribe(std::function<void(const T&)> callback);

		inline void addChildSystem(System* system, int32_t queue = 0);
	private:
		friend class World;
		World* world;
		int32_t queue;
		std::vector<System*> children;
	};

}
