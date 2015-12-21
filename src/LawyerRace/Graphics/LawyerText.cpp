#include <LawyerRace/Graphics/LawyerText.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>

SDL_Renderer* LawyerText::textRenderer;

LawyerText::LawyerText(const int number, const int fontSize, const float x, const float y, int r, int g, int b)
    : LawyerText(std::to_string(number), fontSize, x, y, r, g, b)
{
}


LawyerText::LawyerText(std::string text, const int fontSize, const float x, const float y, int r, int g, int b)
    : lwe::Text(textRenderer, LawyerRace::standardFont.get(), text, fontSize, x, y, r, g, b)
{
}
