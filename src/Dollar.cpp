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


#include "Dollar.hpp"

std::list<Dollar*> Dollar::s_dollarList;

Dollar::Dollar()
    : Entity()
{
}

Dollar::Dollar(const std::string _fileName)
    : Entity(_fileName)
{
}
Dollar::Dollar(const std::string _fileName, int _xPos, int _yPos)
    : Entity(_fileName, _xPos, _yPos)
{
}

Dollar::~Dollar() {
}

void Dollar::draw(SDL_Surface* _destSurf, float timeAlpha) {
    if(!m_visible) return;

    SDL_Rect destRect;
    destRect.x = (Sint16)(m_xPos);
    destRect.y = (Sint16)(m_yPos);
    destRect.h = m_height;
    destRect.w = m_width;

    SDL_BlitSurface(m_surf, NULL, _destSurf, &destRect);
}

void Dollar::handleEvent(SDL_Event& ev) {
}

void Dollar::setXPos(const float _xPos) {
    m_xPos = _xPos;
}

void Dollar::setYPos(const float _yPos) {
    m_yPos = _yPos;
}
