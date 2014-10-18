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


#include "Enemy.hpp"
#include <iostream>
#include <sstream>

Enemy::Enemy(SDL_Renderer* renderer, const std::string _fileName, const float _xPos, const float _yPos)
: Entity(renderer, _fileName, _xPos, _yPos, config::E_VELOCITY, config::E_VELOCITY),
  m_direction(DOWN),
  currentTarget(NULL)
{
    m_height = (float)config::E_HEIGHT;
    m_width = (float)config::E_WIDTH;
    m_movingX = true; m_movingY = true;

	auto enemyListSize = manager->getAll<Enemy>().size();
    if(enemyListSize > 0) {
        if(enemyListSize % 2 == 1) m_movingX = false;
        else m_movingY = false;
    }
    m_diagonalSensitivity = (rand() % 6 +3);
}

Enemy::~Enemy() {
}

void Enemy::render(SDL_Renderer* renderer, float timeAlpha) {
	if (!m_visible) return;

	SDL_Rect destRect;
	destRect.x = static_cast<int>(lerp(getPreviousX(), getX(), timeAlpha));
	destRect.y = static_cast<int>(lerp(getPreviousY(), getY(), timeAlpha));
	destRect.h = (int)m_height;
	destRect.w = (int)m_width;

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = (int)m_height * m_direction;
	srcRect.h = (int)m_height;
	srcRect.w = (int)m_width;

	SDL_RenderCopy(renderer, m_texture->getTexture(), &srcRect, &destRect);
}


void Enemy::update(float timeStep) {
	setMoving(false);
	for (auto& e : manager->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
        if (p->isMoving() && !p->isDead()) {
			setMoving(true);
            break;
        }
    }

    if (!isMoving()) return;

    //Update target depending on players movement and deadness.
    updateTarget();
    if (currentTarget == NULL) return;

    //Determine direction of enemy so correct sprite is drawn.
    updateDirection();

    //Movement phase
    updateMovement(timeStep);

}

void Enemy::updateMovement(float timeStep) {

    //Get target X,Y so we can ignore sprite sizes
    int targetYCompare = (int)(currentTarget->getY() - ((m_height - currentTarget->getHeight()) / 2.f));
    int targetXCompare = (int)(currentTarget->getX() - ((m_width - currentTarget->getWidth()) / 2.f));

    bool tmp_movingY = m_movingY;
    bool tmp_movingX = m_movingX;

    float delta_x = 0.0;
    float delta_y = 0.0;

    //Move vertical
    if(  tmp_movingY && 
       ((m_yPos < targetYCompare - (config::W_HEIGHT / m_diagonalSensitivity)) || 
        (m_yPos > targetYCompare + (config::W_HEIGHT / m_diagonalSensitivity)) 
        )) 
        tmp_movingX = true;

    if ( tmp_movingX &&
       ((m_xPos < targetXCompare - (config::W_WIDTH / m_diagonalSensitivity)) ||
        (m_xPos > targetXCompare + (config::W_WIDTH / m_diagonalSensitivity))
        ))
        tmp_movingY = true;

    if(tmp_movingY && (m_yPos == targetYCompare)) tmp_movingX = true;
    if(tmp_movingX && (m_xPos == targetXCompare)) tmp_movingY = true;

    if(tmp_movingY) {
        if ( m_yPos < targetYCompare ) {
            delta_y += (getVelocityY() * timeStep);
            if ( (m_yPos + delta_y) + m_height > config::W_HEIGHT) {
                m_yPos = static_cast<float>(config::W_HEIGHT - m_height); //Prevent from going out of screen
                delta_y = 0.0;
            }
            if ( (m_yPos + delta_y) > targetYCompare) {
                m_yPos = float(targetYCompare);
                delta_y = 0.0;
            }
            if (tmp_movingX == false) {
                m_direction = DOWN;
            }
        } else if ( m_yPos > targetYCompare) {
            delta_y -= (getVelocityY() * timeStep);
            if ( (m_yPos + delta_y) < 0) {
                m_yPos = 0;
                delta_y = 0.0;
            }
            if ( (m_yPos + delta_y) < targetYCompare) {
                m_yPos = float(targetYCompare);
                delta_y = 0.0;
            }
            if( tmp_movingX == false ) {
                m_direction = UP;
            }
        }
    }
    //Move horizontal
    if(tmp_movingX) {
        if (m_xPos < targetXCompare) {
            delta_x += (getVelocityX() * timeStep);
            if ( (m_xPos + delta_x) + m_width > config::W_WIDTH) {
                m_xPos = static_cast<float>(config::W_WIDTH - m_width);
                delta_x = 0.0;
            }
            if ( (m_xPos + delta_x) > targetXCompare) {
                m_xPos = float(targetXCompare);
                delta_x = 0.0;
            }
            if( tmp_movingY == false ) {
                m_direction = RIGHT;
            }

        } else if (m_xPos > targetXCompare) {
            delta_x -= (getVelocityX() * timeStep);
            if ( (m_xPos + delta_x) < 0) {
                m_xPos = 0;
                delta_x = 0.0;
            }
            if ( (m_xPos + delta_x) < targetXCompare) {
                m_xPos = float(targetXCompare);
                delta_x = 0.0;
            }
            if( tmp_movingY == false ) {
                m_direction = LEFT;
            }
        }
    }

    // Update the calculated position
    if (delta_x != 0.0 && delta_y != 0.0 && !config::OLD_DIAGONAL_SPEED) {
        /* Going to explain the multiplier value here
         *                      |
         *                    / |
         *   sqrt(2*2 + 3*3)/   |
         *                /     | 3
         *              /       |
         *            / - - - - |
         *                 2
         * And the value I want is ((2+3)/2) / sqrt(2*2 + 3*3)
         * which is :                 2.5    / sqrt(13)
         *                            2.5    / 3.605551275463989    = 0.69~
         * However in our case we can assume the enemy always moves with equal speed in both X and Y,
         * because FPS::FPSControl.GetSpeedFactor() doesn't change between the modifications of delta_x and delta_y.
         * The formula would look like  (x / sqrt( 2(x*x) )
         * ... which is 0.7071067811865475.
         */

        /*
        float d = abs(delta_x);
        float multiplier = d / sqrt(2*(d*d));
        */
        float multiplier = 0.7071068f; //fast-forward to answer, skipping calculation
        delta_x *= multiplier;
        delta_y *= multiplier;
    }

    m_xPos += delta_x;
    m_yPos += delta_y;
}

