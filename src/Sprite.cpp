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
#include "Gameconfig.hpp"

Sprite::Sprite() {
    m_texture = NULL;
	m_xPos = 0;
	m_yPos = 0;
	m_width = 0;
	m_height = 0;
	m_visible = true;
}

Sprite::Sprite(SDL_Renderer* renderer, const std::string _fileName) {
	m_texture = Texture::createTexture(renderer, _fileName);
	if (m_texture == NULL)
        LOG_ERROR << "Couldn't load file: \"" << _fileName << "\"\n"; //TODO: Errorhandling if m_Surf is NULL!
	m_xPos = 0;
	m_yPos = 0;
	m_width = 0;
	m_height = 0;
	m_visible = true;
}

Sprite::Sprite(SDL_Renderer* renderer, const std::string _fileName, const float _xPos, const float _yPos) {
	m_texture = Texture::createTexture(renderer, _fileName);
	if (m_texture == NULL)
		LOG_ERROR << "Couldn't load file: \"" << _fileName << "\"\n";

	m_xPos = _xPos;
	m_yPos = _yPos;
	m_visible = true;

	if (!m_texture) return;
	m_width = (float)m_texture->W();
	m_height = (float)m_texture->H();
}

Sprite::~Sprite() {
	delete m_texture;
}

void Sprite::render(SDL_Renderer* renderer, float x, float y) {
	if (!isVisible()) return;

	SDL_Rect destRect;
	destRect.x = (int)x;
	destRect.y = (int)y;
	destRect.h = (int)m_height;
	destRect.w = (int)m_width;

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_texture->W();
	srcRect.h = m_texture->H();

	SDL_RenderCopy(renderer, m_texture->getTexture(), &srcRect, &destRect);
}

void Sprite::render(SDL_Renderer* renderer) {
	if (!isVisible()) return;
	render(renderer, getX(), getY());
}

void Sprite::setVisible(bool visible) {
    m_visible = visible;
}

bool Sprite::isVisible() const {
	return m_visible;
}

float Sprite::getWidth() const {
    return m_width;
}

float Sprite::getHeight() const {
    return m_width;
}

float Sprite::getX() const {
    return m_xPos;
}

float Sprite::getY() const {
    return m_yPos;
}

void Sprite::setX(const float x) {
	m_xPos = x;
}

void Sprite::setY(const float y) {
	m_yPos = y;
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
