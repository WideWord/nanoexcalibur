#pragma once

#include <memory>
#include "../gfx/Texture.hpp"
#include "../gfx/Font.hpp"
#include "../gfx/Sprite.hpp"
#include "../util/Memory.hpp"
#include "Sound.hpp"
#include <unordered_map>

namespace nexc {

	class AssetsManager {
	public:
		Ref<Texture> getTexture(const std::string& filename) {
			return getAsset(filename, textures);
		}

		Ref<Font> getFont(const std::string& filename) {
			return getAsset(filename, fonts);
		}

		Ref<Sprite> getSprite(const std::string& filename) {
			return getAsset(filename, sprites);
		}

		Ref<Sound> getSound(const std::string& filename) {
			return getAsset(filename, sounds);
		}

	private:
		template<typename T> using AssetsStorage = std::unordered_map<std::string, WRef<T>>;

		template<typename T>
		Ref<T> getAsset(const std::string& filename, AssetsStorage<T>& storage) {
			auto it = storage.find(filename);
			if (it != storage.end()) {
				auto ptr = it->second.lock();
				if (ptr != nullptr) {
					return ptr;
				}
			}
			auto asset = New<T>();
			asset->loadFromFile(*this, filename);
			storage[filename] = WRef<T>(asset);
			return asset;
		}

		AssetsStorage<Texture> textures;
		AssetsStorage<Font> fonts;
		AssetsStorage<Sprite> sprites;
		AssetsStorage<Sound> sounds;
	};

}
