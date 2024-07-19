#pragma once

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 880
#define SPLASH_STATE_SHOW_TIME 3.0
#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/Splash Background.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/res/Main_Menu_Background.png"
#define GAME_BACKGROUND_FILEPATH "Resources/res/Game Background.png"
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/res/GameOverBackground.png"
#define LOADING_BACKGROUND_FILEPATH "Resources/res/Loading_Background.jpg"
#define REPLAY_BACKGROUND_FILEPATH "Resources/res/replay_Background.jpg"
#define RULES_BACKGROUND_FILEPATH "Resources/res/rulesBackground.png"
#define RANKING_BACKGROUND_FILEPATH "Resources/res/rankingBackground.png"

#define BLITZ_MODE_BACKGROUND_FILEPATH "Resources/res/blitzMode.png"
#define CLASSIC_MODE_BACKGROUND_FILEPATH "Resources/res/classicMode.png"

#define CURSOR_FILEPATH "Resources/res/cursor.png"

#define PLAY_BUTTON_FILEPATH "Resources/res/play.png"
#define SHOW_COMPUTER_SOLUTION_BUTTON_FILEPATH "Resources/res/showComputerSolutionButton.png"
#define RESTART_BUTTON_FILEPATH "Resources/res/restartButton.png"
#define BACK_TO_MODES_BUTTON_FILEPATH "Resources/res/backToModesButton.png"
#define RED_BUTTON_FILEPATH "Resources/res/red_button.png"
#define YELLOW_BUTTON_FILEPATH "Resources/res/yellow_button.png"
#define BLUE_BUTTON_FILEPATH "Resources/res/blue_button.png"
#define ORANGE_BUTTON_FILEPATH "Resources/res/orange_button.png"
#define GREEN_BUTTON_FILEPATH "Resources/res/green_button.png"
#define VIOLET_BUTTON_FILEPATH "Resources/res/violet_button.png"
#define RULES_CONTINUE_BUTTON "Resources/res/start.png"

#define TEXT_BOX_FILEPATH "Resources/res/textBox.png"

#define EXIT_BUTTON_FILEPATH "Resources/res/exit_button.png"
#define FORWARD_BUTTON_FILEPATH "Resources/res/forwardButton.png"
#define BACKWARD_BUTTON_FILEPATH "Resources/res/backwardButton.png"
#define RULES_BUTTON_FILEPATH "Resources/res/rulesButton.png"
#define RANKING_BUTTON_FILEPATH "Resources/res/rankingButton.png"
#define LOG_OUT_BUTTON_FILEPATH "Resources/res/logOut.png"

#define LOADING_FONT_FILEPATH "Resources/fonts/Mkpixelproject-LJEW.ttf"
#define GAME_OVER_FONT_FILEPATH "Resources/fonts/AnneSans-ellp.ttf"
#define LEVEL_FONT_FILEPATH "Resources/fonts/VCR_OSD_MONO_1.001.ttf"


enum GameStates {
	eReady,
	eplaying,
	eGameOver
};


#define TIME_BEFORE_GAME_OVER_APPEARS 1.5f;
