#include <sstream>
#include "MainMenuState.hpp"
#include "Leaderboard.h"
#include "RankingState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

using namespace sf;
using namespace std;

namespace ColorRush {
	RankingState::RankingState(GameDataRef data) : _data(data) {

	}
	void RankingState::Init() {
		_cursor.setTexture(this->_data->assets.GetTexture("Cursor"));
		_cursor.setScale(0.5, 0.5);

		_data->assets.LoadTexture("Ranking Background", RANKING_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("Ranking Background"));

		_data->assets.LoadTexture("Exit Button", EXIT_BUTTON_FILEPATH);
		_exitButton.setTexture(_data->assets.GetTexture("Exit Button"));
		_exitButton.setPosition(1385, 20);

		_data->assets.LoadFont("Player Details", LEVEL_FONT_FILEPATH);

		_playerNameText.setFont(_data->assets.GetFont("Player Details"));
		_playerNameText.setCharacterSize(86);
		_playerNameText.setFillColor(Color::Yellow);

		_playerRankText.setFont(_data->assets.GetFont("Player Details"));
		_playerRankText.setCharacterSize(86);
		_playerRankText.setFillColor(Color::Yellow);

		_playerLevelText.setFont(_data->assets.GetFont("Player Details"));
		_playerLevelText.setCharacterSize(86);
		_playerLevelText.setFillColor(Color::Yellow);

	}

	void RankingState::HandleInput() {
		Event event;
		while (_data->window.pollEvent(event)) {
			if (Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_exitButton, Mouse::Left, _data->window)) {
				_data->machine.addState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}
	void RankingState::Update(float dt) {

	}

	void RankingState::Draw(float dt) {
		_data->window.clear();
		_data->window.draw(_background);
		Player* tmp = Leaderboard::getInstance().getRoot();
		float yPos = 268;
		float xPosRank = 187;
		float xPosName = 300;
		float xPosLevel = 1210;
		int place = 0;
		for (int i = 0; i < 4; i++) {
			if (tmp == NULL) {
				place = 0;
			}
			else {
				if (tmp->prev == NULL) {
					place = 1;
				}
				else if (tmp->prev->classicBestScore > tmp->classicBestScore) {
					place++;
				}
			}

			if (tmp != NULL && tmp->classicBestScore > 1) {
				_playerRankText.setString(to_string(place));
				_playerNameText.setString(tmp->name);
				_playerLevelText.setString(to_string(tmp->classicBestScore));
				tmp = tmp->next;
			}
			else {
				_playerRankText.setString("-");
				_playerNameText.setString("-");
				_playerLevelText.setString("-");

			}

			_playerRankText.setPosition(xPosRank, yPos);
			_playerNameText.setPosition(xPosName, yPos);
			_playerLevelText.setPosition(xPosLevel, yPos);

			yPos += 137.0;

			_data->window.draw(_playerRankText);
			_data->window.draw(_playerNameText);
			_data->window.draw(_playerLevelText);
		}

		_data->window.draw(_exitButton);
		Vector2i mousePosition = sf::Mouse::getPosition(this->_data->window);
		_cursor.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		_data->window.draw(_cursor);
		_data->window.display();
	}
}
