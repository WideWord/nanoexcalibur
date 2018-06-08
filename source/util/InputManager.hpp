#pragma once

#include <SFML/Window.hpp>
#include "../util/Math.hpp"

namespace nexc {

	using KeyCode = sf::Keyboard::Key;

	using MouseButton = sf::Mouse::Button;

	class InputManager {
	public:
		explicit InputManager(sf::Window& window) : window(window) {}

		bool getKey(KeyCode key) const {
			return sf::Keyboard::isKeyPressed(key);
		}

		IVec2 getMousePosition() const {
			auto pos = sf::Mouse::getPosition(window);
			return IVec2(pos.x, pos.y);
		}

		bool getMouseButton(MouseButton button) const {
			return sf::Mouse::isButtonPressed(button);
		}
	private:
		sf::Window& window;
	};

}
