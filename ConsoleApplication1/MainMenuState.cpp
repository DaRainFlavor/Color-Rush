#include <sstream>
#include "MainMenuState.hpp"
#include "Leaderboard.h"
#include "GameState.hpp"
#include "RulesState.hpp"
#include "RankingState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace ColorRush {
	MainMenuState::MainMenuState(GameDataRef data) : _data(data) {

	}
	void MainMenuState::Init() {
		_inputText = "";
		_entered = false;

		_data->assets.LoadTexture("Cursor", CURSOR_FILEPATH);
		_cursor.setTexture(this->_data->assets.GetTexture("Cursor"));
		_cursor.setScale(0.5, 0.5);

		_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_background.setOrigin(_background.getLocalBounds().width / 2, _background.getLocalBounds().height / 2);
		_background.setPosition(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2));

		_data->assets.LoadTexture("Text Box", TEXT_BOX_FILEPATH);
		_box.setTexture(this->_data->assets.GetTexture("Text Box"));
		_box.setPosition((SCREEN_WIDTH / 2) - (_box.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_box.getGlobalBounds().height / 2) + 310.0);

		_data->assets.LoadTexture("Log Out Button", LOG_OUT_BUTTON_FILEPATH);
		_logOutButton.setTexture(this->_data->assets.GetTexture("Log Out Button"));
		_logOutButton.setPosition(1280, 20);
		_logOutButton.setScale(0.7, 0.7);

		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2) + 290.0);
		_playButton.setScale(1.2, 1.2);

		_data->assets.LoadTexture("Rules Button", RULES_BUTTON_FILEPATH);
		_rulesButton.setTexture(this->_data->assets.GetTexture("Rules Button"));
		_rulesButton.setPosition((SCREEN_WIDTH / 2) - (_rulesButton.getGlobalBounds().width / 2) - 300, (SCREEN_HEIGHT / 2) - (_rulesButton.getGlobalBounds().height / 2) + 297.0);

		_data->assets.LoadTexture("Ranking Button", RANKING_BUTTON_FILEPATH);
		_rankingButton.setTexture(this->_data->assets.GetTexture("Ranking Button"));
		_rankingButton.setPosition((SCREEN_WIDTH / 2) - (_rankingButton.getGlobalBounds().width / 2) + 360, (SCREEN_HEIGHT / 2) - (_rankingButton.getGlobalBounds().height / 2) + 297.0);



		_data->assets.LoadFont("Level Font", LEVEL_FONT_FILEPATH);
		_textBox.setFont(this->_data->assets.GetFont("Level Font"));
		_textBox.setCharacterSize(53);
		_textBox.setFillColor(Color::White);


	}

	void MainMenuState::HandleInput() {
		Event event;
		while (_data->window.pollEvent(event)) {
			if (Event::Closed == event.type) {
				_data->window.close();
			}
			if (_data->input.IsSpriteClicked(_playButton, Mouse::Left, _data->window) && Leaderboard::getInstance().loggedIn) {
				_data->machine.addState(StateRef(new GameState(_data, 1, 0)), true);

			}

			if (_data->input.IsSpriteClicked(_logOutButton, Mouse::Left, _data->window) && Leaderboard::getInstance().loggedIn) {
				Leaderboard::getInstance().loggedIn = false;
				_inputText = "";
			}

			if (_data->input.IsSpriteClicked(_rulesButton, Mouse::Left, _data->window) && Leaderboard::getInstance().loggedIn) {
				_data->machine.addState(StateRef(new RulesState(_data)), true);
			}

			if (_data->input.IsSpriteClicked(_rankingButton, Mouse::Left, _data->window) && Leaderboard::getInstance().loggedIn) {
				_data->machine.addState(StateRef(new RankingState(_data)), true);
			}

			if (!Leaderboard::getInstance().loggedIn && event.type == Event::TextEntered && _inputText.size() <= 15) {
				if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13) {//8 is backspace 13 is enter
					_inputText += static_cast<char>(event.text.unicode);
				}
				else if (event.text.unicode == 8 && !_inputText.empty()) {
					_inputText.pop_back();
				}
			}

			if (_data->input.IsKeyPressed(Keyboard::Enter) && !_inputText.empty()) {
				Leaderboard::getInstance().currentlyUsing(_inputText);
				Leaderboard::getInstance().loggedIn = true;
			}

			_textBox.setString(_inputText);
		}
	}
	void MainMenuState::Update(float dt) {

	}

	void MainMenuState::Draw(float dt) {
		_data->window.clear();
		_data->window.draw(_background);

		float xPos = (_data->window.getSize().x - _textBox.getGlobalBounds().width) / 2.0f;
		float yPos = (_data->window.getSize().y - _textBox.getGlobalBounds().height) / 2.0f;
		if (!Leaderboard::getInstance().loggedIn) {
			_textBox.setPosition(xPos, yPos + 310.0);
			_data->window.draw(_box);
			_data->window.draw(_textBox);
		}
		else {
			_data->window.draw(_logOutButton);
			_data->window.draw(_playButton);
			_data->window.draw(_rulesButton);
			_data->window.draw(_rankingButton);
		}

		Vector2i mousePosition = sf::Mouse::getPosition(this->_data->window);
		_cursor.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		_data->window.draw(_cursor);


		_data->window.display();
	}
}
