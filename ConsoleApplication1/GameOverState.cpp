#include <sstream>
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "ReplayState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace ColorRush {
	ColorRush::GameOverState::GameOverState(GameDataRef data, int level, vector<vector<int>> originalGrid, vector<int> computerAnswer, vector<int> playerAnswer)
		: _data(data), _level(level), _originalGrid(originalGrid), _computerAnswer(computerAnswer), _playerAnswer(playerAnswer) // Corrected semicolon to colon
	{
	}
	void GameOverState::Init() {
		_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));

		_cursor.setTexture(_data->assets.GetTexture("Cursor"));
		_cursor.setScale(0.5, 0.5);

		_data->assets.LoadFont("Level Font", LEVEL_FONT_FILEPATH);
		_levelText.setFont(this->_data->assets.GetFont("Level Font"));
		_levelText.setString(to_string(_level));
		_levelText.setCharacterSize(86);
		_levelText.setFillColor(Color::Red);
		_levelText.setPosition(990, 364);

		_data->assets.LoadTexture("Show Computer Solution Button", SHOW_COMPUTER_SOLUTION_BUTTON_FILEPATH);
		_showComputerSolutionButton.setTexture(this->_data->assets.GetTexture("Show Computer Solution Button"));
		_showComputerSolutionButton.setPosition(200, 600);
		_showComputerSolutionButton.setScale(1.3, 1.3);

		_data->assets.LoadTexture("Restart Button", RESTART_BUTTON_FILEPATH);
		_restartButton.setTexture(this->_data->assets.GetTexture("Restart Button"));
		_restartButton.setPosition(553, 600);
		_restartButton.setScale(1.3, 1.3);

		_data->assets.LoadTexture("Back to Modes Button", BACK_TO_MODES_BUTTON_FILEPATH);
		_backToModesButton.setTexture(this->_data->assets.GetTexture("Back to Modes Button"));
		_backToModesButton.setPosition(905, 600);
		_backToModesButton.setScale(1.3, 1.3);
	}
	void GameOverState::HandleInput() {
		Event event;
		while (_data->window.pollEvent(event)) {
			if (Event::Closed == event.type) {
				_data->window.close();
			}
			if (_data->input.IsSpriteClicked(_backToModesButton, Mouse::Left, _data->window)) {
				_data->machine.addState(StateRef(new MainMenuState(_data)), true);
			}


			if (_data->input.IsSpriteClicked(_showComputerSolutionButton, Mouse::Left, _data->window)) {
				_data->machine.addState(StateRef(new ReplayState(_data, _originalGrid, _computerAnswer, _playerAnswer)), true);
			}
			else if (_data->input.IsSpriteClicked(_restartButton, Mouse::Left, _data->window)) {
				_data->machine.addState(StateRef(new GameState(_data, 1, 0)), true);
			}

		}
	}
	void GameOverState::Update(float dt) {

	}

	void GameOverState::Draw(float dt) {
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_levelText);
		_data->window.draw(_showComputerSolutionButton);
		_data->window.draw(_restartButton);
		_data->window.draw(_backToModesButton);

		Vector2i mousePosition = sf::Mouse::getPosition(this->_data->window);
		_cursor.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		_data->window.draw(_cursor);
		_data->window.display();
	}
}
