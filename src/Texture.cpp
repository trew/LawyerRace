#include "Texture.h"
#include "Log.hpp"

Texture::Texture() {
}

Texture::Texture(SDL_Texture* texture) : m_texture(texture) {
	SDL_QueryTexture(m_texture, &format, &access, &w, &h);
}

Texture::~Texture() {
}

int Texture::W() const {
	return w;
}

int Texture::H() const {
	return h;
}

SDL_Texture* Texture::getTexture() const {
	return m_texture;
}

Texture* Texture::createTexture(SDL_Renderer* renderer, std::string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		LOG_ERROR << "Couldn't load texture " << path << std::endl;
		return NULL;
	}
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL) {
		LOG_ERROR << "Couldn't load texture " << path << std::endl;
	}
	SDL_FreeSurface(loadedSurface);
	return new Texture(newTexture);
}