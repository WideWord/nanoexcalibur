#include "Window.hpp"

namespace nexc {

	Window::Window(const Config& config) : internal(sf::VideoMode(config.width, config.height), config.title) {}

	void Window::run() {
		sf::Event e;
		while (internal.pollEvent(e)) {}

		deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();
	}

	IVec2 Window::getSize() {
		auto size = internal.getSize();
		return IVec2(size.x, size.y);
	}

	Vec2 Window::getMousePosition() {
		auto pos = sf::Mouse::getPosition(internal);
		return Vec2(pos.x, pos.y);
	}

	bool Window::getMouseButton(int button) {
		return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
	}

	bool Window::getKey(int key) {
		return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
	}

}