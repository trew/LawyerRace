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


#include "Button.hpp"

Button::Button()
: selected(false)
{
}

Button::Button(SDL_Renderer* renderer, const char* _fileName, const float _xPos, const float _yPos)
: Sprite(renderer, _fileName, _xPos, _yPos),
selected(false)
{
}

Button::~Button() {
}

void Button::render(SDL_Renderer* renderer) {
    if(!isVisible()) return;
	if (m_regions.size() != 2) return;

	TextureRegion* region = NULL;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(m_xPos);
    destRect.y = static_cast<int>(m_yPos);
    destRect.h = (int)(m_height);
    destRect.w = (int)(m_width);

    if(selected) {
		region = m_regions[0];
    } else {
		region = m_regions[1];
    }
	SDL_Rect srcRect = region->getRect();

	SDL_RenderCopy(renderer, region->getTexture()->getTexture(), &srcRect, &destRect);
}

void Button::select() {
    selected = true;
}

void Button::deselect() {
    selected = false;
}

bool Button::isSelected() const {
    return selected;
}
