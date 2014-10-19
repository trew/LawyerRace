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
#include "PositionHelper.h"

int Player::alivePlayers = 0;
int Player::currentPlayerNum = 0;

Player::Player(std::vector<TextureRegion*> _regions, KeySet keySet)
: Entity(_regions, 0, 0, config::P_WIDTH, config::P_HEIGHT)
{
    currentPlayerNum++;
    alivePlayers++;
    playerNum = currentPlayerNum;

	if (playerNum == 1) score_text = new Text(" ", 12, 0, 0, 30, 30, 255);
	else if (playerNum == 2) score_text = new Text(" ", 12, 0, 0, 230, 0, 0);
	else if (playerNum == 3) score_text = new Text(" ", 12, 0, 0, 0, 230, 0);
	else if (playerNum == 4) score_text = new Text(" ", 12, 0, 0, 230, 230, 0);
    updateScore();
    loadKeySet(keySet);

	setVelocity(config::P_VELOCITY, config::P_VELOCITY);
}

Player::Player(std::vector<TextureRegion*> regions, const float x, const float y, const float w, const float h, KeySet keySet)
: Entity(regions, x, y, w, h)
{
    currentPlayerNum++;
    alivePlayers++;
    playerNum = currentPlayerNum;

    if(playerNum == 1) score_text = new Text(" ", 12, 0, 0, 30, 30, 255);
	else if (playerNum == 2) score_text = new Text(" ", 12, 0, 0, 230, 0, 0);
	else if (playerNum == 3) score_text = new Text(" ", 12, 0, 0, 0, 230, 0);
	else if (playerNum == 4) score_text = new Text(" ", 12, 0, 0, 230, 230, 0);
    updateScore();
    loadKeySet(keySet);

	setVelocity(config::P_VELOCITY, config::P_VELOCITY);
}

Player::~Player() {
}

void Player::loadKeySet(const KeySet &set)
{
    m_keySet = set;
}

void Player::render(SDL_Renderer* renderer, float timeAlpha) {
	Entity::render(renderer, timeAlpha, dead ? 4 : m_direction);
    score_text->render(renderer);
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

	if (m_direction == UP) {
        setY(getY() - (getVelocityY() * timeStep));
        if (getY() < 0) setY(0); //Prevent from going out of screen
    }
    else if (m_direction == DOWN) {
		setY(getY() + (getVelocityY() * timeStep));
        if (getY() + getHeight() > config::W_HEIGHT) 
			setY(static_cast<float>(config::W_HEIGHT - getHeight())); //Prevent from going out of screen
    }

    else if (m_direction == LEFT) {
		setX(getX() - (getVelocityX() * timeStep));
        if (getX() < 0) setX(0); //Prevent from going out of screen
    }
    else if (m_direction == RIGHT) {
		setX(getX() + (getVelocityX() * timeStep));
        if (getX() + getWidth() > config::W_WIDTH) 
			setX(static_cast<float>(config::W_WIDTH - getWidth())); //Prevent from going out of screen
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
	using namespace positionHelper;
    //Position text correctly
    if (config::NUM_OF_PLAYERS == 4) {
        float newXPos = static_cast<float>((config::W_WIDTH / 4) * (playerNum-1) + 20);
        score_text->setX(newXPos);
    }
    else if (config::NUM_OF_PLAYERS == 3) {
		if (playerNum == 1)
			score_text->setX(leftAlign(0, 10));
		else if (playerNum == 2)
			score_text->setX(centerHorizontal(0, config::W_WIDTH, score_text->getWidth()));
		else if (playerNum == 3)
			score_text->setX(rightAlign(config::W_WIDTH, 10, score_text->getWidth()));
    }
    else if (config::NUM_OF_PLAYERS == 2) {
		if (playerNum == 1)
			score_text->setX(leftAlign(0, 10));
		else if (playerNum == 2)
			score_text->setX(rightAlign(config::W_WIDTH, 10, score_text->getWidth()));
    } 
    else if (config::NUM_OF_PLAYERS == 1) {
		score_text->setX(centerHorizontal(0, config::W_WIDTH, score_text->getWidth()));
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
