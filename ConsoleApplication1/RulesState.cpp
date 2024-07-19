#include <sstream>
#include "DEFINITIONS.hpp"
#include "RulesState.hpp"
#include "MainMenuState.hpp"
#include <iostream>

#include "GameState.hpp"

namespace ColorRush
{
	RulesState::RulesState(GameDataRef data) : _data(data)
	{

	}

	void RulesState::Init()
	{
		_cursor.setTexture(_data->assets.GetTexture("Cursor"));
		_cursor.setScale(0.5, 0.5);

		_data->assets.LoadTexture("Rules Background", RULES_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Continue Button", RULES_CONTINUE_BUTTON);

		_background.setTexture(_data->assets.GetTexture("Rules Background"));
		_continueButton.setTexture(_data->assets.GetTexture("Continue Button"));
		_continueButton.setScale(1.3f, 1.3f);


		_background.setPosition(0, 0);

		float scaleX = static_cast<float>(SCREEN_WIDTH) / _background.getTexture()->getSize().x;
		float scaleY = static_cast<float>(SCREEN_HEIGHT) / _background.getTexture()->getSize().y;
		_background.setScale(scaleX, scaleY);

		_data->assets.LoadTexture("Exit Button", EXIT_BUTTON_FILEPATH);
		_exitButton.setTexture(_data->assets.GetTexture("Exit Button"));
		_exitButton.setPosition(1385, 20);


		int yOffset = 290;

		this->_continueButton.setPosition(
			(SCREEN_WIDTH / 2) - (_continueButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_continueButton.getGlobalBounds().height / 2) + yOffset
		);

	}

	void RulesState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_continueButton, Mouse::Left, _data->window))
			{
				_data->machine.addState(StateRef(new GameState(_data, 1, 0)), true);;
			}
			if (_data->input.IsSpriteClicked(_exitButton, Mouse::Left, _data->window)) {
				_data->machine.addState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void RulesState::Update(float dt)
	{

	}

	void RulesState::Draw(float dt)
	{
		_data->window.clear();


		_data->window.draw(_background);
		_data->window.draw(_continueButton);
		_data->window.draw(_exitButton);

		Vector2i mousePosition = sf::Mouse::getPosition(_data->window);
		_cursor.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		_data->window.draw(_cursor);

		_data->window.display();
	}
}

