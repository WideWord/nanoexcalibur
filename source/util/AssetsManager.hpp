#pragma once

#include <memory>
#include "../gfx/Texture.hpp"
#include <unordered_map>

namespace nexc {

	class AssetsManager {
	public:
		std::shared_ptr<Texture> getTexture(const std::string& filename) {
			auto it = textures.find(filename);
			if (it != textures.end()) {
				auto ptr = it->second.lock();
				if (ptr != nullptr) {
					return ptr;
				}
			}
			auto tex = std::make_shared<Texture>();
			tex->loadFromFile(filename);
			textures[filename] = std::weak_ptr<Texture>(tex);
			return tex;
		}

	private:
		std::unordered_map<std::string, std::weak_ptr<Texture>> textures;
	};

}
