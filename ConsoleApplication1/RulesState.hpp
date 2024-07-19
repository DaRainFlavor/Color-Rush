#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace ColorRush
{
    class RulesState : public State
    {
    public:
        RulesState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;

        Sprite _background;

        Sprite _continueButton;

        Sprite _exitButton;

        Sprite _cursor;
    };


}
