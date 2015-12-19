#include <LawyerRace/Core/MenuState.hpp>
#include <LawyerRace/Core/GameState.hpp>

#include <iostream>

MenuState::MenuState() {
}

MenuState::~MenuState() {
}


/* RUN ONCE FUNCTIONS */

bool MenuState::init() {
	///Initialize all

	return true;
}

void MenuState::cleanup() {
}
/* END RUN ONCE FUNCTIONS */



/* GAMELOOP FUNCTIONS*/
bool MenuState::handleEvent(const SDL_Event &ev) {
    if (ev.type == SDL_KEYDOWN) {
		getEngine()->setState(new GameState());
    return true;
    }

    return false;
}

void MenuState::copyDataForInterpolation() {
}

void MenuState::update(float timeStep) {
}


void MenuState::render(SDL_Renderer* const renderer, float timeAlpha) {
	for (LawyerText* text : LawyerText::s_textList) {
		text->render();
    }
}
/* END GAMELOOP FUNCTIONS */


void MenuState::pause() {
}

void MenuState::resume() {
}
