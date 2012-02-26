#ifndef _TEXT_H_
#define _TEXT_H_

#include <map>
#include "Sprite.hpp"
#include <SDL/SDL_ttf.h>

class Text: public Sprite {
public:
	Text();
	Text(const int _number, const int _fontSize, const int _xPos, const int _yPos, int r, int g, int b);
	Text(std::string _text, const int _fontSize, const int _xPos, const int _yPos, int r, int g, int b);
	virtual ~Text();

	void draw(SDL_Surface* _destSurf);
	void updateText(const int _number);
	void updateText(const std::string _newText);
	void setXPos(const float _xPos);
	void setYPos(const float _yPos);

	const std::string numberToText(int _number);

	void setColor(int r, int g, int b);

private:
	SDL_Color m_color;
	int m_fontSize;
public:
	static std::map<int, TTF_Font*> standard_font;
	static std::list<Text*> s_textList;
};

#endif 
