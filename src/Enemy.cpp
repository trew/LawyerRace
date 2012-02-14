#include "Enemy.h"
#include <iostream>

std::list<Enemy*> Enemy::s_enemyList;

Enemy::Enemy()
: m_direction(DOWN),
currentTarget(NULL)
{
	m_vel = E_VELOCITY;
	m_height = E_HEIGHT;
	m_width = E_WIDTH;
	moving = true;
	m_movingX = true; m_movingY = true;
	if(s_enemyList.size() > 0) {
		if(s_enemyList.size() % 2 == 1) m_movingX = false;
		else m_movingY = false;
	}
	m_diagonalSensitivity = (rand() % 6 +3);
}

Enemy::Enemy(const char* _fileName) 
: Entity(_fileName),
  m_direction(DOWN),
  currentTarget(NULL)
{
	m_vel = E_VELOCITY;
	m_height = E_HEIGHT;
	m_width = E_WIDTH;
	moving = false;
	m_movingX = true; m_movingY = true;
	if(s_enemyList.size() > 0) {
		if(s_enemyList.size() % 2 == 1) m_movingX = false;
		else m_movingY = false;
	}
	m_diagonalSensitivity = (rand() % 6 +3);
}

Enemy::Enemy(const char* _fileName, const int _xPos, const int _yPos) 
: Entity(_fileName, _xPos, _yPos),
  m_direction(DOWN),
  currentTarget(NULL)
{
	m_vel = E_VELOCITY;
	m_height = E_HEIGHT;
	m_width = E_WIDTH;
	moving = false;
	m_movingX = true; m_movingY = true;
	if(s_enemyList.size() > 0) {
		if(s_enemyList.size() % 2 == 1) m_movingX = false;
		else m_movingY = false;
	}
	m_diagonalSensitivity = (rand() % 6 +3);
}

Enemy::~Enemy() {
}

void Enemy::draw(SDL_Surface* _destSurf) {
	if(!m_visible) return;
	
	SDL_Rect destRect;
	destRect.x = static_cast<int>(m_xPos);
	destRect.y = static_cast<int>(m_yPos);
	destRect.h = m_height;
	destRect.w = m_width;

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = m_height * m_direction;
	srcRect.h = m_height;
	srcRect.w = m_width;
	
	SDL_BlitSurface(m_surf, &srcRect, _destSurf, &destRect);
}

void Enemy::handleEvent(SDL_Event& ev) {
}

void Enemy::startMovement() {
	moving = true;
}

void Enemy::stopMovement() {
	moving = false;
}
void Enemy::toggleMovement() {
	moving = !moving;
}


void Enemy::update() {
	std::list<Player*>::const_iterator it_player = Player::s_playerList.begin();
	while (it_player != Player::s_playerList.end()) {
		if ((*it_player)->isMoving() && !(*it_player)->isDead()) {
			moving = true;
			break;
		}
		it_player++;

		if (it_player == Player::s_playerList.end()) moving = false;
	}
	
	if (!moving) return;

	//Update target depending on players movement and deadness.
	updateTarget();
	if (currentTarget == NULL) return;

	//Determine direction of enemy so correct sprite is drawn.
	updateDirection(currentTarget);

	//Movement phase
	updateMovement();

}

void Enemy::updateMovement() {

	//Get target X,Y so we can ignore sprite sizes
	int targetYCompare = int(currentTarget->getYPos()) - ((m_height - currentTarget->getHeight()) / 2);
	int targetXCompare = int(currentTarget->getXPos()) - ((m_width - currentTarget->getWidth()) / 2);

	//Move vertical
	bool tmp_movingY = m_movingY;
	bool tmp_movingX = m_movingX;

	if(  tmp_movingY && 
	   ((m_yPos < targetYCompare - (W_HEIGHT / m_diagonalSensitivity)) || 
		(m_yPos > targetYCompare + (W_HEIGHT / m_diagonalSensitivity)) 
		)) 
		tmp_movingX = true;

	if ( tmp_movingX && 
	   ((m_xPos < targetXCompare - (W_WIDTH / m_diagonalSensitivity)) || 
		(m_xPos > targetXCompare + (W_WIDTH / m_diagonalSensitivity)) 
		)) 
		tmp_movingY = true;

	if(tmp_movingY && (m_yPos == targetYCompare)) tmp_movingX = true;
	if(tmp_movingX && (m_xPos == targetXCompare)) tmp_movingY = true;


	if(tmp_movingY) {
		if ( m_yPos < targetYCompare ) {
			m_yPos += (FPS::FPSControl.GetSpeedFactor() * m_vel);
			if (m_yPos + m_height > W_HEIGHT) 
				m_yPos = static_cast<float>(W_HEIGHT - m_height); //Prevent from going out of screen
			if (m_yPos > targetYCompare) m_yPos = float(targetYCompare);
			if (tmp_movingX == false) {
				m_direction = DOWN;
			}
		} else if ( m_yPos > targetYCompare) {
			m_yPos -= (FPS::FPSControl.GetSpeedFactor() * m_vel);
			if (m_yPos < 0) m_yPos = 0; 
			if (m_yPos < targetYCompare) {
				m_yPos = float(targetYCompare);
			}
			if( tmp_movingX == false ) {
				m_direction = UP;
			}
		}
	}
	//Move horizontal
	if(tmp_movingX) { 
		if (m_xPos < targetXCompare) {
			m_xPos += (FPS::FPSControl.GetSpeedFactor() * m_vel);
			if (m_xPos + m_width > W_WIDTH) 
				m_xPos = static_cast<float>(W_WIDTH - m_width); 
			if (m_xPos > targetXCompare) {
				m_xPos = float(targetXCompare);
			}
			if( tmp_movingY == false ) {
				m_direction = RIGHT;
			}

		} else if (m_xPos > targetXCompare) {
			m_xPos -= (FPS::FPSControl.GetSpeedFactor() * m_vel);
			if (m_xPos < 0) m_xPos = 0; 
			if (m_xPos < targetXCompare) {
				m_xPos = float(targetXCompare);
			}
			if( tmp_movingY == false ) {
				m_direction = LEFT;
			}
		}
	}
}

