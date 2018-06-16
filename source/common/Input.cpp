#include "Input.hpp"
#include "GUI.hpp"
#include "../engine/Engine.hpp"
#include <GLFW/glfw3.h>

namespace nexc {

	void Input::run() {
		auto ctx = getWorld()->getSystem<GUI>()->getNuklear();
		auto engine = getWorld()->getSystem<Engine>();

		nk_input_begin(ctx);

		auto mouse = engine->getMousePosition();
		nk_input_motion(ctx, (int)mouse.x, (int)mouse.y);

		nk_input_key(ctx, NK_KEY_DEL, engine->getKey((KeyCode)GLFW_KEY_DELETE));
		nk_input_key(ctx, NK_KEY_ENTER, engine->getKey((KeyCode)GLFW_KEY_ENTER));
		nk_input_key(ctx, NK_KEY_TAB, engine->getKey((KeyCode)GLFW_KEY_TAB));
		nk_input_key(ctx, NK_KEY_BACKSPACE, engine->getKey((KeyCode)GLFW_KEY_BACKSPACE));
		nk_input_key(ctx, NK_KEY_LEFT, engine->getKey((KeyCode)GLFW_KEY_LEFT));
		nk_input_key(ctx, NK_KEY_RIGHT, engine->getKey((KeyCode)GLFW_KEY_RIGHT));
		nk_input_key(ctx, NK_KEY_UP, engine->getKey((KeyCode)GLFW_KEY_UP));
		nk_input_key(ctx, NK_KEY_DOWN, engine->getKey((KeyCode)GLFW_KEY_DOWN));


		if (engine->getKey((KeyCode)GLFW_KEY_LEFT_CONTROL) || engine->getKey((KeyCode)GLFW_KEY_RIGHT_CONTROL)) {
			nk_input_key(ctx, NK_KEY_COPY, engine->getKey((KeyCode)GLFW_KEY_C));
			nk_input_key(ctx, NK_KEY_PASTE, engine->getKey((KeyCode)GLFW_KEY_P));
			nk_input_key(ctx, NK_KEY_CUT, engine->getKey((KeyCode)GLFW_KEY_X));
			nk_input_key(ctx, NK_KEY_DOWN, engine->getKey((KeyCode)GLFW_KEY_DOWN));

		} else {
			nk_input_key(ctx, NK_KEY_COPY, 0);
			nk_input_key(ctx, NK_KEY_PASTE, 0);
			nk_input_key(ctx, NK_KEY_CUT, 0);
			nk_input_key(ctx, NK_KEY_SHIFT, 0);
		}

		nk_input_button(ctx, NK_BUTTON_LEFT, (int)mouse.x, (int)mouse.y, engine->getMouseButton(0));
		nk_input_button(ctx, NK_BUTTON_MIDDLE, (int)mouse.x, (int)mouse.y, engine->getMouseButton(2));
		nk_input_button(ctx, NK_BUTTON_RIGHT, (int)mouse.x, (int)mouse.y, engine->getMouseButton(1));

		nk_input_end(ctx);
	}

}
