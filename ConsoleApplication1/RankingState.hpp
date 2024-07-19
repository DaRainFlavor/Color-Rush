#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <string>

namespace ColorRush {
	class RankingState : public State {
	public:
		RankingState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		Sprite _background;
		Sprite _exitButton;
		Sprite _cursor;
		Text _playerNameText;
		Text _playerLevelText;
		Text _playerRankText;
	};
}
