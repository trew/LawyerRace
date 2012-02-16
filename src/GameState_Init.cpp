#include "GameState.h"
#include "Log.h"

bool GameState::Init() {
///Initialize all
	
	Player::numOfPlayers = 1; //TEMPORARY SOLUTION UNTIL MENUSTATES IS IMPLEMENTED.

	mainScreen = Game::mainScreen;

	LOG_DEBUG("Loading fonts...");
    if((Text::standard_font[12] = TTF_OpenFont( (config::path + "/font/VeraMono.ttf").c_str(), 12)) == NULL) 
		LOG_DEBUG("Loading \"" + config::path + "/font/VeraMono.ttf\" failed."); 
	if((Text::standard_font[48] = TTF_OpenFont( (config::path + "/font/VeraMono.ttf").c_str(), 48)) == NULL)
		LOG_DEBUG("Loading \"" + config::path + "/font/VeraMono.ttf\" failed."); 
	if((Text::standard_font[72] = TTF_OpenFont( (config::path + "/font/VeraMono.ttf").c_str(), 72)) == NULL)
		LOG_DEBUG("Loading \"" + config::path + "/font/VeraMono.ttf\" failed."); 

	SetupKeySets();

    LOG_DEBUG("Loading players...");	
    if (!(m_player_1 = new Player(config::P1_SRC, 0, 0, m_p1_keySet))) return false;
	m_player_1->centerVertical(0, config::W_HEIGHT);
	if(Player::numOfPlayers > 1) {
		if (!(m_player_2 = new Player(config::P2_SRC, 0, 0, m_p2_keySet))) return false;
		m_player_2->centerVertical(0, config::W_HEIGHT);
	}
	if(Player::numOfPlayers > 2) {
		if (!(m_player_3 = new Player(config::P3_SRC, 0, 0, m_p3_keySet))) return false;
		m_player_3->centerVertical(0, config::W_HEIGHT);
	}
	if(Player::numOfPlayers > 3) {
		if (!(m_player_4 = new Player(config::P4_SRC, 0, 0, m_p4_keySet))) return false;
		m_player_4->centerVertical(0, config::W_HEIGHT);
	}
	
	Player::s_playerList.push_back(m_player_1);
	if(Player::numOfPlayers > 1)
		Player::s_playerList.push_back(m_player_2);
	if(Player::numOfPlayers > 2)
		Player::s_playerList.push_back(m_player_3);
	if(Player::numOfPlayers > 3)
		Player::s_playerList.push_back(m_player_4);
	
	if(Player::numOfPlayers == 1) {
		m_player_1->centerHorizontal(0, config::W_WIDTH);
	} else if(Player::numOfPlayers == 2) {
		m_player_1->centerHorizontal(0, (config::W_WIDTH - (m_player_1->getWidth() * 3)));
		m_player_2->centerHorizontal((m_player_2->getWidth() * 3), config::W_WIDTH);
	} else if(Player::numOfPlayers == 3) {
		m_player_1->centerHorizontal(0, (config::W_WIDTH - (m_player_1->getWidth() * 6)));
		m_player_2->centerHorizontal(0, config::W_WIDTH);
		m_player_3->centerHorizontal((m_player_3->getWidth() * 6), config::W_WIDTH);
	} else if(Player::numOfPlayers == 4) {
		m_player_1->centerHorizontal(0, (config::W_WIDTH - (m_player_1->getWidth() * 9)));
		m_player_2->centerHorizontal(0, (config::W_WIDTH - (m_player_1->getWidth() * 3)));
		m_player_3->centerHorizontal((m_player_2->getWidth() * 3), config::W_WIDTH);
		m_player_4->centerHorizontal((m_player_3->getWidth() * 9), config::W_WIDTH);
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

void GameState::SetupKeySets() {
	//Player 1
	m_p1_keySet.K_DOWN = SDLK_DOWN;
	m_p1_keySet.K_UP = SDLK_UP;
	m_p1_keySet.K_LEFT = SDLK_LEFT;
	m_p1_keySet.K_RIGHT = SDLK_RIGHT;
	m_p1_keySet.K_STOP = SDLK_RCTRL;
	//Player 2
	m_p2_keySet.K_DOWN = SDLK_s;
	m_p2_keySet.K_UP = SDLK_w;
	m_p2_keySet.K_LEFT = SDLK_a;
	m_p2_keySet.K_RIGHT = SDLK_d;
	m_p2_keySet.K_STOP = SDLK_LCTRL;
	//Player 3
	m_p3_keySet.K_DOWN = SDLK_k;
	m_p3_keySet.K_UP = SDLK_i;
	m_p3_keySet.K_LEFT = SDLK_j;
	m_p3_keySet.K_RIGHT = SDLK_l;
	m_p3_keySet.K_STOP = SDLK_SPACE;
	//Player 4
	m_p4_keySet.K_DOWN = SDLK_KP5;
	m_p4_keySet.K_UP = SDLK_KP8;
	m_p4_keySet.K_LEFT = SDLK_KP4;
	m_p4_keySet.K_RIGHT = SDLK_KP6;
	m_p4_keySet.K_STOP = SDLK_KP0;

	if (Player::numOfPlayers == 1) {
		m_p1_keySet.K_STOP = SDLK_SPACE;
	}

}
