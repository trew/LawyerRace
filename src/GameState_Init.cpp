#include "GameState.hpp"
#include "Log.hpp"

bool GameState::Init() {
    ///Initialize all

    mainScreen = Game::mainScreen;

    LOG_DEBUG << "Loading fonts...\n";
    if((Text::standard_font[12] = TTF_OpenFont( (config::path + "/font/VeraMono.ttf").c_str(), 12)) == NULL) 
        LOG_ERROR << "Loading \"" << config::path << "font/VeraMono.ttf\" failed.\n";
    if((Text::standard_font[48] = TTF_OpenFont( (config::path + "/font/VeraMono.ttf").c_str(), 48)) == NULL)
        LOG_ERROR << "Loading \"" << config::path << "font/VeraMono.ttf\" failed.\n";
    if((Text::standard_font[72] = TTF_OpenFont( (config::path + "/font/VeraMono.ttf").c_str(), 72)) == NULL)
        LOG_ERROR << "Loading \"" << config::path << "font/VeraMono.ttf\" failed.\n";

    LOG_DEBUG << "Loading players...\n";
    for (int i = 0; i < config::NUM_OF_PLAYERS; i++)
    {
        if (!(m_player[i] = new Player(config::path + config::P_SRC[i], 0, 0, config::KEYSET[i]))) return false;
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
