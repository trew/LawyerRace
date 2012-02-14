#include "Image.h"

Image::Image() {
}

Image::Image(const char* _fileName, const int _xPos, const int _yPos)
	:Sprite(_fileName, _xPos, _yPos)
{
}

Image::~Image() {
}

void Image::draw(SDL_Surface* _destSurf) {
	if(!m_visible) return;
	
	SDL_Rect destRect;
	destRect.x = static_cast<int>(m_xPos);
	destRect.y = static_cast<int>(m_yPos);
	destRect.h = m_height;
	destRect.w = m_width;

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = m_height;
	srcRect.w = m_width;
	
	SDL_BlitSurface(m_surf, &srcRect, _destSurf, &destRect);
}
