#include <sstream>
#include "ReplayState.hpp"
#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace ColorRush {

	ReplayState::ReplayState(GameDataRef data, vector<vector<int>> originalGrid, vector<int> computerAnswer, vector<int> playerAnswer)
		: _data(data), _originalGrid(originalGrid), _computerAnswer(computerAnswer), _playerAnswer(playerAnswer)
	{
	}
	void ReplayState::Init() {
		_cursor.setTexture(_data->assets.GetTexture("Cursor"));
		_cursor.setScale(0.5, 0.5);

		_cellSize = 50;
		rows = cols = 14;
		i = 0;
		I = J = 0;
		_data->assets.LoadTexture("Game Background", REPLAY_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		_data->assets.LoadTexture("Forward Button", FORWARD_BUTTON_FILEPATH);
		_forwardButton.setTexture(this->_data->assets.GetTexture("Forward Button"));
		_forwardButton.setPosition(800, 763);

		_data->assets.LoadTexture("Backward Button", BACKWARD_BUTTON_FILEPATH);
		_backButton.setTexture(this->_data->assets.GetTexture("Backward Button"));
		_backButton.setPosition(615, 763);

		_data->assets.LoadTexture("Exit Button", EXIT_BUTTON_FILEPATH);
		_exitButton.setTexture(this->_data->assets.GetTexture("Exit Button"));
		_exitButton.setPosition(1385, 20);

		_computerGridSequence.push_back(_originalGrid);
		_playerGridSequence.push_back(_originalGrid);
		floodFill();

	}
	void ReplayState::HandleInput() {
		Event event;
		while (_data->window.pollEvent(event)) {
			if (Event::Closed == event.type) {
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_exitButton, Mouse::Left, _data->window)) {
				_data->machine.addState(StateRef(new MainMenuState(_data)), true);
			}

			if (_data->input.IsKeyPressed(Keyboard::Right) || _data->input.IsSpriteClicked(_forwardButton, Mouse::Left, _data->window)) {
				I++;
				if (I >= _computerGridSequence.size()) {
					I = 0;
				}
			}
			if (_data->input.IsKeyPressed(Keyboard::Left) || _data->input.IsSpriteClicked(_backButton, Mouse::Left, _data->window)) {
				I--;
				if (I < 0) {
					I = _computerGridSequence.size() - 1;
				}
			}
		}
	}
	void ReplayState::Update(float dt) {

	}

	void ReplayState::floodFill() {
		vector<vector<int>> gridCopy = _originalGrid;
		for (int i = 0; i < _computerAnswer.size(); i++) {
			vector<vector<int>> tmp;

			int targetColor = gridCopy[0][0];
			int replacementColor = _computerAnswer[i];

			if (targetColor == replacementColor) {
				continue;
			}
			queue<pair<int, int>> q;
			q.push({ 0, 0 });

			while (!q.empty()) {
				int r = q.front().first;
				int c = q.front().second;
				q.pop();

				if (gridCopy[r][c] == replacementColor) continue;

				gridCopy[r][c] = replacementColor;

				if (r - 1 >= 0 && gridCopy[r - 1][c] == targetColor) q.push({ r - 1, c });
				if (r + 1 < rows && gridCopy[r + 1][c] == targetColor) q.push({ r + 1, c });
				if (c - 1 >= 0 && gridCopy[r][c - 1] == targetColor) q.push({ r, c - 1 });
				if (c + 1 < cols && gridCopy[r][c + 1] == targetColor) q.push({ r, c + 1 });
			}
			_computerGridSequence.push_back(gridCopy);
		}

		gridCopy = _originalGrid;
		for (int i = 0; i < _playerAnswer.size(); i++) {
			vector<vector<int>> tmp;

			int targetColor = gridCopy[0][0];
			int replacementColor = _playerAnswer[i];

			if (targetColor == replacementColor) {
				continue;
			}
			queue<pair<int, int>> q;
			q.push({ 0, 0 });

			while (!q.empty()) {
				int r = q.front().first;
				int c = q.front().second;
				q.pop();

				if (gridCopy[r][c] == replacementColor) continue;

				gridCopy[r][c] = replacementColor;

				if (r - 1 >= 0 && gridCopy[r - 1][c] == targetColor) q.push({ r - 1, c });
				if (r + 1 < rows && gridCopy[r + 1][c] == targetColor) q.push({ r + 1, c });
				if (c - 1 >= 0 && gridCopy[r][c - 1] == targetColor) q.push({ r, c - 1 });
				if (c + 1 < cols && gridCopy[r][c + 1] == targetColor) q.push({ r, c + 1 });
			}
			_playerGridSequence.push_back(gridCopy);
		}

		int add = _computerGridSequence.size() - _playerGridSequence.size();
		if (add < 0) {
			add *= -1;
			while (add--) {
				_computerGridSequence.push_back(_computerGridSequence.back());
			}
		}
		else if (add > 0) {
			while (add--) {
				_playerGridSequence.push_back(_playerGridSequence.back());
			}
		}
	}

	void ReplayState::drawGrid(vector<vector<int>> grid, float cellSize, float offsetX, float offsetY) {
		RectangleShape cell(Vector2f(cellSize, cellSize));
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				int x = i * cellSize + offsetX;
				int y = j * cellSize + offsetY;
				cell.setPosition(x, y);
				switch (grid[i][j]) {
				case 1:
					cell.setFillColor(sf::Color(255, 0, 0, 255));//red
					break;
				case 2:
					cell.setFillColor(sf::Color(255, 255, 0, 255));//yellow
					break;
				case 3:
					cell.setFillColor(sf::Color(51, 76, 203, 255));//blue
					break;
				case 4:
					cell.setFillColor(sf::Color(255, 128, 0, 255));//orange
					break;
				case 5:
					cell.setFillColor(sf::Color(0, 255, 0, 255));//green
					break;
				case 6:
					cell.setFillColor(sf::Color(128, 0, 179, 255)); // violet
					break;
				}
				_data->window.draw(cell);

				int color = grid[i][j];
				float borderSize = 3.5f;
				if ((i < (rows - 1) && grid[i + 1][j] != color) || i == cols - 1) {
					RectangleShape border(Vector2f(borderSize, cellSize + borderSize));
					border.setPosition(x + cellSize - borderSize, y - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

				if (i == 0) {
					RectangleShape border(Vector2f(borderSize, cellSize + borderSize));
					border.setPosition(x, y - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

				if ((j < (cols - 1) && grid[i][j + 1] != color) || j == rows - 1) {
					RectangleShape border(Vector2f(cellSize, borderSize));
					border.setPosition(x, y + cellSize - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

				if (j == 0) {
					RectangleShape border(Vector2f(cellSize, borderSize));
					border.setPosition(x, y - borderSize);
					border.setFillColor(sf::Color::Black);
					_data->window.draw(border);
				}

			}
		}
	}

	void ReplayState::Draw(float dt) {
		_data->window.clear();
		_data->window.draw(_background);
		int offsetX = ((_data->window.getSize().x - COLS * _cellSize) / 2) - 320;
		int offsetY = (_data->window.getSize().y - ROWS * _cellSize) / 2 + 100;
		drawGrid(_computerGridSequence[I], 40, offsetX, offsetY);

		drawGrid(_playerGridSequence[I], 40, offsetX + 760, offsetY);
		_data->window.draw(_forwardButton);
		_data->window.draw(_backButton);
		_data->window.draw(_exitButton);

		Vector2i mousePosition = sf::Mouse::getPosition(this->_data->window);
		_cursor.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		_data->window.draw(_cursor);

		_data->window.display();


	}
}

