#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace ColorRush {
	class GameOverState : public State {
	public:
		GameOverState(GameDataRef data, int level, vector<vector<int>>originalGrid, vector<int>computerAnswer, vector<int> playerAnswer);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		Sprite _background;
		Sprite _showComputerSolutionButton;
		Sprite _restartButton;
		Sprite _backToModesButton;
		Sprite _cursor;
		Text _levelText;
		Text _highScoreText;

		int _level;
		int _highScore;
		vector<vector<int>>_originalGrid;
		vector<int>_computerAnswer;
		vector<int>_playerAnswer;
	};
}
