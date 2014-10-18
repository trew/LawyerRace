/*
    Lawyer Race - A game about escaping the law
    Copyright (C) 2012 Samuel Andersson

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "GameState.hpp"
#include <sstream>
#include <iostream>
#include "Log.hpp"

GameState::GameState(GameEngine* engine) : AbstractState(engine), entityManager(EntityManager::Instance()) {
    m_player[0] = NULL;
    m_player[1] = NULL;
    m_player[2] = NULL;
    m_player[3] = NULL;
}

GameState::~GameState() {
}


/* RUN ONCE FUNCTIONS */

bool GameState::init() {
	///Initialize all

	window = GameEngine::window;
	screenSurface = GameEngine::screenSurface;

	LOG_DEBUG << "Loading fonts...\n";
	if ((Text::standard_font[12] = TTF_OpenFont((config::path + "font/VeraMono.ttf").c_str(), 12)) == NULL)
		LOG_ERROR << "Loading \"" << config::path << "font/VeraMono.ttf\" failed.\n";
	if ((Text::standard_font[48] = TTF_OpenFont((config::path + "font/VeraMono.ttf").c_str(), 48)) == NULL)
		LOG_ERROR << "Loading \"" << config::path << "font/VeraMono.ttf\" failed.\n";
	if ((Text::standard_font[72] = TTF_OpenFont((config::path + "font/VeraMono.ttf").c_str(), 72)) == NULL)
		LOG_ERROR << "Loading \"" << config::path << "font/VeraMono.ttf\" failed.\n";

	LOG_DEBUG << "Loading players...\n";
	for (int i = 0; i < config::NUM_OF_PLAYERS; i++)
	{
		m_player[i] = entityManager->create<Player>(config::path + config::P_SRC[i], 0.f, 0.f, config::KEYSET[i]);
		m_player[i]->centerVertical(0, config::W_HEIGHT);
	}

	if (config::NUM_OF_PLAYERS == 1) {
		m_player[0]->centerHorizontal(0, config::W_WIDTH);
	}
	else if (config::NUM_OF_PLAYERS == 2) {
		m_player[0]->centerHorizontal(0, (int)(config::W_WIDTH - (m_player[0]->getWidth() * 3)));
		m_player[1]->centerHorizontal((int)(m_player[1]->getWidth() * 3), config::W_WIDTH);
	}
	else if (config::NUM_OF_PLAYERS == 3) {
		m_player[0]->centerHorizontal(0, (int)(config::W_WIDTH - (m_player[0]->getWidth() * 6)));
		m_player[1]->centerHorizontal(0, config::W_WIDTH);
		m_player[2]->centerHorizontal((int)(m_player[2]->getWidth() * 6), config::W_WIDTH);
	}
	else if (config::NUM_OF_PLAYERS == 4) {
		m_player[0]->centerHorizontal(0, (config::W_WIDTH - (int)(m_player[0]->getWidth() * 9)));
		m_player[1]->centerHorizontal(0, (config::W_WIDTH - (int)(m_player[0]->getWidth() * 3)));
		m_player[2]->centerHorizontal((int)(m_player[1]->getWidth() * 3), config::W_WIDTH);
		m_player[3]->centerHorizontal((int)(m_player[2]->getWidth() * 9), config::W_WIDTH);
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

void GameState::cleanup() {
    std::map<int, TTF_Font*>::iterator it_font = Text::standard_font.begin();
    while(it_font != Text::standard_font.end()) {
        TTF_CloseFont((*it_font).second);
        it_font++;
    }

	for (Text* text : Text::s_textList) {
		delete text;
	}

    Player::currentPlayerNum = 0;
	entityManager->clear();
    Text::s_textList.clear();
}
/* END RUN ONCE FUNCTIONS */



/* GAMELOOP FUNCTIONS*/
void GameState::handleEvent(SDL_Event &ev) {
    if(currentInGameState == Play) {
        if (ev.type == SDL_KEYDOWN) {
            //Handle movement input
            //TODO: Also set speed to max available speed
			for (auto& e : entityManager->getAll<Player>()) {
				Player* p = reinterpret_cast<Player*>(e);
				p->handleEvent(ev);
			}
        }
    } else if (currentInGameState == GameOver) {
        if (ev.type == SDL_KEYDOWN) {
            int c = 1;
			for (auto& e : entityManager->getAll<Player>()) {
				Player* p = reinterpret_cast<Player*>(e);
                std::cout << "Player " << c << ": " <<  p->getScore() << std::endl;
                c++;
            }
			getEngine()->exit();
        }
    }
}

void GameState::copyDataForInterpolation() {
	for (auto& e : entityManager->getAllEntities()) {
		e->copyDataForInterpolation();
	}
}

void GameState::update(float timeStep) {
	entityManager->refresh();

	if(currentInGameState == Play) {
		for (auto& e : entityManager->getAll<Player>()) {
			Player* p = reinterpret_cast<Player*>(e);
			if (!p->isDead())
                p->update(timeStep);
        }

		for (auto& e : entityManager->getAll<Rock>()) {
			Rock* r = reinterpret_cast<Rock*>(e);
			r->update(timeStep);
        }

		for (auto& e : entityManager->getAll<Enemy>()) {
			Enemy* en = reinterpret_cast<Enemy*>(e);
			en->update(timeStep);
        }

        checkForCollision();

        createDollar();
        createEnemy();
        createRock();

        if(isGameOver() && currentInGameState != GameOver) {
            //ALL PLAYERS DIED!
            currentInGameState = GameOver;
            Text::s_textList.push_back(new Text("Press key to exit to menu", 48, 0, 0, 255, 255, 255));
            Text::s_textList.back()->centerHorizontal(0,config::W_WIDTH);
            Text::s_textList.back()->bottomAlign(config::W_HEIGHT, 20);
        }
    }
    else if (currentInGameState == CountDown) {
        if(countDown_compareTime < SDL_GetTicks()) {
            text_countDown->updateText(countDown);
            text_countDown->centerHorizontal(0,config::W_WIDTH);
            text_countDown->centerVertical(0,config::W_HEIGHT / 2);
            countDown_compareTime += 1000;
            countDown--;
            if (countDown < 0) {
                Text::s_textList.remove(text_countDown);
                currentInGameState = Play;
            }
        }
    }

#ifdef WIN32
    std::stringstream ss;
    ss << config::WINDOW_TEXT << "    " << FPS::FPSControl.GetFPS();
	SDL_SetWindowTitle(window, ss.str().c_str());
#endif
}


void GameState::render(float timeAlpha) {
	for (auto& e : entityManager->getAll<Dollar>()) {
		Dollar* d = reinterpret_cast<Dollar*>(e);
		d->render(screenSurface, timeAlpha);
    }

	for (auto& e : entityManager->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
		p->render(screenSurface, timeAlpha);
    }

	for (auto& e : entityManager->getAll<Enemy>()) {
		Enemy* en = reinterpret_cast<Enemy*>(e);
		en->render(screenSurface, timeAlpha);
    }

	for (auto& e : entityManager->getAll<Rock>()) {
		Rock* r = reinterpret_cast<Rock*>(e);
		r->render(screenSurface, timeAlpha);
    }

	for (Text* text : Text::s_textList) {
		text->render(screenSurface);
    }

    if(currentInGameState == GameOver) {
        //Render gameover screen here
    }

	SDL_UpdateWindowSurface(window);
}
/* END GAMELOOP FUNCTIONS */


void GameState::pause() {
}

void GameState::resume() {
}


/* SUPPORTIVE FUNCTIONS */

void GameState::checkForCollision() {
	for (auto& e : entityManager->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
        if (p->isDead()) {
            continue;
        }

        //Check collision with dollar
		for (auto& e : entityManager->getAll<Dollar>()) {
			Dollar* d = reinterpret_cast<Dollar*>(e);
			if (Entity::collides(p, d)) {
				// TODO: check if dollar is scheduled for removal!
				p->incScore(1);
				entityManager->remove(d);
			}
        }

        //Check collision with enemy
		for (auto& e : entityManager->getAll<Enemy>()) {
			Enemy* en = reinterpret_cast<Enemy*>(e);
            if(Entity::collides(p, en)) {
                //Player collides with enemy
				p->kill();
				goto continueOuterLoop;
            }
        }

		//Check collision with rocks
		for (auto& e : entityManager->getAll<Rock>()) {
			Rock* r = reinterpret_cast<Rock*>(e);
			if (Entity::collides(p, r)) {
				//Player collides with rock
				entityManager->remove(r);
				p->kill();
				goto continueOuterLoop;
			}
		}

		continueOuterLoop:;
    }

}

void GameState::createDollar() {
	auto& dollarList = entityManager->getAll<Dollar>();
    while (dollarList.size() < unsigned(Player::alivePlayers)) {
		Dollar* newDollar = entityManager->create<Dollar>(config::path + config::D_SRC);
        int newDollar_xPos = 0;
        int newDollar_yPos = 0;
        bool valid = false;
        while(!valid) { //Loop until valid pos is found
            valid = true;
            newDollar_xPos = rand() % (config::W_WIDTH - (int)newDollar->getWidth())   ;
            newDollar_yPos = rand() % (config::W_HEIGHT - (int)newDollar->getHeight()) ;
			newDollar->setX(static_cast<float>(newDollar_xPos));
			newDollar->setY(static_cast<float>(newDollar_yPos));

			for (auto& e : entityManager->getAll<Player>()) {
				Player* p = reinterpret_cast<Player*>(e);
				if (Entity::collides(p, newDollar)) {
                    valid = false;
                    break;
                }
            }
        }
        newDollar->setX(static_cast<float>(newDollar_xPos));
        newDollar->setY(static_cast<float>(newDollar_yPos));
		newDollar->copyDataForInterpolation();
    }
}

void GameState::createEnemy() {
	auto& enemyList = entityManager->getAll<Enemy>();
    if(enemyList.size() >= static_cast<unsigned int>(config::MAX_ENEMIES)) return;

    unsigned int highestCurrentScore = getHighestCurrentScore();

    while( enemyList.size() < ((highestCurrentScore / 5) +1) ) {
        int e_xPos;
        int e_yPos;
        //Create enemy out of screen. Randomize up/down, left/right
        if ((rand() % 2) == 1) {
            e_xPos = -config::E_WIDTH;
            e_yPos = -config::E_HEIGHT;
        } else {
            e_xPos = config::W_WIDTH+1;
            e_yPos = config::W_HEIGHT+1;
        }

        //Randomize x and y-position.
        if ((rand() % 2) == 1)  {
            e_xPos = (rand() % (config::W_WIDTH - config::E_WIDTH));
        } else {
            e_yPos = (rand() % (config::W_HEIGHT - config::E_HEIGHT));
        }

        //Finally, create new enemy
		entityManager->create<Enemy>(config::path + config::E_SRC, (float)e_xPos, (float)e_yPos);
    }

}

void GameState::createRock() {
	// this function must be called right after entityManager->refresh() is called
    int highestCurrentScore = getHighestCurrentScore() - ((config::ENEMIES_BEFORE_ROCK -1) * 5);
    if(highestCurrentScore < 0) highestCurrentScore = 0;
    std::size_t max_amount_of_rocks = std::size_t(highestCurrentScore / 5);
    if (max_amount_of_rocks > std::size_t(config::MAX_ROCKS)) max_amount_of_rocks = std::size_t(config::MAX_ROCKS);
	auto& rockList = entityManager->getAll<Rock>();

	while ( rockList.size() < max_amount_of_rocks ) {
        int r_yPos = -config::MAX_R_HEIGHT;

        int rockType = (rand() % 10 +1);
        if (rockType >= 7 && rockType <= 9) {
            int r_xPos = (rand() % (config::W_WIDTH - config::R_WIDTH[1]));
			entityManager->create<Rock>(config::path + config::R_SRC[1], (float)r_xPos, (float)r_yPos, 2);
        }
        else if(rockType == 10) {
            int r_xPos = (rand() % (config::W_WIDTH - config::R_WIDTH[2]));
			entityManager->create<Rock>(config::path + config::R_SRC[2], (float)r_xPos, (float)r_yPos, 3);
        }
        else {
            int r_xPos = (rand() % (config::W_WIDTH - config::R_WIDTH[0]));
			entityManager->create<Rock>(config::path + config::R_SRC[0], (float)r_xPos, (float)r_yPos, 1);
        }
    }
}

bool GameState::isGameOver() {
	for (auto& e : entityManager->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
		if (!(p->isDead())) {
            return false;
        }
    }
    return true;
}

int GameState::getHighestCurrentScore() {
    int highestCurrentScore = 0;
	for (auto& e : entityManager->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
		if (p->getScore() > highestCurrentScore)
            highestCurrentScore = p->getScore();
    }
    return highestCurrentScore;
}

std::list<Player*> GameState::getWinners() {
    std::list<Player*> returnList;
    int highestScore = getHighestCurrentScore();
	for (auto& e : entityManager->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
		if (p->getScore() == highestScore) {
            returnList.push_back(p);
        }
    }
    return returnList;
}
/* END SUPPORTIVE FUNCTIONS */


