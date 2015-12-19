#include <LawyerRace/Graphics/LawyerText.hpp>
#include <iostream>
#include <sstream>
#include <list>

lwe::Font* LawyerText::standardFont;
std::list<LawyerText*> LawyerText::s_textList;
SDL_Renderer* LawyerText::textRenderer;

LawyerText::LawyerText(const int _number, const int _fontSize, const float _x, const float _y, int r, int g, int b)
    : LawyerText(std::to_string(_number), _fontSize, _x, _y, r, g, b)
{
}


LawyerText::LawyerText(std::string _text, const int _fontSize, const float _x, const float _y, int r, int g, int b)
    : lwe::Text(textRenderer, standardFont, _text, _fontSize, _x, _y, r, g, b)
{
}