void Enemy::updateTarget() {
///Sets target depending on distance. Measures from Enemys center to Players center

	std::list<Player*>::const_iterator it_player = Player::s_playerList.begin();
	float shortestDistance = 0;
	float currentDistance = 0;
	
	//Set initial target
	while ( shortestDistance == 0 && (it_player != Player::s_playerList.end()) ) {
		if (((*it_player)->isMoving()) && (!(*it_player)->isDead())) {
			currentDistance = 0;
			if((*it_player)->getXPos() > m_xPos)
				currentDistance += ((*it_player)->getXPos() + (*it_player)->getWidth() / 2)  - (m_xPos + m_width / 2);
			else 
				currentDistance += ((m_xPos + m_width / 2)  - ((*it_player)->getXPos() + (*it_player)->getWidth() / 2));
			
			if ((*it_player)->getYPos() > m_yPos)
				currentDistance += ((*it_player)->getYPos() + (*it_player)->getHeight() / 2) - (m_yPos + m_height / 2);
			else
				currentDistance += ((m_yPos + m_height / 2)  - ((*it_player)->getYPos() + (*it_player)->getHeight() / 2));
			
			shortestDistance = currentDistance;
			currentTarget = (*it_player);
			it_player++;
			break;
		}
		it_player++;
		
	}

	//Loop through rest of players
	while (it_player != Player::s_playerList.end()) {
		if ((*it_player)->isMoving() && !(*it_player)->isDead()) {
			currentDistance = 0;
			if((*it_player)->getXPos() > m_xPos)
				currentDistance += ((*it_player)->getXPos() + (*it_player)->getWidth() / 2)  - (m_xPos + m_width / 2);
			else 
				currentDistance += ((m_xPos + m_width / 2)  - ((*it_player)->getXPos() + (*it_player)->getWidth() / 2));
			
			if ((*it_player)->getYPos() > m_yPos)
				currentDistance += ((*it_player)->getYPos() + (*it_player)->getHeight() / 2) - (m_yPos + m_height / 2);
			else
				currentDistance += ((m_yPos + m_height / 2)  - ((*it_player)->getYPos() + (*it_player)->getHeight() / 2));

			if (currentDistance < shortestDistance) {
				shortestDistance = currentDistance;
				currentTarget = (*it_player);
			}
		}
		it_player++;
	}

}

void Enemy::updateDirection(Player* _player) {
///Update direction of enemy. Used to determine which sprite to draw.
	if(_player == NULL) return;

	//Get target X,Y so we can ignore sprite sizes
	int targetYCompare = int(_player->getYPos()) - ((m_height - _player->getHeight()) / 2);
	int targetXCompare = int(_player->getXPos()) - ((m_width - _player->getWidth()) / 2);


	if( (m_xPos < targetXCompare) ) {
		if (m_yPos < targetYCompare) {
			m_direction = DOWN_RIGHT; 
		}
		else if (m_yPos > targetYCompare) {
			m_direction = UP_RIGHT;
		}
		else {
			m_direction = RIGHT;
		}
	}
	else if( (m_xPos > targetXCompare) ) {
		if (m_yPos < targetYCompare) {
			m_direction = DOWN_LEFT; 
		}
		else if (m_yPos > targetYCompare) {
			m_direction = UP_LEFT;
		}
		else {
			m_direction = LEFT;
		}
	}
	else {
		if (m_yPos < targetYCompare) {
			m_direction = DOWN; 
		}
		else if (m_yPos > targetYCompare) {
			m_direction = UP;
		}
	}
}
