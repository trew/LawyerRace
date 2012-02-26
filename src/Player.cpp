#include "Player.h"
#include <iostream>
#include <sstream>

std::list<Player*> Player::s_playerList;
int Player::alivePlayers = 0;
int Player::currentPlayerNum = 0;

Player::Player()
: m_direction(DOWN),
  m_score(0),
  dead(false)
{
    moving = false;
    m_vel = config::P_VELOCITY;
    m_width = config::P_WIDTH;
    m_height = config::P_HEIGHT;

    currentPlayerNum++;
    alivePlayers++;
    playerNum = currentPlayerNum;

         if(playerNum == 1) score_text = new Text(" ", 12, 0, 0, 30, 30, 255);
    else if(playerNum == 2) score_text = new Text(" ", 12, 0, 0,230, 0, 0);
    else if(playerNum == 3) score_text = new Text(" ", 12, 0, 0, 0 , 230, 0);
    else if(playerNum == 4) score_text = new Text(" ", 12, 0, 0,230,230, 0);
    updateScore();
}

Player::Player(const std::string _fileName, KeySet _keySet)
: Entity(_fileName),
  m_direction(DOWN),
  m_score(0),
  dead(false)
{
    moving = false;
    m_vel = config::P_VELOCITY;
    m_width = config::P_WIDTH;
    m_height = config::P_HEIGHT;

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

Player::Player(const std::string _fileName, const int _xPos, const int _yPos, KeySet _keySet)
: Entity(_fileName, _xPos, _yPos),
  m_direction(DOWN),
  m_score(0),
  dead(false)
{
    moving = false;
    m_vel = config::P_VELOCITY;
    m_width = config::P_WIDTH;
    m_height = config::P_HEIGHT;

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

void Player::draw(SDL_Surface* _destSurf) {
///Draw Player to screen

    if(!m_visible) return;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(m_xPos);
    destRect.y = static_cast<int>(m_yPos);
    destRect.h = m_height;
    destRect.w = m_width;

    SDL_Rect srcRect;
    srcRect.x = 0;
    if(dead)
        srcRect.y = m_height * 4;
    else
        srcRect.y = m_height * m_direction;
    srcRect.h = m_height;
    srcRect.w = m_width;

    SDL_BlitSurface(m_surf, &srcRect, _destSurf, &destRect);

    score_text->draw(_destSurf);
}

void Player::handleEvent(SDL_Event& ev) {
    if (dead) return;
    if(ev.type == SDL_KEYDOWN) {
        if (ev.key.keysym.sym == m_keySet.K_LEFT) {
            startMovement();
            setDirection(LEFT);
        }
        else if (ev.key.keysym.sym == m_keySet.K_RIGHT) {
            startMovement();
            setDirection(RIGHT);
        }
        else if (ev.key.keysym.sym == m_keySet.K_UP) {
            startMovement();
            setDirection(UP);
        }
        else if (ev.key.keysym.sym == m_keySet.K_DOWN) {
            startMovement();
            setDirection(DOWN);
        }
        else if (ev.key.keysym.sym == m_keySet.K_STOP) {
            if (config::PLAYER_STOP_ENABLED)
                toggleMovement();
        }
    }
}


void Player::update() {
///Moves player according to direction and speed 
    if (!moving || dead) return;    //Return if no movement

    else if (m_direction == UP) {
        m_yPos -= (FPS::FPSControl.GetSpeedFactor() * m_vel);
        if (m_yPos < 0) m_yPos = 0; //Prevent from going out of screen
    }
    else if (m_direction == DOWN) {
        m_yPos += (FPS::FPSControl.GetSpeedFactor() * m_vel);
        if (m_yPos + m_height > config::W_HEIGHT) m_yPos = static_cast<float>(config::W_HEIGHT - m_height); //Prevent from going out of screen
    }

    else if (m_direction == LEFT) {
        m_xPos -= (FPS::FPSControl.GetSpeedFactor() * m_vel);
        if (m_xPos < 0) m_xPos = 0; //Prevent from going out of screen
    }
    else if (m_direction == RIGHT) {
        m_xPos += (FPS::FPSControl.GetSpeedFactor() * m_vel);
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
    moving = false;
    alivePlayers--;
    updateScore();
}

bool Player::isDead() const{
    return dead;
}
 
bool Player::isMoving() const {
    return moving;
}

void Player::startMovement() {
    moving = true;
}

void Player::stopMovement() {
    moving = false;
}

void Player::toggleMovement() {
    moving = !moving;
}

float Player::getXPos() {
    return m_xPos;
}
float Player::getYPos() {
    return m_yPos;
}
int Player::getScore() const {
    return m_score;
}


void Player::setDirection(Direction newDir) {
///Set direction of player
    m_direction = newDir;
}
