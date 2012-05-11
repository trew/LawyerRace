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


#include "Sprite.hpp"
#include <string>
#include <iostream>
#include "Log.hpp"

std::list<Sprite*> Sprite::s_spriteList;

Sprite::Sprite() {
    m_surf = NULL;
    s_spriteList.push_back(this);
    m_visible = true;
}

Sprite::Sprite(const std::string _fileName) {
    if ( (m_surf = loadImage(_fileName)) == NULL) 
        LOG_ERROR << "Couldn't load file: \"" << _fileName << "\"\n"; //TODO: Errorhandling if m_Surf is NULL!
    s_spriteList.push_back(this);
    m_visible = true;
}

Sprite::Sprite(const std::string _fileName, const int _xPos, const int _yPos) {
    if ( (m_surf = loadImage(_fileName, _xPos, _yPos)) == NULL)
        LOG_ERROR << "Couldn't load file: \"" << _fileName << "\"\n";
    s_spriteList.push_back(this);
    m_visible = true;
}

Sprite::~Sprite() {
    SDL_FreeSurface(m_surf);
    m_surf = NULL;
}

SDL_Surface* Sprite::loadImage(const std::string _fileName, const int _xPos, const int _yPos) {
    SDL_Surface* tmpSurf;
    SDL_Surface* returnSurf = NULL;

    if ((tmpSurf = IMG_Load(_fileName.c_str())) == NULL) return NULL;

    returnSurf = SDL_DisplayFormatAlpha(tmpSurf);

    m_xPos = static_cast<float>(_xPos);
    m_yPos = static_cast<float>(_yPos);
    m_height = returnSurf->h;
    m_width = returnSurf->w;
    SDL_FreeSurface(tmpSurf);
    return returnSurf;
}

SDL_Surface* Sprite::loadImage(const std::string _fileName) {
    return loadImage(_fileName, 0, 0);
}

void Sprite::setVisibility(bool newVisibility) {
    m_visible = newVisibility;
}

int Sprite::getWidth() const {
    return m_width;
}

int Sprite::getHeight() const {
    return m_width;
}

void Sprite::centerHorizontal(const int _leftBorder, const int _rightBorder) {
    m_xPos = (float)(((_rightBorder - _leftBorder) / 2) - (m_width / 2) + (_leftBorder));
}

void Sprite::centerVertical(const int _topBorder, const int _bottomBorder) {
    m_yPos = (float)(((_bottomBorder - _topBorder) / 2) - (m_height / 2) + (_topBorder));
}

void Sprite::leftAlign(const int _leftBorder, const int _leftMargin) {
    m_xPos = (float)(_leftMargin + _leftBorder);
}

void Sprite::rightAlign(const int _rightBorder, const int _rightMargin) {
    m_xPos = (float)(_rightBorder - _rightMargin - m_width);
}

void Sprite::topAlign(const int _topBorder, const int _topMargin) {
    m_yPos = (float)(_topMargin + _topBorder);
}

void Sprite::bottomAlign(const int _bottomBorder, const int _bottomMargin) {
    m_yPos = (float)(_bottomBorder - _bottomMargin - m_height);
}

float Sprite::getXPos() const {
    return m_xPos;
}

float Sprite::getYPos() const {
    return m_yPos;
}
