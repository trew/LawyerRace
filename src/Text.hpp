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


/* Text object */

#ifndef _TEXT_H_
#define _TEXT_H_

#include <map>
#include <SDL_ttf.h>
#include <list>
#include "Texture.h"

class Text {
public:
	Text(const int number, const int fontSize, const float x, const float y, int r, int g, int b);
	Text(std::string text, const int fontSize, const float x, const float y, int r, int g, int b);

    virtual ~Text();

    void render(SDL_Renderer* renderer);

    void updateText(const int _number);
    void updateText(const std::string _newText);

    /**
     *  Sets the color of the text.
     *
     *  @param r Red.   0-255
     *  @param g Green. 0-255
     *  @param b Blue.  0-255
     */
    void setColor(int r, int g, int b);

	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);

	float getWidth() const;
	float getHeight() const;

	bool isVisible() const;
	void setVisible(bool visible);

private:
	float m_x{ 0 };
	float m_y{ 0 };
	float m_width{ 0 };
	float m_height{ 0 };

	bool m_visible{ true };

	Texture* m_texture{ NULL };
    SDL_Color m_color;
	int m_fontSize{ 0 };
	SDL_Renderer* m_renderer{ NULL };
public:
    static std::map<int, TTF_Font*> standard_font;
    static std::list<Text*> s_textList;
};

#endif 
