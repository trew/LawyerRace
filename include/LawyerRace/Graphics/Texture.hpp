#ifndef LWR_TEXTURE_HPP
#define LWR_TEXTURE_HPP

#include <SDL.h>

#include <string>

class Texture {
public:
	/** if the texture is managed the underlying SDL texture is not destroyed when deleted */
	Texture(SDL_Texture* texture);
	~Texture();

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	SDL_Texture* getSDLTexture() const { return m_texture; }

	static Texture* createTexture(SDL_Renderer* renderer, std::string fileName);
private:
	int m_width;
	int m_height;

	int access;
	Uint32 format;

	SDL_Texture* m_texture;
};

#endif