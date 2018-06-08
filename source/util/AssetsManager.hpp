#pragma once

#include <memory>
#include "../gfx/Texture.hpp"
#include "../gfx/Font.hpp"
#include <unordered_map>

namespace nexc {

	class AssetsManager {
	public:
		std::shared_ptr<Texture> getTexture(const std::string& filename) {
			return getAsset(filename, textures);
		}

		std::shared_ptr<Font> getFont(const std::string& filename) {
			return getAsset(filename, fonts);
		}

	private:
		template<typename T> using AssetsStorage = std::unordered_map<std::string, std::weak_ptr<T>>;

		template<typename T>
		std::shared_ptr<T> getAsset(const std::string& filename, AssetsStorage<T>& storage) {
			auto it = storage.find(filename);
			if (it != storage.end()) {
				auto ptr = it->second.lock();
				if (ptr != nullptr) {
					return ptr;
				}
			}
			auto asset = std::make_shared<T>();
			asset->loadFromFile(filename);
			storage[filename] = std::weak_ptr<T>(asset);
			return asset;
		}

		AssetsStorage<Texture> textures;
		AssetsStorage<Font> fonts;
	};

}
