#pragma once
#include <SFML/Graphics.hpp>
#include <future>
#include <thread>
#include <vector>
#include "State.hpp"
#include "Game.hpp"
#include "Grid.hpp"

namespace ColorRush {
	class ReplayState : public State {
	public:
		ReplayState(GameDataRef data, vector<vector<int>> originalGrid, vector<int>computerAnswer, vector<int>playerAnswer);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		int i, I, J;
		int _cellSize;
		int rows, cols;
		GameDataRef _data;
		vector<vector<int>> _originalGrid;
		vector<vector<vector<int>>> _computerGridSequence;
		vector<vector<vector<int>>> _playerGridSequence;
		vector<int> _computerAnswer;
		vector<int> _playerAnswer;
		Sprite _background;
		Sprite _forwardButton;
		Sprite _backButton;
		Sprite _exitButton;
		Sprite _cursor;

		void drawGrid(vector<vector<int>> grid, float cellSize, float offsetX, float offsetY);
		void floodFill();
	};
}

