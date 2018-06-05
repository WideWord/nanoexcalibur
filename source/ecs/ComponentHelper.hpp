#pragma once

#include <stdint.h>

namespace nanoecs {

	class ComponentFamilyResolver {
	public:
		static uint32_t newFamily() {
			static uint32_t family = 0;
			auto result = family;
			family += 1;
			return result;
		}
	};

	template<typename T>
	class ComponentHelper {
	protected:
		friend class PoorWorld;

		static uint32_t getFamily() {
			static uint32_t family = 64;
			if (family == 64) {
				family = ComponentFamilyResolver::newFamily();
			}
			return family;
		}


	};

}