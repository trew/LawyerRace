#include "Button.h"

Button::Button()
: selected(false)
{
}

Button::Button(const char* _fileName, const int _xPos, const int _yPos)
: Sprite(_fileName, _xPos, _yPos),
selected(false)
{
}

Button::~Button() {
}

void Button::draw(SDL_Surface* _destSurf) {
    if(!m_visible) return;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(m_xPos);
    destRect.y = static_cast<int>(m_yPos);
    destRect.h = m_height / 2;
    destRect.w = m_width;

    SDL_Rect srcRect;
    srcRect.x = 0;
    if(selected) {
        srcRect.y = m_height / 2;
    } else {
        srcRect.y = 0;
    }
    srcRect.h = m_height / 2;
    srcRect.w = m_width;

    SDL_BlitSurface(m_surf, &srcRect, _destSurf, &destRect);
}

void Button::select() {
    selected = true;
}

void Button::deselect() {
    selected = false;
}

bool Button::isSelected() const {
    return selected;
}
