#include "GameState.h"
#include "Log.h"

bool GameState::Init() {
///Initialize all
	
	config::NUM_OF_PLAYERS = 1; //TEMPORARY SOLUTION UNTIL MENUSTATES IS IMPLEMENTED.
	
	mainScreen = Game::mainScreen;

	LOG_DEBUG("Loading fonts...");
    if((Text::standard_font[12] = TTF_OpenFont( (config::path + "/font/VeraMono.ttf").c_str(), 12)) == NULL) 
		LOG_DEBUG("Loading \"" + config::path + "/font/VeraMono.ttf\" failed."); 
	if((Text::standard_font[48] = TTF_OpenFont( (config::path + "/font/VeraMono.ttf").c_str(), 48)) == NULL)
		LOG_DEBUG("Loading \"" + config::path + "/font/VeraMono.ttf\" failed."); 
	if((Text::standard_font[72] = TTF_OpenFont( (config::path + "/font/VeraMono.ttf").c_str(), 72)) == NULL)
		LOG_DEBUG("Loading \"" + config::path + "/font/VeraMono.ttf\" failed."); 

	LOG_DEBUG("Loading keysets...");
	config::loadKeySets();

    LOG_DEBUG("Loading players...");	
	for (int i = 0; i < config::NUM_OF_PLAYERS; i++)
	{
	    if (!(m_player[i] = new Player(config::P_SRC[i], 0, 0, config::KEYSET[i]))) return false;
		m_player[i]->centerVertical(0, config::W_HEIGHT);
		Player::s_playerList.push_back(m_player[i]);
	}

	if(config::NUM_OF_PLAYERS == 1) {
		m_player[0]->centerHorizontal(0, config::W_WIDTH);
	} else if(config::NUM_OF_PLAYERS == 2) {
		m_player[0]->centerHorizontal(0, (config::W_WIDTH - (m_player[0]->getWidth() * 3)));
		m_player[1]->centerHorizontal((m_player[1]->getWidth() * 3), config::W_WIDTH);
	} else if(config::NUM_OF_PLAYERS == 3) {
		m_player[0]->centerHorizontal(0, (config::W_WIDTH - (m_player[0]->getWidth() * 6)));
		m_player[1]->centerHorizontal(0, config::W_WIDTH);
		m_player[2]->centerHorizontal((m_player[2]->getWidth() * 6), config::W_WIDTH);
	} else if(config::NUM_OF_PLAYERS == 4) {
		m_player[0]->centerHorizontal(0, (config::W_WIDTH - (m_player[0]->getWidth() * 9)));
		m_player[1]->centerHorizontal(0, (config::W_WIDTH - (m_player[0]->getWidth() * 3)));
		m_player[2]->centerHorizontal((m_player[1]->getWidth() * 3), config::W_WIDTH);
		m_player[3]->centerHorizontal((m_player[2]->getWidth() * 9), config::W_WIDTH);
	}

	countDown = 3;
	text_countDown = new Text(3, 72, 0, 0, 255, 255, 255);
	text_countDown->centerHorizontal(0, config::W_WIDTH);
	text_countDown->centerVertical(0, config::W_HEIGHT / 2);
	Text::s_textList.push_back(text_countDown);

	currentInGameState = CountDown;
	countDown_compareTime = SDL_GetTicks();
	return true;
}

/*void GameState::SetupKeySets() {
	//Player 1
	m_keySet[0].K_DOWN = SDLK_DOWN;
	m_keySet[0].K_UP = SDLK_UP;
	m_keySet[0].K_LEFT = SDLK_LEFT;
	m_keySet[0].K_RIGHT = SDLK_RIGHT;
	m_keySet[0].K_STOP = SDLK_RCTRL;
	//Player 2
	m_keySet[1].K_DOWN = SDLK_s;
	m_keySet[1].K_UP = SDLK_w;
	m_keySet[1].K_LEFT = SDLK_a;
	m_keySet[1].K_RIGHT = SDLK_d;
	m_keySet[1].K_STOP = SDLK_LCTRL;
	//Player 3
	m_keySet[2].K_DOWN = SDLK_k;
	m_keySet[2].K_UP = SDLK_i;
	m_keySet[2].K_LEFT = SDLK_j;
	m_keySet[2].K_RIGHT = SDLK_l;
	m_keySet[2].K_STOP = SDLK_SPACE;
	//Player 4
	m_keySet[3].K_DOWN = SDLK_KP5;
	m_keySet[3].K_UP = SDLK_KP8;
	m_keySet[3].K_LEFT = SDLK_KP4;
	m_keySet[3].K_RIGHT = SDLK_KP6;
	m_keySet[3].K_STOP = SDLK_KP0;

	if (Player::numOfPlayers == 1) {
		m_keySet[0].K_STOP = SDLK_SPACE;
	}

}*/
