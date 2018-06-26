#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>

namespace nexc {

	inline void panic(const char* message) {
		std::cerr << message << '\n';
		exit(1);
	}

	inline void checkAssert(bool condition, const char* failMessage) {
		if (!condition) {
			panic(failMessage);
		}
	}

}
