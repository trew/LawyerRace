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

GameState::GameState(GameEngine* engine) : AbstractState(engine) {
    m_player[0] = NULL;
    m_player[1] = NULL;
    m_player[2] = NULL;
    m_player[3] = NULL;
}

GameState::~GameState() {
}


/* RUN ONCE FUNCTIONS */

void GameState::Cleanup() {
    std::map<int, TTF_Font*>::iterator it_font = Text::standard_font.begin();
    while(it_font != Text::standard_font.end()) {
        TTF_CloseFont((*it_font).second);
        it_font++;
    }

    //Delete all sprites
    std::list<Sprite*>::iterator it_Sprite = Sprite::s_spriteList.begin();
    while(it_Sprite != Sprite::s_spriteList.end()) {
        if ((*it_Sprite) != NULL) {
            delete (*it_Sprite); (*it_Sprite) = NULL;
        }
        it_Sprite++;
    }

    Player::currentPlayerNum = 0;
    Player::s_playerList.clear();
    Enemy::s_enemyList.clear();
    Rock::s_rockList.clear();
    Entity::s_entityList.clear();
    Sprite::s_spriteList.clear();
    Dollar::s_dollarList.clear();
    Text::s_textList.clear();
}
/* END RUN ONCE FUNCTIONS */



/* GAMELOOP FUNCTIONS*/
void GameState::HandleEvent(SDL_Event &ev) {
    if(currentInGameState == Play) {
        if (ev.type == SDL_KEYDOWN) {
            //Handle movement input
            //TODO: Also set speed to max available speed
            auto it_player = Player::s_playerList.begin();
            while(it_player != Player::s_playerList.end()) {
                (*it_player)->handleEvent(ev);
                it_player++;
            }
        }
    } else if (currentInGameState == GameOver) {
        if (ev.type == SDL_KEYDOWN) {
            auto it_player = Player::s_playerList.begin();
            int c = 1;
            while(it_player != Player::s_playerList.end()) {
                std::cout << "Player " << c << ": " <<  (*it_player)->getScore() << std::endl;
                it_player++; c++;
            }
			GetEngine()->Exit();
        }
    }
}

