#ifndef LWR_TEXTUREREGION_HPP
#define LWR_TEXTUREREGION_HPP

#include "LawyerRace/Graphics/Texture.hpp"

class TextureRegion {
public:
	TextureRegion();
	TextureRegion(TextureRegion const& region);
	TextureRegion(Texture* const texture);
	TextureRegion(Texture* const texture, int width, int height);
	TextureRegion(Texture* const texture, int x, int y, int width, int height);
	virtual ~TextureRegion();

	int x, y;
	int regionWidth, regionHeight;

	void setRegion(Texture* const texture);
	void setRegion(TextureRegion* const textureRegion);
	void setRegion(TextureRegion const& textureRegion);
	void setRegion(int x, int y, int width, int height);

	int getRegionX() const;
	int getRegionY() const;
	int getRegionWidth() const;
	int getRegionHeight() const;

	SDL_Rect const& getRect(); //lol
	Texture* const getTexture();
private:
	Texture* const m_texture;
	SDL_Rect m_regionRect;
};

#endif