#include "LawyerRace/Entity/Enemy.hpp"
#include <iostream>
#include <sstream>

Enemy::Enemy(std::vector<TextureRegion*> regions, const float x, const float y, const float w, const float h, bool movingX, bool movingY)
	: Entity(regions, x, y, w, h), m_movingX(movingX), m_movingY(movingY)
{
    m_diagonalSensitivity = (rand() % 6 +3);
	setVelocity(config::E_VELOCITY, config::E_VELOCITY);
}

Enemy::~Enemy() {
}

void Enemy::render(SDL_Renderer* renderer, float timeAlpha) {
	Entity::render(renderer, timeAlpha, m_direction);
}


void Enemy::update(float timeStep) {
	setMoving(false);
	for (auto& e : getManager()->getAll<Player>()) {
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
    int targetYCompare = (int)(currentTarget->getY() - ((getHeight() - currentTarget->getHeight()) / 2.f));
    int targetXCompare = (int)(currentTarget->getX() - ((getWidth() - currentTarget->getWidth()) / 2.f));

    bool tmp_movingY = m_movingY;
    bool tmp_movingX = m_movingX;

    float delta_x = 0.0;
    float delta_y = 0.0;

    //Move vertical
    if(  tmp_movingY && 
       ((getY() < targetYCompare - (config::W_HEIGHT / m_diagonalSensitivity)) || 
        (getY() > targetYCompare + (config::W_HEIGHT / m_diagonalSensitivity)) 
        )) 
        tmp_movingX = true;

    if ( tmp_movingX &&
       ((getX() < targetXCompare - (config::W_WIDTH / m_diagonalSensitivity)) ||
        (getX() > targetXCompare + (config::W_WIDTH / m_diagonalSensitivity))
        ))
        tmp_movingY = true;

    if(tmp_movingY && (getY() == targetYCompare)) tmp_movingX = true;
    if(tmp_movingX && (getX() == targetXCompare)) tmp_movingY = true;

    if(tmp_movingY) {
        if ( getY() < targetYCompare ) {
            delta_y += (getVelocityY() * timeStep);
            if ( (getY() + delta_y) + getHeight() > config::W_HEIGHT) {
                setY(static_cast<float>(config::W_HEIGHT - getHeight())); //Prevent from going out of screen
                delta_y = 0.0;
            }
            if ( (getY() + delta_y) > targetYCompare) {
                setY(float(targetYCompare));
                delta_y = 0.0;
            }
            if (tmp_movingX == false) {
                m_direction = DOWN;
            }
        } else if ( getY() > targetYCompare) {
            delta_y -= (getVelocityY() * timeStep);
            if ( (getY() + delta_y) < 0) {
                setY(0);
                delta_y = 0.0;
            }
            if ( (getY() + delta_y) < targetYCompare) {
                setY(float(targetYCompare));
                delta_y = 0.0;
            }
            if( tmp_movingX == false ) {
                m_direction = UP;
            }
        }
    }
    //Move horizontal
    if(tmp_movingX) {
        if (getX() < targetXCompare) {
            delta_x += (getVelocityX() * timeStep);
            if ( (getX() + delta_x) + getWidth() > config::W_WIDTH) {
                setX(static_cast<float>(config::W_WIDTH - getWidth()));
                delta_x = 0.0;
            }
            if ( (getX() + delta_x) > targetXCompare) {
                setX(float(targetXCompare));
                delta_x = 0.0;
            }
            if( tmp_movingY == false ) {
                m_direction = RIGHT;
            }

        } else if (getX() > targetXCompare) {
            delta_x -= (getVelocityX() * timeStep);
            if ( (getX() + delta_x) < 0) {
                setX(0);
                delta_x = 0.0;
            }
            if ( (getX() + delta_x) < targetXCompare) {
                setX(float(targetXCompare));
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

    setX(getX() + delta_x);
    setY(getY() + delta_y);
}

void Enemy::updateTarget() {
    float shortestDistance = 0;
    float currentDistance = 0;

    //Set initial target
	for (auto& e : getManager()->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
		if ((p->isMoving()) && (!p->isDead())) {
            currentDistance = 0;
            if(p->getX() > getX())
                currentDistance += (p->getX() + p->getWidth() / 2)  - (getX() + getWidth() / 2);
            else
                currentDistance += ((getX() + getWidth() / 2)  - (p->getX() + p->getWidth() / 2));

            if (p->getY() > getY())
                currentDistance += (p->getY() + p->getHeight() / 2) - (getY() + getHeight() / 2);
            else
                currentDistance += ((getY() + getHeight() / 2)  - (p->getY() + p->getHeight() / 2));

            shortestDistance = currentDistance;
            currentTarget = p;
            break;
        }
		if (shortestDistance > 0) break;
    }

    //Loop through rest of players
	for (auto& e : getManager()->getAll<Player>()) {
		Player* p = reinterpret_cast<Player*>(e);
		if (p->isMoving() && !p->isDead()) {
            currentDistance = 0;
            if(p->getX() > getX())
                currentDistance += (p->getX() + p->getWidth() / 2)  - (getX() + getWidth() / 2);
            else
                currentDistance += ((getX() + getWidth() / 2)  - (p->getX() + p->getWidth() / 2));

            if (p->getY() > getY())
                currentDistance += (p->getY() + p->getHeight() / 2) - (getY() + getHeight() / 2);
            else
                currentDistance += ((getY() + getHeight() / 2)  - (p->getY() + p->getHeight() / 2));

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
    int targetYCompare = (int)(currentTarget->getY() - ((getHeight() - currentTarget->getHeight()) / 2));
    int targetXCompare = (int)(currentTarget->getX() - ((getWidth() - currentTarget->getWidth()) / 2));

    if( (getX() < targetXCompare) ) {
        if (getY() < targetYCompare) {
            m_direction = DOWN_RIGHT;
        }
        else if (getY() > targetYCompare) {
            m_direction = UP_RIGHT;
        }
        else {
            m_direction = RIGHT;
        }
    }
    else if( (getX() > targetXCompare) ) {
        if (getY() < targetYCompare) {
            m_direction = DOWN_LEFT;
        }
        else if (getY() > targetYCompare) {
            m_direction = UP_LEFT;
        }
        else {
            m_direction = LEFT;
        }
    }
    else {
        if (getY() < targetYCompare) {
            m_direction = DOWN;
        }
        else if (getY() > targetYCompare) {
            m_direction = UP;
        }
    }
}
