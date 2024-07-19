#include "Game.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "SplashState.hpp"

namespace ColorRush {
	Game::Game(int width, int height, string title) {
		_data->window.create(VideoMode(width, height), title, Style::Close | Style::Titlebar);
		_data->machine.addState(StateRef(new SplashState(this->_data)));

		this->Run();
	}
	void Game::Run() {

		float newTime, frameTime, interpolation;
		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		sf::Music music;

		if (!music.openFromFile("Resources/res/Turkish march from The Ruins of Athens by Beethoven.wav")) {
			std::cout << "Error" << std::endl;
		}
		music.setLoop(true);
		music.play();



		while (this->_data->window.isOpen()) {
			this->_data->machine.ProcessStateChanges();
			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;
			if (frameTime > 0.25f) {
				frameTime = 0.25f;
			}
			currentTime = newTime;
			accumulator += frameTime;
			while (accumulator >= dt) {
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update(dt);
				accumulator -= dt;
			}
			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);

		}
	}


}
