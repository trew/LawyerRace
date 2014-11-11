#ifndef LWR_TEXT_HPP
#define LWR_TEXT_HPP

#include <SDL_ttf.h>

#include "LawyerRace/Graphics/Texture.hpp"

#include <map>
#include <list>

class Text {
public:
	Text(const int number, const int fontSize, const float x, const float y, int r, int g, int b);
	Text(std::string text, const int fontSize, const float x, const float y, int r, int g, int b);

    virtual ~Text();

    void render(SDL_Renderer* renderer);

    void updateText(const int _number);
    void updateText(const std::string _newText);

    /**
     *  Sets the color of the text.
     *  @param r Red.   0-255
     *  @param g Green. 0-255
     *  @param b Blue.  0-255
     */
    void setColor(int r, int g, int b);

	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);

	float getWidth() const;
	float getHeight() const;

	bool isVisible() const;
	void setVisible(bool visible);

private:
	float m_x{ 0 };
	float m_y{ 0 };
	float m_width{ 0 };
	float m_height{ 0 };

	bool m_visible{ true };

	Texture* m_texture{ NULL };
    SDL_Color m_color;
	int m_fontSize{ 0 };
	SDL_Renderer* m_renderer{ NULL };
public:
    static std::map<int, TTF_Font*> standard_font;
    static std::list<Text*> s_textList;
};

#endif 
