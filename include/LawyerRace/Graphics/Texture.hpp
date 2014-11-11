#ifndef LWR_TEXTURE_HPP
#define LWR_TEXTURE_HPP

#include <SDL.h>

#include <string>

class Texture {
public:
	Texture(SDL_Texture* texture);
	~Texture();

	static Texture* createTexture(SDL_Renderer* renderer, std::string path);

	int W() const;
	int H() const;

	SDL_Texture* getTexture() const;
private:
	Texture();

	int w, h;
	int access;
	Uint32 format;

	SDL_Texture* m_texture;
};

#endif