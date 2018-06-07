#pragma once

#include <functional>

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

		template<typename T>
		inline void subscribe(std::function<void(const T&)> callback);

	private:
		friend class World;
		World* world;
	};

}
