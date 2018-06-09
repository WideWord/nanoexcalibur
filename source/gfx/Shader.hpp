#pragma once

#include <cstdint>

namespace nexc {

	class Shader {
	public:
		Shader();
		~Shader();
		void build(const char* vs, const char* fs);

		uint32_t getId() {
			return id;
		}
	private:
		uint32_t id;
		uint32_t vertex;
		uint32_t fragment;
	};

}
