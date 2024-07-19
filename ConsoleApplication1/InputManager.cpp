#include "InputManager.hpp"

namespace ColorRush {
    bool InputManager::IsSpriteClicked(Sprite object, Mouse::Button button, RenderWindow& window) {
        static bool isButtonPressedLastFrame = false;
        bool isButtonPressed = Mouse::isButtonPressed(button);

        if (isButtonPressed && !isButtonPressedLastFrame) {
            IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

            if (tempRect.contains(Mouse::getPosition(window))) {
                isButtonPressedLastFrame = true;
                return true;
            }
        }
        else {
            isButtonPressedLastFrame = isButtonPressed;
        }

        return false;
    }

    Vector2i GetMousePosition(RenderWindow& window) {
        return Mouse::getPosition(window);
    }

    bool InputManager::IsKeyPressed(Keyboard::Key key) {
        return Keyboard::isKeyPressed(key);
    }

}