void Enemy::updateTarget() {
    float shortestDistance = 0;
    float currentDistance = 0;

    //Set initial target
	for (auto& e : manager->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
		if ((p->isMoving()) && (!p->isDead())) {
            currentDistance = 0;
            if(p->getX() > m_xPos)
                currentDistance += (p->getX() + p->getWidth() / 2)  - (m_xPos + m_width / 2);
            else
                currentDistance += ((m_xPos + m_width / 2)  - (p->getX() + p->getWidth() / 2));

            if (p->getY() > m_yPos)
                currentDistance += (p->getY() + p->getHeight() / 2) - (m_yPos + m_height / 2);
            else
                currentDistance += ((m_yPos + m_height / 2)  - (p->getY() + p->getHeight() / 2));

            shortestDistance = currentDistance;
            currentTarget = p;
            break;
        }
		if (shortestDistance > 0) break;
    }

    //Loop through rest of players
	for (auto& e : manager->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
		if (p->isMoving() && !p->isDead()) {
            currentDistance = 0;
            if(p->getX() > m_xPos)
                currentDistance += (p->getX() + p->getWidth() / 2)  - (m_xPos + m_width / 2);
            else
                currentDistance += ((m_xPos + m_width / 2)  - (p->getX() + p->getWidth() / 2));

            if (p->getY() > m_yPos)
                currentDistance += (p->getY() + p->getHeight() / 2) - (m_yPos + m_height / 2);
            else
                currentDistance += ((m_yPos + m_height / 2)  - (p->getY() + p->getHeight() / 2));

            if (currentDistance < shortestDistance) {
                shortestDistance = currentDistance;
                currentTarget = p;
            }
        }
    }
}

void Enemy::updateDirection() {

    if (currentTarget == NULL) return;

    //Get target X,Y so we can ignore sprite sizes
    int targetYCompare = (int)(currentTarget->getY() - ((m_height - currentTarget->getHeight()) / 2));
    int targetXCompare = (int)(currentTarget->getX() - ((m_width - currentTarget->getWidth()) / 2));

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
