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


/* Base sprite class */

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>
#include <SDL_image.h>

#include "Texture.h"
#include "TextureRegion.h"

#include <string>
#include <vector>

class Sprite {
public:

    /**
     *  Constructor
     */
    Sprite();


    /**
     *  Constructor
     *
     *  @param _fileName Full path to the image of the sprite.
     */
    Sprite(SDL_Renderer* renderer, const std::string _fileName);


    /**
     *  Constructor
     *
     *  @param _fileName Full path to the image of the sprite.
     *  @param _xPos     X-position of the sprite.
     *  @param _yPos     Y-position of the sprite.
     */
	Sprite(SDL_Renderer* renderer, const std::string _fileName, const float _xPos, const float _yPos);


    /**
     *  Destructor
     */
    virtual ~Sprite();


    /**
     *  Drawing method. Draws the sprite to a destination surface.
     *
     *  @param _destSurf Surface which the sprite will be drawn to.
     */
	virtual void render(SDL_Renderer* renderer, float x, float y);


	virtual void render(SDL_Renderer* renderer);


    /**
     *  Sets whether the sprite will be drawn to the screen or not.
     *
     *  @param newVisibility True if visible, False if hidden.
     */
    void setVisible(bool visible);

	bool isVisible() const;

    /**
     *  Width of sprite image.
     *
     *  @return Width of the image.
     */
    float getWidth() const;


    /**
     *  Height of sprite image.
     *
     *  @return Height of the image.
     */
    float getHeight() const;


	/**
     *  Retrieve the current X-position.
     *
     *  @return Current X-position as a float.
     */
    float getX() const;


    /**
     *  Retrieve the current Y-position.
     *
     *  @return Current Y-position as a float.
     */
    float getY() const;

	void setX(const float x);
	void setY(const float y);

	//////////////////////////////////////////////
	///////////  UTILITY FUNCTIONS  //////////////
	//////////////////////////////////////////////

	/**
	*  Position the sprite centered horizontally according to left and right border.
	*
	*  @param _leftBorder  Left border
	*  @param _rightBorder Right border
	*/
	void centerHorizontal(const int _leftBorder, const int _rightBorder);


	/**
	*  Position the sprite centered vertically according to top and bottom border.
	*
	*  @param _topBorder    Top border
	*  @param _bottomBorder Bottom border
	*/
	void centerVertical(const int _topBorder, const int _bottomBorder);


	/**
	*  Position the sprite aligned to the left border with a margin.
	*
	*  @param _leftBorder  Left border
	*  @param _margin      Margin from left border
	*/
	void leftAlign(const int _leftBorder, const int _margin);


	/**
	*  Position the sprite aligned to the right border with a margin.
	*
	*  @param _rightBorder  Right border
	*  @param _margin       Margin from right border
	*/
	void rightAlign(const int _rightBorder, const int _margin);


	/**
	*  Position the sprite aligned to the top border with a margin.
	*
	*  @param _topBorder    Top border
	*  @param _margin       Margin from top border
	*/
	void topAlign(const int _topBorder, const int _margin);


	/**
	*  Position the sprite aligned to the bottom border with a margin.
	*
	*  @param _bottomBorder Bottom border
	*  @param _margin       Margin from bottom border
	*/
	void bottomAlign(const int _bottomBorder, const int _margin);

	//////////////////////////////////////////////
	/////////  END UTILITY FUNCTIONS  ////////////
	//////////////////////////////////////////////


protected:
    float m_xPos;
    float m_yPos;
    float m_width;
    float m_height;

	std::vector<TextureRegion*> m_regions;

    bool m_visible;
};

#endif
