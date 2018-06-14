#pragma once

#include <functional>
#include <vector>

namespace nexc {

	class World;

	class AnySystemFamily {
	protected:
		static uint32_t newFamily() {
			static uint32_t family = 0;
			return family++;
		}
	};

	template<typename T>
	class SystemFamily : public AnySystemFamily {
	public:
		static uint32_t getFamily() {
			static uint32_t family = newFamily();
			return family;
		}
	};



	class AnySystem {
	public:
		virtual void configure() {}
		virtual void shutdown() {}
		virtual void run() {}

		World* getWorld() {
			return world;
		}

		template<typename T>
		inline T* getSystem();

		int32_t getQueue() {
			return queue;
		}

		template<typename E>
		inline void subscribe(std::function<void(const E&)> callback);

		inline void addChildSystem(AnySystem* system, int32_t queue = 0);
	private:
		friend class World;
		World* world;
		int32_t queue;
		std::vector<AnySystem*> children;
		virtual uint32_t getFamily() {
			return 0;
		}
	};

	template<typename T>
	class System : public AnySystem {
	private:
		uint32_t getFamily() final {
			return SystemFamily<T>::getFamily();
		}
	};

}
