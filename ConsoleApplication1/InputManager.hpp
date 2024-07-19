#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
namespace ColorRush {
	class InputManager {
	public:
		InputManager() {}
		~InputManager() {}
		bool IsSpriteClicked(Sprite object, Mouse::Button button, RenderWindow& window);
		Vector2i GetMousePosition(RenderWindow& window);
		bool IsKeyPressed(Keyboard::Key key);
	};
}
