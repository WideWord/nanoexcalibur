#include "Rendering.hpp"
#include "../common/Transform2D.hpp"
#include "Camera2D.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "SpriteRenderer.hpp"
#include "HUDTextRenderer.hpp"
#include <locale>
#include <codecvt>
#include <string>
#include "../3rdparty/glad/glad.h"


namespace nexc {

	Rendering::Rendering(sf::Window& window) : window(window) {
		window.setActive(true);

		auto vs = R"""(
			#version 330

			in vec2 iWorldPosition;

			void main() {
				gl_Position = vec4(iWorldPosition, 0.5, 1);
			}
		)""";
		auto fs = R"""(
			#version 330

			out vec4 oColor;

			void main() {
				oColor = vec4(0, 1, 0, 1);
			}
		)""";
		shader.build(vs, fs);

	}

	void Rendering::run() {
		window.setActive(true);

		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		window.display();
	}

}
