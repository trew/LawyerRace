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
     */
    Enemy();


    /**
     *  Constructor
     *
     *  @param _fileName Full path to the image of the enemy
     */
    Enemy(const std::string _fileName);


    /**
     *  Constructor
     *
     *  @param _fileName Full path to the image of the enemy
     *  @param _xPos     X-position of the enemy in pixels
     *  @param _yPos     Y-position of the enemy in pixels
     */
    Enemy(const std::string _fileName, const int _xPos, const int _yPos);


    /**
     *  Destructor
     */
    virtual ~Enemy();

    /**
     *  Drawing function
     *
     *  @param _destSurf Surface to which the enemy is drawn
     */
    virtual void draw(SDL_Surface* _destSurf);


    /**
     *  Event handling function
     *
     *  @param ev Struct containing the information about the event
     */
    void handleEvent(SDL_Event& ev);


    /**
     *  Update function
     *   - Called each frame
     */
    void update();


    /**
     *  Updates movement
     */
    void updateMovement();


    /**
     *  Update the enemys target
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

public:
    static std::list<Enemy*> s_enemyList;
};

#endif
