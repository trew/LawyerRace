#include "LawyerRace/Core/MenuState.hpp"
#include <iostream>
#include "LawyerRace/Utils/Log.hpp"

MenuState::MenuState() {
}

MenuState::~MenuState() {
}


/* RUN ONCE FUNCTIONS */

bool MenuState::init() {
	///Initialize all

	window = getEngine()->getWindow();
	renderer = getEngine()->getRenderer();

	return true;
}

void MenuState::cleanup() {
}
/* END RUN ONCE FUNCTIONS */



/* GAMELOOP FUNCTIONS*/
void MenuState::handleEvent(SDL_Event &ev) {
    if (ev.type == SDL_KEYDOWN) {
		getEngine()->changeState(new GameState());
    }
}

void MenuState::copyDataForInterpolation() {
}

void MenuState::update(float timeStep) {
}


void MenuState::render(float timeAlpha) {
	for (Text* text : Text::s_textList) {
		text->render(renderer);
    }
}
/* END GAMELOOP FUNCTIONS */


void MenuState::pause() {
}

void MenuState::resume() {
}
