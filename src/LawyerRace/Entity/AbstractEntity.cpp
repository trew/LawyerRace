#include <LawyerRace/Entity/AbstractEntity.hpp>
#include <LawyerRace/Core/Config.hpp>
#include <iostream>


AbstractEntity::AbstractEntity(lwe::TextureRegion* region) : AbstractEntity(region, 0, 0, (float)region->getRegionWidth(), (float)region->getRegionHeight())
{
}

AbstractEntity::AbstractEntity(lwe::TextureRegion* region, float x, float y, float w, float h) : lwe::Entity(x, y, w, h)
{
	m_regions.push_back(region);
}

AbstractEntity::AbstractEntity(const std::vector<lwe::TextureRegion*>& regions) : AbstractEntity(regions, 0, 0)
{
}

AbstractEntity::AbstractEntity(const std::vector<lwe::TextureRegion*>& regions, float x, float y) : AbstractEntity(regions, x, y, (float)regions.front()->getRegionWidth(), (float)regions.front()->getRegionHeight())
{
}

AbstractEntity::AbstractEntity(const std::vector<lwe::TextureRegion*>& regions, float x, float y, float w, float h) : lwe::Entity(x, y, w, h)
{
	m_regions.insert(m_regions.end(), regions.begin(), regions.end());
}

AbstractEntity::~AbstractEntity() {
}

void AbstractEntity::render(SDL_Renderer* const renderer, float timeAlpha, unsigned int index)
{
	if (!isVisible())
  {
    return;
  }
	if (index >= m_regions.size() || index < 0) return;

	float x = lerp(getPreviousX(), getX(), timeAlpha);
	float y = lerp(getPreviousY(), getY(), timeAlpha);

	lwe::TextureRegion* region = m_regions[index];

	SDL_Rect destRect;
	destRect.x = (int)x;
	destRect.y = (int)y;
	destRect.h = (int)getHeight();
	destRect.w = (int)getWidth();

	SDL_RenderCopy(renderer, region->getTexture()->getSDLTexture(), &region->getRect(), &destRect);
}

void AbstractEntity::render(SDL_Renderer* renderer, float timeAlpha) {
	AbstractEntity::render(renderer, timeAlpha, 0);
}

void AbstractEntity::update(float timeStep) {
}
