#ifndef LWR_TEXT_HPP
#define LWR_TEXT_HPP

#include <LawyerEngine/LawyerEngine.hpp>

#include <map>
#include <list>

class LawyerText : public lwe::Text {
public:

	LawyerText(int number, int fontSize, float x, float y, int r, int g, int b);
	LawyerText(std::string text, int fontSize, float x, float y, int r, int g, int b);

  virtual ~LawyerText() {}

	static SDL_Renderer* textRenderer;

  static lwe::Font* standardFont;
  static std::list<LawyerText*> s_textList;
};

#endif 
