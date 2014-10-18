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


/* Enemy entity */

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.hpp"
#include "Player.hpp"

class Player;
class Enemy: public Entity {

public:

	/**
     *  Constructor
     *
     *  @param _fileName Full path to the image of the enemy
     *  @param _xPos     X-position of the enemy in pixels
     *  @param _yPos     Y-position of the enemy in pixels
     */
	Enemy(SDL_Renderer* renderer, const std::string _fileName, const float _xPos, const float _yPos);


    /**
     *  Destructor
     */
    virtual ~Enemy();

	//////////////////////////////////////////////////////
	///////////////  ENTITY OVERRIDES  ///////////////////
	//////////////////////////////////////////////////////

    /**
     *  Update function
     *   - Called each frame
     */
    void update(float timeStep);

	//////////////////////////////////////////////////////
	//////////////  END ENTITY OVERRIDES  ////////////////
	//////////////////////////////////////////////////////



	void render(SDL_Renderer* renderer, float alphaTime);

    /**
     *  Updates movement
     */
    void updateMovement(float timeStep);


    /**
     * Sets target depending on distance. Measures from Enemys center to Players center. 
     * Doesn't target non-moving players.
     */
    void updateTarget();


    /**
     *  Update the direction to face current target
     */
    void updateDirection();


    /**
     *  Sets the enemy to be moving
     */
    void startMovement();


    /**
     *  Sets the enemy to stop moving
     */
    void stopMovement();


    /**
     *  Toggle movement for the enemy
     */
    void toggleMovement();

private:
    Direction m_direction;
    Player* currentTarget;
    bool m_movingX;
    bool m_movingY;
    int m_diagonalSensitivity;
};

#endif
