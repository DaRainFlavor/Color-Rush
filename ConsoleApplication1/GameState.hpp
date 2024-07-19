#pragma once
#include <SFML/Graphics.hpp>
#include <future>
#include <thread>
#include <vector>
#include "State.hpp"
#include "Game.hpp"
#include "Grid.hpp"

namespace ColorRush {
	class GameState : public State {
	public:
		GameState(GameDataRef data, int level, int extraMoves);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		int i;
		int _moves;
		int _level;
		int _cellSize;
		int _extraMoves;
		GameDataRef _data;

		Sprite _background;
		Sprite _loadingBackground;

		Sprite _cursor;

		Sprite _exitButton;

		Text _loadingText;
		Text _levelText;
		Text _movesText;
		Text _extraMovesText;
		Text _bestScoreText;

		Sprite _redButton;
		Sprite _yellowButton;
		Sprite _blueButton;
		Sprite _orangeButton;
		Sprite _greenButton;
		Sprite _violetButton;




		GRID* grid;
		bool isHeavyTaskRunning;

		int _gameState;
	};
}
