#include "Text.h"
#include <iostream>
#include <sstream>

std::map<int, TTF_Font*> Text::standard_font;
std::list<Text*> Text::s_textList;

Text::Text() 
{
	m_color.r = 0;
	m_color.g = 0;
	m_color.b = 0;
}


Text::Text(const int _number, const int _fontSize, const int _xPos, const int _yPos, int r, int g, int b)
	: m_fontSize(_fontSize)
{
	m_visible = true;
	m_xPos = static_cast<float>(_xPos);
	m_yPos = static_cast<float>(_yPos);

	m_color.r = r;
	m_color.g = g;
	m_color.b = b;

	char text[8];
	sprintf_s(text, "%d", _number);

	m_surf = TTF_RenderText_Blended(standard_font[_fontSize], text, m_color);
	m_height = m_surf->h;
	m_width = m_surf->w;
}


Text::Text(const char* _text, const int _fontSize, const int _xPos, const int _yPos, int r, int g, int b) 
	: m_fontSize(_fontSize)
{
	m_visible = true;
	m_xPos = static_cast<float>(_xPos);
	m_yPos = static_cast<float>(_yPos);

	m_color.r = r;
	m_color.g = g;
	m_color.b = b;

	if ((m_surf = TTF_RenderText_Blended(standard_font[_fontSize], _text, m_color)) == NULL) exit(-1); //TODO: ERRORHANDLING
	m_height = m_surf->h;
	m_width = m_surf->w;
}

Text::~Text() 
{
}

void Text::draw(SDL_Surface* _destSurf) {
	if(!m_visible) return;
	
	SDL_Rect destRect;
	destRect.x = (Sint16)(m_xPos);
	destRect.y = (Sint16)(m_yPos);

	SDL_BlitSurface(m_surf, NULL, _destSurf, &destRect);
}

void Text::updateText(const int _number) {
	char text[8];
	sprintf_s(text, "%d", _number);
	updateText(text);
}

void Text::updateText(const char* _newText) {
	m_surf = TTF_RenderText_Blended(standard_font[m_fontSize], _newText, m_color);
	m_height = m_surf->h;
	m_width = m_surf->w;
}

//Position text
void Text::setXPos(const float _xPos) {
	m_xPos = _xPos;
}
void Text::setYPos(const float _yPos) {
	m_yPos = _yPos;
}

void Text::setColor(int r, int g, int b) {
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
}