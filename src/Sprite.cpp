#include "Sprite.h"
#include <string>
#include <iostream>
#include "Log.h"

std::list<Sprite*> Sprite::s_spriteList;

Sprite::Sprite() {
/// Load default values of Sprite
	m_surf = NULL;
	s_spriteList.push_back(this);
	m_visible = true;
}

Sprite::Sprite(const std::string _fileName) {
/// Load image into Sprite with x,y = 0,0
	if ( (m_surf = loadImage(_fileName)) == NULL) LOG_DEBUG("Couldn't load file: \"" + _fileName + "\""); //TODO: Errorhandling if m_Surf is NULL!
	s_spriteList.push_back(this);
	m_visible = true;
}

Sprite::Sprite(const std::string _fileName, const int _xPos, const int _yPos) {
/// Load image into Sprite with provided X- and Y-pos.
	if ( (m_surf = loadImage(_fileName, _xPos, _yPos)) == NULL) LOG_DEBUG("Couldn't load file: \"" + _fileName + "\"");
	s_spriteList.push_back(this);
	m_visible = true;
}

Sprite::~Sprite() {
/// Destructor. Sets Surface to NULL
	SDL_FreeSurface(m_surf);
	m_surf = NULL;
}

SDL_Surface* Sprite::loadImage(const std::string _fileName, const int _xPos, const int _yPos) {
/// Load image using IMG_Load and set values to the sprites Rect. Returns NULL if image couldn't be loaded.
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
/// Calls loadImage(const char* _fileName, const int _xPos, const int _yPos) 
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
