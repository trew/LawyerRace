#include "Dollar.h"

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

void Dollar::draw(SDL_Surface* _destSurf) {
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
