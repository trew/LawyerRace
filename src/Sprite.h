#ifndef _SPRITE_H_ 
#define _SPRITE_H_

#include <SDL.h>
#include <SDL_image.h>

#include <list>
#include <string>

class Sprite {
public:
	Sprite();
	Sprite(const std::string _fileName);
	Sprite(const std::string _fileName, const int _xPos, const int _yPos);
	virtual ~Sprite();

	virtual void draw(SDL_Surface* _destSurf)=0;

	SDL_Surface* loadImage(const std::string _fileName, const int _xPos, const int _yPos);
	SDL_Surface* loadImage(const std::string _fileName);

	void setVisibility(bool newVisibility);
	int getWidth() const;
	int getHeight() const;

	void centerHorizontal(const int _leftBorder, const int _rightBorder);
	void centerVertical(const int _topBorder, const int _bottomBorder);
	void leftAlign(const int _leftBorder, const int _leftmargin);
	void rightAlign(const int _rightBorder, const int _rightmargin);
	void topAlign(const int _topBorder, const int _topMargin);
	void bottomAlign(const int _bottomBorder, const int _bottomMargin);

	float getXPos() const;
	float getYPos() const;

protected:
	SDL_Surface* m_surf;
	float m_xPos; 
	float m_yPos;
	int m_width;
	int m_height;
	bool m_visible;
	

public:
	static std::list<Sprite*> s_spriteList;
};

#endif
