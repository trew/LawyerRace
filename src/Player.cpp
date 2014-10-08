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


#include "Player.hpp"
#include <iostream>
#include <sstream>

std::list<Player*> Player::s_playerList;
int Player::alivePlayers = 0;
int Player::currentPlayerNum = 0;

Player::Player(const std::string _fileName, KeySet _keySet)
: MovingEntity(_fileName, 0, 0, config::P_VELOCITY, config::P_VELOCITY),
  m_direction(DOWN),
  m_score(0),
  dead(false)
{
    m_width = (float)config::P_WIDTH;
    m_height = (float)config::P_HEIGHT;

    currentPlayerNum++;
    alivePlayers++;
    playerNum = currentPlayerNum;

         if(playerNum == 1) score_text = new Text(" ", 12, 0, 0, 30, 30, 255);
    else if(playerNum == 2) score_text = new Text(" ", 12, 0, 0,230, 0, 0);
    else if(playerNum == 3) score_text = new Text(" ", 12, 0, 0, 0 , 230, 0);
    else if(playerNum == 4) score_text = new Text(" ", 12, 0, 0,230,230, 0);
    updateScore();
    loadKeySet(_keySet);
}

Player::Player(const std::string _fileName, const float _xPos, const float _yPos, KeySet _keySet)
: MovingEntity(_fileName, _xPos, _yPos, config::P_VELOCITY, config::P_VELOCITY),
  m_direction(DOWN),
  m_score(0),
  dead(false)
{
    m_width = (float)config::P_WIDTH;
    m_height = (float)config::P_HEIGHT;

    currentPlayerNum++;
    alivePlayers++;
    playerNum = currentPlayerNum;

         if(playerNum == 1) score_text = new Text(" ", 12, 0, 0, 30, 30, 255);
    else if(playerNum == 2) score_text = new Text(" ", 12, 0, 0,230, 0, 0);
    else if(playerNum == 3) score_text = new Text(" ", 12, 0, 0, 0 , 230, 0);
    else if(playerNum == 4) score_text = new Text(" ", 12, 0, 0,230,230, 0);
    updateScore();
    loadKeySet(_keySet);
}

Player::~Player() {
}

void Player::loadKeySet(const KeySet &set)
{
    m_keySet = set;
}

void Player::draw(SDL_Surface* _destSurf, float timeAlpha) {
    if(!m_visible) return;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(lerp(m_prevX, m_xPos, timeAlpha));
	destRect.y = static_cast<int>(lerp(m_prevY, m_yPos, timeAlpha));
    destRect.h = (int)m_height;
    destRect.w = (int)m_width;

    SDL_Rect srcRect;
    srcRect.x = 0;
    if(dead)
        srcRect.y = (int)(m_height * 4);
    else
        srcRect.y = (int)(m_height * m_direction);
    srcRect.h = (int)m_height;
    srcRect.w = (int)m_width;

    SDL_BlitSurface(m_surf, &srcRect, _destSurf, &destRect);

    score_text->draw(_destSurf, timeAlpha);
}

void Player::handleEvent(SDL_Event& ev) {
    if (dead) return;
    if(ev.type == SDL_KEYDOWN) {
        if (ev.key.keysym.sym == m_keySet.K_LEFT) {
			setMoving(true);
            setDirection(LEFT);
        }
        else if (ev.key.keysym.sym == m_keySet.K_RIGHT) {
			setMoving(true);
            setDirection(RIGHT);
        }
        else if (ev.key.keysym.sym == m_keySet.K_UP) {
			setMoving(true);
			setDirection(UP);
        }
        else if (ev.key.keysym.sym == m_keySet.K_DOWN) {
			setMoving(true);
			setDirection(DOWN);
        }
        else if (ev.key.keysym.sym == m_keySet.K_STOP) {
            if (config::PLAYER_STOP_ENABLED)
				setMoving(!isMoving());
        }
    }
}


void Player::update(float timeStep) {
    if (!isMoving() || dead) return;    //Return if no movement

	m_prevX = m_xPos;
	m_prevY = m_yPos;

	if (m_direction == UP) {
        m_yPos -= (getVelocityY() * timeStep);
        if (m_yPos < 0) m_yPos = 0; //Prevent from going out of screen
    }
    else if (m_direction == DOWN) {
		m_yPos += (getVelocityY() * timeStep);
        if (m_yPos + m_height > config::W_HEIGHT) m_yPos = static_cast<float>(config::W_HEIGHT - m_height); //Prevent from going out of screen
    }

    else if (m_direction == LEFT) {
		m_xPos -= (getVelocityX() * timeStep);
        if (m_xPos < 0) m_xPos = 0; //Prevent from going out of screen
    }
    else if (m_direction == RIGHT) {
		m_xPos += (getVelocityX() * timeStep);
        if (m_xPos + m_width > config::W_WIDTH) m_xPos = static_cast<float>(config::W_WIDTH - m_width); //Prevent from going out of screen
    }

}

void Player::updateScore() {
    std::stringstream ss;
    if (dead) {
        ss << "Player " << playerNum << ": " << m_score << " DEAD!";
    } else {
        ss << "Player " << playerNum << ": " << m_score;
    }
    score_text->updateText(ss.str());

    //Position text correctly
    if (config::NUM_OF_PLAYERS == 4) {
        float newXPos = static_cast<float>((config::W_WIDTH / 4) * (playerNum-1) + 20);
        score_text->setXPos(newXPos);
    }
    else if (config::NUM_OF_PLAYERS == 3) {
        if (playerNum == 1) 
            score_text->leftAlign(0, 10);
        else if (playerNum == 2) 
            score_text->centerHorizontal(0, config::W_WIDTH);
        else if (playerNum == 3) 
            score_text->rightAlign(config::W_WIDTH, 10);
    }
    else if (config::NUM_OF_PLAYERS == 2) {
        if (playerNum == 1)
            score_text->leftAlign(0, 10);
        else if (playerNum == 2) 
            score_text->rightAlign(config::W_WIDTH, 10);
    } 
    else if (config::NUM_OF_PLAYERS == 1) {
        score_text->centerHorizontal(0, config::W_WIDTH);
    }
}

void Player::incScore(int _score) {
    m_score += _score;
    updateScore();
}

void Player::kill() {
    dead = true;
	setMoving(false);
    alivePlayers--;
    updateScore();
}

bool Player::isDead() const{
    return dead;
}

int Player::getScore() const {
    return m_score;
}


void Player::setDirection(Direction newDir) {
    m_direction = newDir;
}
