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
	Enemy(std::vector<TextureRegion*> regions, const float x, const float y, const float w, const float h, bool movingX, bool movingY);
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
	Direction m_direction{ DOWN };
	Player* currentTarget{ NULL };
	bool m_movingX{ false };
	bool m_movingY{ false };
	int m_diagonalSensitivity{ 0 };
};

#endif
