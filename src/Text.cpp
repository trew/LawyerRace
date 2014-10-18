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


#include "Text.hpp"
#include <iostream>
#include <sstream>
#include "Log.hpp"

std::map<int, TTF_Font*> Text::standard_font;
std::list<Text*> Text::s_textList;

Text::Text(SDL_Renderer* renderer, const int _number, const int _fontSize, const float _xPos, const float _yPos, int r, int g, int b)
    : m_fontSize(_fontSize)
{
	m_renderer = renderer;
	m_visible = true;
    m_xPos = static_cast<float>(_xPos);
    m_yPos = static_cast<float>(_yPos);

    m_color.r = r;
    m_color.g = g;
    m_color.b = b;

    std::string text = numberToText(_number);

	SDL_Surface* surface = TTF_RenderText_Blended(standard_font[_fontSize], text.c_str(), m_color);
	if (surface != NULL) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		if (texture != NULL) {
			m_texture = new Texture(texture);
		}
		SDL_FreeSurface(surface);
	}
	if (m_texture == NULL)
		LOG_ERROR << "Couldn't render text \"" << text << "\".\n"; //TODO: ERRORHANDLING
	m_height = (float)m_texture->H();
    m_width = (float)m_texture->W();
}


Text::Text(SDL_Renderer* renderer, std::string _text, const int _fontSize, const float _xPos, const float _yPos, int r, int g, int b)
    : m_fontSize(_fontSize)
{
	m_renderer = renderer;
    m_visible = true;
    m_xPos = static_cast<float>(_xPos);
    m_yPos = static_cast<float>(_yPos);

    m_color.r = r;
    m_color.g = g;
    m_color.b = b;

	SDL_Surface* surface = TTF_RenderText_Blended(standard_font[_fontSize], _text.c_str(), m_color);
	if (surface != NULL) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		if (texture != NULL) {
			m_texture = new Texture(texture);
		}
		SDL_FreeSurface(surface);
	}
	if (m_texture == NULL)
        LOG_ERROR << "Couldn't render text \"" << _text << "\".\n"; //TODO: ERRORHANDLING
    m_height = (float)m_texture->H();
    m_width = (float)m_texture->W();
}

Text::~Text()
{
}

void Text::render(SDL_Renderer* renderer) {
    if(!isVisible()) return;

    SDL_Rect destRect;
    destRect.x = (int)(getX());
    destRect.y = (int)(getY());
	destRect.w = m_texture->W();
	destRect.h = m_texture->H();

	SDL_RenderCopy(renderer, m_texture->getTexture(), NULL, &destRect);
}

void Text::updateText(const int _number) {
    std::string text = numberToText(_number);
    updateText(text);
}

void Text::updateText(const std::string _newText) {
	SDL_Surface* surface = TTF_RenderText_Blended(standard_font[m_fontSize], _newText.c_str(), m_color);
	if (surface != NULL) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		if (texture != NULL) {
			m_texture = new Texture(texture);
		}
		SDL_FreeSurface(surface);
	}
    m_height = (float)m_texture->H();
    m_width = (float)m_texture->W();
}

const std::string Text::numberToText(int _number)
{
    std::stringstream ss;
    ss << _number;
    return ss.str();
}

void Text::setColor(int r, int g, int b) {
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
}

