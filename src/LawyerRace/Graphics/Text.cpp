#include "LawyerRace/Graphics/Text.hpp"
#include <iostream>
#include <sstream>
#include "LawyerRace/Utils/Log.hpp"
#include <list>
#include "LawyerRace/Core/GameEngine.hpp"

std::map<int, TTF_Font*> Text::standard_font;
std::list<Text*> Text::s_textList;
SDL_Renderer* Text::textRenderer;

Text::Text(const int _number, const int _fontSize, const float _x, const float _y, int r, int g, int b)
    : Text(std::to_string(_number), _fontSize, _x, _y, r, g, b)
{
}


Text::Text(std::string _text, const int _fontSize, const float _x, const float _y, int r, int g, int b)
    : m_fontSize(_fontSize)
{
    m_x = static_cast<float>(_x);
    m_y = static_cast<float>(_y);

    m_color.r = r;
    m_color.g = g;
    m_color.b = b;

	SDL_Surface* surface = TTF_RenderText_Blended(standard_font[_fontSize], _text.c_str(), m_color);
	if (surface != NULL) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(textRenderer, surface);
		if (texture != NULL) {
			m_texture = new Texture(texture);
		}
		SDL_FreeSurface(surface);
	}
	if (m_texture == NULL)
        LOG_ERROR << "Couldn't render text \"" << _text << "\".\n"; //TODO: ERRORHANDLING
    m_height = (float)m_texture->getHeight();
    m_width = (float)m_texture->getWidth();
}

Text::~Text()
{
	delete m_texture;
}

void Text::render(SDL_Renderer* renderer) {
    if(!isVisible()) return;

    SDL_Rect destRect;
    destRect.x = (int)(getX());
    destRect.y = (int)(getY());
	destRect.w = m_texture->getWidth();
	destRect.h = m_texture->getHeight();

	SDL_RenderCopy(renderer, m_texture->getSDLTexture(), NULL, &destRect);
}

void Text::updateText(const int _number) {
	updateText(std::to_string(_number));
}

void Text::updateText(const std::string _newText) {
	SDL_Surface* surface = TTF_RenderText_Blended(standard_font[m_fontSize], _newText.c_str(), m_color);
	if (surface != NULL) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(textRenderer, surface);
		if (texture != NULL) {
			delete m_texture;
			m_texture = new Texture(texture);
		}
		SDL_FreeSurface(surface);
	}
    m_height = (float)m_texture->getHeight();
    m_width = (float)m_texture->getWidth();
}

void Text::setColor(int r, int g, int b) {
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
}

float Text::getX() const {
	return m_x;
}

float Text::getY() const {
	return m_y;
}

void Text::setX(float x) {
	m_x = x;
}

void Text::setY(float y) {
	m_y = y;
}

float Text::getWidth() const {
	return m_width;
}

float Text::getHeight() const {
	return m_height;
}

bool Text::isVisible() const {
	return m_visible;
}

void Text::setVisible(bool visible) {
	m_visible = visible;
}