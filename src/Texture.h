#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

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