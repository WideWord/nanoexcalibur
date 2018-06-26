#include "Sprite.hpp"
#include <fstream>
#include "../3rdparty/nlohmann/json.hpp"
#include "../engine/AssetsManager.hpp"

namespace nexc {

	void Sprite::loadFromFile(AssetsManager& assets, const std::string& filename)  {
		std::ifstream file(filename);
		nlohmann::json j;
		file >> j;
		texture = assets.getTexture(j["texture"].get<std::string>());
		rect.origin.x = j["rect"][0].get<int>();
		rect.origin.y = j["rect"][1].get<int>();
		rect.size.x = j["rect"][2].get<int>();
		rect.size.y = j["rect"][3].get<int>();
		origin.x = j["origin"][0].get<float>();
		origin.y = j["origin"][1].get<float>();
		pixelsInUnit = j["pixelsInUnit"].get<float>();

	}

}