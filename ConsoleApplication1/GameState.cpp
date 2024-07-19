#include <sstream>
#include "GameState.hpp"
#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "Leaderboard.h"
#include "DEFINITIONS.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace ColorRush {
	GameState::GameState(GameDataRef data, int level, int extraMoves) : _data(data), _level(level), _extraMoves(extraMoves) {

	}
	void GameState::Init() {
		_cellSize = 50;
		i = 0;
		_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));
		_background.setScale(0.78, 0.88);

		_data->assets.LoadTexture("Loading Background", LOADING_BACKGROUND_FILEPATH);
		_loadingBackground.setTexture(this->_data->assets.GetTexture("Loading Background"));

		_cursor.setTexture(_data->assets.GetTexture("Cursor"));
		_cursor.setScale(0.5, 0.5);

		_data->assets.LoadTexture("Exit Button", EXIT_BUTTON_FILEPATH);
		_exitButton.setTexture(this->_data->assets.GetTexture("Exit Button"));
		_exitButton.setPosition(1385, 20);

		_data->assets.LoadFont("Loading Font", LOADING_FONT_FILEPATH);
		_loadingText.setFont(this->_data->assets.GetFont("Loading Font"));
		_loadingText.setString("Setting up level " + to_string(_level) + ".");
		_loadingText.setCharacterSize(70);
		_loadingText.setFillColor(Color::Black);
		_loadingText.setOutlineThickness(0.5);
		_loadingText.setOutlineColor(Color::Black);
		_loadingText.setOrigin(_loadingText.getGlobalBounds().width / 2, _loadingText.getGlobalBounds().height / 2);
		_loadingText.setPosition(_data->window.getSize().x / 2, (_data->window.getSize().y / 2) + 100);

		_data->assets.LoadFont("Level Font", LEVEL_FONT_FILEPATH);
		_levelText.setFont(this->_data->assets.GetFont("Level Font"));
		_levelText.setString(to_string(_level));
		_levelText.setCharacterSize(46);
		_levelText.setFillColor(Color::Black);
		_levelText.setOutlineColor(Color::Black);
		_levelText.setPosition(1170.0, 160.0);

		_movesText.setFont(this->_data->assets.GetFont("Level Font"));
		_movesText.setCharacterSize(46);
		_movesText.setFillColor(Color::Black);
		_movesText.setOutlineColor(Color::Black);
		_movesText.setPosition(1170.0, 210.0);

		_extraMovesText.setFont(this->_data->assets.GetFont("Level Font"));
		_extraMovesText.setCharacterSize(46);
		_extraMovesText.setFillColor(Color::Red);
		_extraMovesText.setOutlineColor(Color::Black);
		_extraMovesText.setPosition(1370.0, 210.0);

		_bestScoreText.setFont(this->_data->assets.GetFont("Level Font"));
		_bestScoreText.setCharacterSize(46);
		_bestScoreText.setFillColor(Color::Black);
		_bestScoreText.setOutlineColor(Color::Black);
		_bestScoreText.setString(to_string(Leaderboard::getInstance().getCurrentUser()->classicBestScore));
		_bestScoreText.setPosition(1400, 164);

		_data->assets.LoadTexture("Red Button", RED_BUTTON_FILEPATH);
		_redButton.setTexture(this->_data->assets.GetTexture("Red Button"));
		_redButton.setPosition(980, 400);

		_data->assets.LoadTexture("Yellow Button", YELLOW_BUTTON_FILEPATH);
		_yellowButton.setTexture(this->_data->assets.GetTexture("Yellow Button"));
		_yellowButton.setPosition(1145, 398);

		_data->assets.LoadTexture("Blue Button", BLUE_BUTTON_FILEPATH);
		_blueButton.setTexture(this->_data->assets.GetTexture("Blue Button"));
		_blueButton.setPosition(1310, 400);

		_data->assets.LoadTexture("Orange Button", ORANGE_BUTTON_FILEPATH);
		_orangeButton.setTexture(this->_data->assets.GetTexture("Orange Button"));
		_orangeButton.setPosition(980, 560);

		_data->assets.LoadTexture("Green Button", GREEN_BUTTON_FILEPATH);
		_greenButton.setTexture(this->_data->assets.GetTexture("Green Button"));
		_greenButton.setPosition(1145, 560);

		_data->assets.LoadTexture("Violet Button", VIOLET_BUTTON_FILEPATH);
		_violetButton.setTexture(this->_data->assets.GetTexture("Violet Button"));
		_violetButton.setPosition(1313, 560);

		isHeavyTaskRunning = true;

		std::thread heavyTaskThread([this]() {
			grid = new GRID(_data);
			grid->solver();
			_moves = grid->getAnswer().size();
			int addMoves = 0;
			if (_level == 1) addMoves = 4;
			else if (_level == 2 || _level == 3) addMoves = 2;
			else if (_level == 4 || _level == 6) addMoves = 1;
			_moves += addMoves;


			isHeavyTaskRunning = false; 
			});

		heavyTaskThread.detach();


	}
	void GameState::HandleInput() {
		if (!isHeavyTaskRunning && _moves > 0) {
			vector<int> ans = grid->getAnswer();
			int ansL = ans.size();
			//cout << "AnsL: " << ans.size() << endl;
			Event event;
			while (_data->window.pollEvent(event) && _moves > 0) {
				if (Event::Closed == event.type) {
					_data->window.close();
				}
				if (_data->input.IsSpriteClicked(_exitButton, Mouse::Left, _data->window)) {
					if (_level > Leaderboard::getInstance().getCurrentUser()->classicBestScore) {
						Leaderboard::getInstance().updateClassicBestScore(_level);
					}
					_data->machine.addState(StateRef(new MainMenuState(_data)), true);
				}
				if (_data->input.IsSpriteClicked(_redButton, Mouse::Left, _data->window) || _data->input.IsKeyPressed(Keyboard::R)) {
					if (_extraMoves > 0) {
						_extraMoves -= grid->floodFill(1);
					}
					else {
						_moves -= grid->floodFill(1);
					}
				}
				if (_data->input.IsSpriteClicked(_yellowButton, Mouse::Left, _data->window) || _data->input.IsKeyPressed(Keyboard::Y)) {
					if (_extraMoves > 0) {
						_extraMoves -= grid->floodFill(2);
					}
					else {
						_moves -= grid->floodFill(2);
					}
				}
				if (_data->input.IsSpriteClicked(_blueButton, Mouse::Left, _data->window) || _data->input.IsKeyPressed(Keyboard::B)) {
					if (_extraMoves > 0) {
						_extraMoves -= grid->floodFill(3);
					}
					else {
						_moves -= grid->floodFill(3);
					}
				}
				if (_data->input.IsSpriteClicked(_orangeButton, Mouse::Left, _data->window) || _data->input.IsKeyPressed(Keyboard::O)) {
					if (_extraMoves > 0) {
						_extraMoves -= grid->floodFill(4);
					}
					else {
						_moves -= grid->floodFill(4);
					}
				}
				if (_data->input.IsSpriteClicked(_greenButton, Mouse::Left, _data->window) || _data->input.IsKeyPressed(Keyboard::G)) {
					if (_extraMoves > 0) {
						_extraMoves -= grid->floodFill(5);
					}
					else {
						_moves -= grid->floodFill(5);
					}
				}
				if (_data->input.IsSpriteClicked(_violetButton, Mouse::Left, _data->window) || _data->input.IsKeyPressed(Keyboard::V)) {
					if (_extraMoves > 0) {
						_extraMoves -= grid->floodFill(6);
					}
					else {
						_moves -= grid->floodFill(6);
					}
				}
			}
		}
		else{
			Event event;
			while (_data->window.pollEvent(event) && _moves > 0) {
				if (Event::Closed == event.type) {
					_data->window.close();
				}
			}
		}
	}
	void GameState::Update(float dt) {
		//cout << "moves: " << _moves << endl;
		if (!isHeavyTaskRunning) {
			_movesText.setString(to_string(_moves));
			_extraMovesText.setString(to_string(_extraMoves));
			if (grid->isGameWon() && _moves >= 0) {
				//cout << "Game Over";
				_level++;
				Leaderboard::getInstance().updateClassicBestScore(_level);
				_data->machine.addState(StateRef(new GameState(_data, _level, _moves + _extraMoves)), true);
			}
			else if (!grid->isGameWon() && _moves <= 0) {
				if (_level > Leaderboard::getInstance().getCurrentUser()->classicBestScore) {
					Leaderboard::getInstance().updateClassicBestScore(_level);
				}
				_data->machine.addState(StateRef(new GameOverState(_data, _level, grid->originalGrid, grid->getAnswer(), grid->getPlayerSequence())));
			}

		}
	}

	void GameState::Draw(float dt) {
		_data->window.clear();
		int offsetX = ((_data->window.getSize().x - COLS * _cellSize) / 2) - 295;
		int offsetY = (_data->window.getSize().y - ROWS * _cellSize) / 2;
		if (isHeavyTaskRunning) {
			_data->window.draw(_loadingBackground);
			loadingGRID tmpGrid(_data);
			tmpGrid.drawGrid(_cellSize, ((_data->window.getSize().x - 5 * _cellSize) / 2), (_data->window.getSize().y - 5 * _cellSize) / 2 - 100);
			_data->window.draw(_loadingText);
		}
		else {
			_data->window.draw(_background);
			_data->window.draw(_exitButton);
			grid->drawGrid(_cellSize, offsetX, offsetY);
			_data->window.draw(_levelText);
			_data->window.draw(_movesText);
			_data->window.draw(_extraMovesText);
			_data->window.draw(_redButton);
			_data->window.draw(_yellowButton);
			_data->window.draw(_blueButton);
			_data->window.draw(_orangeButton);
			_data->window.draw(_greenButton);
			_data->window.draw(_violetButton);
			_data->window.draw(_bestScoreText);
		}
		Vector2i mousePosition = sf::Mouse::getPosition(this->_data->window);
		_cursor.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		_data->window.draw(_cursor);
		_data->window.display();
	}
}
