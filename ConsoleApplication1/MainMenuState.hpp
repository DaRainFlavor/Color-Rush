#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <string>

namespace ColorRush {
	class MainMenuState : public State {
	public:
		MainMenuState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		Sprite _box;
		Sprite _background;
		Sprite _playButton;
		Sprite _rulesButton;
		Sprite _rankingButton;
		Sprite _logOutButton;
		string _inputText;
		Sprite _cursor;
		bool _entered;
		Text _textBox;
	};
}
