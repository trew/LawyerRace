#include "TextureRegion.h"

TextureRegion::TextureRegion() :m_texture(NULL) {
}

TextureRegion::TextureRegion(TextureRegion const& region) : m_texture(region.m_texture) {
	setRegion(region.x, region.y, region.regionWidth, region.regionHeight);
}

TextureRegion::TextureRegion(Texture* const texture) : TextureRegion(texture, texture->W(), texture->H()) {
}

TextureRegion::TextureRegion(Texture* const texture, int width, int height) : TextureRegion(texture, 0, 0, width, height) {
}

TextureRegion::TextureRegion(Texture* const texture, int x, int y, int width, int height) : m_texture(texture) {
	setRegion(x, y, width, height);
}

TextureRegion::~TextureRegion() {
}

void TextureRegion::setRegion(Texture* const texture) {
	setRegion(0, 0, texture->W(), texture->H());
}

void TextureRegion::setRegion(TextureRegion* const textureRegion) {
	setRegion(textureRegion->x, textureRegion->y, textureRegion->regionWidth, textureRegion->regionHeight);
}

void TextureRegion::setRegion(TextureRegion const& textureRegion) {
	setRegion(textureRegion.x, textureRegion.y, textureRegion.regionWidth, textureRegion.regionHeight);
}

void TextureRegion::setRegion(int _x, int _y, int _width, int _height) {
	x = _x;
	y = _y;
	regionWidth = _width;
	regionHeight = _height;
	m_regionRect = SDL_Rect{ x, y, regionWidth, regionHeight };
}

SDL_Rect const& TextureRegion::getRect() {
	return m_regionRect;
}

int TextureRegion::getRegionX() const {
	return x;
}

int TextureRegion::getRegionY() const {
	return y;
}

int TextureRegion::getRegionWidth() const {
	return regionWidth;
}

int TextureRegion::getRegionHeight() const {
	return regionHeight;
}

Texture* const TextureRegion::getTexture() {
	return m_texture;
}