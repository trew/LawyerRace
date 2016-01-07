#include <LawyerRace/Entity/AbstractEntity.hpp>
#include <LawyerRace/Core/Config.hpp>
#include <iostream>

AbstractEntity::AbstractEntity(lwe::TextureRegion* const region)
  : AbstractEntity(region,
                   0,
                   0,
                   (float)region->getRegionWidth(),
                   (float)region->getRegionHeight())
{
}

AbstractEntity::AbstractEntity(lwe::TextureRegion* const region,
                               const float x,
                               const float y,
                               const float w,
                               const float h)
  : lwe::Entity(x, y, w, h)
{
  m_regions.push_back(region);
}

AbstractEntity::AbstractEntity(const std::vector<lwe::TextureRegion*>& regions)
  : AbstractEntity(regions, 0, 0)
{
}

AbstractEntity::AbstractEntity(const std::vector<lwe::TextureRegion*>& regions,
                               const float x,
                               const float y)
  : AbstractEntity(regions,
                   x,
                   y,
                   (float)regions.front()->getRegionWidth(),
                   (float)regions.front()->getRegionHeight())
{
}

AbstractEntity::AbstractEntity(const std::vector<lwe::TextureRegion*>& regions,
                               const float x,
                               const float y,
                               const float w,
                               const float h)
  : lwe::Entity(x, y, w, h)
{
  m_regions.insert(m_regions.end(), regions.begin(), regions.end());
}

AbstractEntity::~AbstractEntity() {
}

void AbstractEntity::render(SDL_Renderer* const renderer, const float timeAlpha, const unsigned int index)
{
  if (!isVisible())
  {
    return;
  }

  if (index >= m_regions.size() || index < 0)
  {
    return;
  }

  float x = lerp(getPreviousX(), getX(), timeAlpha);
  float y = lerp(getPreviousY(), getY(), timeAlpha);

  lwe::TextureRegion* region = m_regions[index];

  SDL_Rect destRect;
  destRect.x = (int)x;
  destRect.y = (int)y;
  destRect.h = (int)getHeight();
  destRect.w = (int)getWidth();

  SDL_SetTextureAlphaMod(region->getTexture()->getSDLTexture(), alpha);
  SDL_RenderCopy(renderer, region->getTexture()->getSDLTexture(), &region->getRect(), &destRect);
}

void AbstractEntity::render(SDL_Renderer* const renderer, const float timeAlpha)
{
  AbstractEntity::render(renderer, timeAlpha, 0);
}

void AbstractEntity::update(const float timeStep)
{
}

Uint8 AbstractEntity::getAlpha() const
{
  return alpha;
}

void AbstractEntity::setAlpha(const Uint8 a)
{
  alpha = a;
}