void GameState::Update(float timeStep) {
    if(currentInGameState == Play) {
        auto it_player = Player::s_playerList.begin();
        while(it_player != Player::s_playerList.end()) {
            if(!(*it_player)->isDead())
                (*it_player)->update(timeStep);
            it_player++;
        }

        auto it_rock = Rock::s_rockList.begin();
        while(it_rock != Rock::s_rockList.end()) {
            (*it_rock)->update(timeStep);
            it_rock++;
        }

        auto it_enemy = Enemy::s_enemyList.begin();
        while(it_enemy != Enemy::s_enemyList.end()) {
            (*it_enemy)->update(timeStep);
            it_enemy++;
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


void GameState::Render(float timeAlpha) {
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

    auto it_dollar = Dollar::s_dollarList.begin();
    while(it_dollar != Dollar::s_dollarList.end()) {
		(*it_dollar)->draw(screenSurface);
        it_dollar++;
    }

    auto it_player = Player::s_playerList.begin();
    while(it_player != Player::s_playerList.end()) {
		(*it_player)->draw(screenSurface, timeAlpha);
        it_player++;
    }

    auto it_enemy = Enemy::s_enemyList.begin();
    while(it_enemy != Enemy::s_enemyList.end()) {
		(*it_enemy)->draw(screenSurface, timeAlpha);
        it_enemy++;
    }

    auto it_rock = Rock::s_rockList.begin();
    while(it_rock != Rock::s_rockList.end()) {
		(*it_rock)->draw(screenSurface, timeAlpha);
        it_rock++;
    }

    std::list<Text*>::const_iterator it_text = Text::s_textList.begin();
    while(it_text != Text::s_textList.end()) {
		(*it_text)->draw(screenSurface, timeAlpha);
        it_text++;
    }

    if(currentInGameState == GameOver) {
        //Render gameover screen here
    }

	SDL_UpdateWindowSurface(window);
}
/* END GAMELOOP FUNCTIONS */


void GameState::Pause() {
}

void GameState::Resume() {
}


/* SUPPORTIVE FUNCTIONS */

void GameState::checkForCollision() {
    std::list<Player*>::iterator it_player = Player::s_playerList.begin();
    std::list<Enemy*>::iterator it_enemy;
//  std::list<Powerup*>::iterator it_powerup;
    std::list<Dollar*>::iterator it_dollar;
    std::list<Rock*>::iterator it_rock;

    while(it_player != Player::s_playerList.end()) {
        if ((*it_player)->isDead()) {
            it_player++;
            continue;
        }
        //TODO::::!!!
        /* 
        it_powerup = Powerup::s_powerupList.begin();
        while(it_powerup != Powerup::s_powerupList.end()) {
            if(Entity::collides((*it_powerup), (*it_player))) {
                //Player collides with powerup
            }
            it_powerup++;
        }
        */

        //Check collision with dollar
        it_dollar = Dollar::s_dollarList.begin();
        Dollar* tmp_dollar = NULL;
        while(it_dollar != Dollar::s_dollarList.end()) {
            if(Entity::collides((*it_player), (*it_dollar))) {
                //Player collides with dollar
                tmp_dollar = (*it_dollar);
            }
            it_dollar++;
        }
        if (tmp_dollar != NULL) {
            (*it_player)->incScore(1);
            Dollar::s_dollarList.remove(tmp_dollar);
            Sprite::s_spriteList.remove(tmp_dollar);
            delete tmp_dollar; tmp_dollar = NULL;
        }

        //Check collision with enemy
        it_enemy = Enemy::s_enemyList.begin();
        Player* tmp_player = NULL;
        while(it_enemy != Enemy::s_enemyList.end()) {
            if(Entity::collides((*it_player), (*it_enemy))) {
                //Player collides with enemy
                tmp_player = (*it_player);
            }
            it_enemy++;
        }
        if(tmp_player != NULL) {
            tmp_player->kill();
        }

        //Check collision with rocks
        it_rock = Rock::s_rockList.begin();
        tmp_player = NULL;
        while(it_rock != Rock::s_rockList.end()) {
            if(Entity::collides((*it_player), (*it_rock))) {
                //Player collides with rock
                tmp_player = (*it_player);
                (*it_rock)->setExpired(true);
            }
            it_rock++;
        }
        if(tmp_player != NULL) {
            tmp_player->kill();

        }

        it_player++;
    }

}

void GameState::createDollar() {
    auto it_player = Player::s_playerList.begin();
    while (Dollar::s_dollarList.size() < unsigned(Player::alivePlayers)) {
        Dollar* newDollar = new Dollar(config::path + config::D_SRC, 0, 0);
        int newDollar_xPos = 0;
        int newDollar_yPos = 0;
        bool valid = false;
        while(!valid) { //Loop until valid pos is found
            valid = true;
            newDollar_xPos = rand() % (config::W_WIDTH - (int)newDollar->getWidth())   ;
            newDollar_yPos = rand() % (config::W_HEIGHT - (int)newDollar->getHeight()) ;

            while(it_player != Player::s_playerList.end()) {
                if(Entity::collides((*it_player), newDollar)) {
                    valid = false;
                    break;
                }
                it_player++;
            }
        }
        newDollar->setX(static_cast<float>(newDollar_xPos));
        newDollar->setY(static_cast<float>(newDollar_yPos));
        Dollar::s_dollarList.push_back(newDollar);
    }
}

void GameState::createEnemy() {
    if(Enemy::s_enemyList.size() >= static_cast<unsigned int>(config::MAX_ENEMIES)) return;

    unsigned int highestCurrentScore = getHighestCurrentScore();

    while( Enemy::s_enemyList.size() < ((highestCurrentScore / 5) +1) ) {
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
		Enemy* enemy = new Enemy(config::path + config::E_SRC, (float)e_xPos, (float)e_yPos);
        Enemy::s_enemyList.push_back(enemy);
    }

}

void GameState::createRock() {
    //Remove expired rocks
    auto it_rock = Rock::s_rockList.begin();
    while(it_rock != Rock::s_rockList.end()) {
        if((*it_rock)->isExpired()) {
            Sprite::s_spriteList.remove((*it_rock));
            delete (*it_rock);
            Rock::s_rockList.erase(it_rock++);
        }
        else {
            it_rock++;
        }
    }

    int highestCurrentScore = getHighestCurrentScore() - ((config::ENEMIES_BEFORE_ROCK -1) * 5);
    if(highestCurrentScore < 0) highestCurrentScore = 0;
    int max_amount_of_rocks = highestCurrentScore / 5;
    if (max_amount_of_rocks > config::MAX_ROCKS) max_amount_of_rocks = config::MAX_ROCKS;

    while ( int(Rock::s_rockList.size()) < max_amount_of_rocks) {
        int r_yPos = -config::MAX_R_HEIGHT;

        int rockType = (rand() % 10 +1);
        if (rockType >= 7 && rockType <= 9) {
            int r_xPos = (rand() % (config::W_WIDTH - config::R_WIDTH[1]));
            Rock::s_rockList.push_back(new Rock(config::path + config::R_SRC[1], (float)r_xPos, (float)r_yPos, 2));
        }
        else if(rockType == 10) {
            int r_xPos = (rand() % (config::W_WIDTH - config::R_WIDTH[2]));
            Rock::s_rockList.push_back(new Rock(config::path + config::R_SRC[2], (float)r_xPos, (float)r_yPos, 3));
        }
        else {
            int r_xPos = (rand() % (config::W_WIDTH - config::R_WIDTH[0]));
            Rock::s_rockList.push_back(new Rock(config::path + config::R_SRC[0], (float)r_xPos, (float)r_yPos, 1));
        }
    }
}

bool GameState::isGameOver() {
    auto it_player = Player::s_playerList.begin();
    while(it_player != Player::s_playerList.end()) {
        if( !((*it_player)->isDead()) ) {
            return false;
        }
        it_player++;
    }
    return true;
}

int GameState::getHighestCurrentScore() {
    int highestCurrentScore = 0;
    auto it_player = Player::s_playerList.begin();
    while(it_player != Player::s_playerList.end()) {
        if ((*it_player)->getScore() > highestCurrentScore) 
            highestCurrentScore = (*it_player)->getScore();
        it_player++;
    }
    return highestCurrentScore;
}

void GameState::RenderResult() {
    std::list<Player*> winners = getWinners();
}

std::list<Player*> GameState::getWinners() {
    std::list<Player*> returnList;
    auto it_player = Player::s_playerList.begin();
    int highestScore = getHighestCurrentScore();
    while(it_player != Player::s_playerList.end()) {
        if((*it_player)->getScore() == highestScore) {
            returnList.push_back((*it_player));
        }
        it_player++;
    }
    return returnList;
}
/* END SUPPORTIVE FUNCTIONS */


