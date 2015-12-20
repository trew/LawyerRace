#ifndef LWR_ENTITY_HPP
#define LWR_ENTITY_HPP

#include <LawyerEngine/LawyerEngine.hpp>
#include <string>
#include <vector>

class AbstractEntity : public lwe::Entity
{
public:
  AbstractEntity();
  AbstractEntity(lwe::TextureRegion* region);
  AbstractEntity(lwe::TextureRegion* region, float x, float y, float w, float h);
  AbstractEntity(std::vector<lwe::TextureRegion*> regions);
  AbstractEntity(std::vector<lwe::TextureRegion*> regions, float x, float y);
  AbstractEntity(std::vector<lwe::TextureRegion*> regions, float x, float y, float w, float h);

  virtual ~AbstractEntity();

  virtual void render(SDL_Renderer* renderer, float timeAlpha, unsigned int index);

  virtual void render(SDL_Renderer* renderer, float timeAlpha) override;
  virtual void update(float timeStep) override;

private:
  std::vector<lwe::TextureRegion*> m_regions;
};

#endif
