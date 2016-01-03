#ifndef LWR_SPRITE_HPP
#define LWR_SPRITE_HPP

#include <LawyerEngine/Graphics/TextureRegion.hpp>

class Sprite
{
public:
  Sprite(TextureRegion* region, float x, float y);
  virtual ~Sprite();

private:
  float x { 0.f };
  float y { 0.f };
  float w { 0.f };
  float h { 0.f };

  TextureRegion* region;
};

#endif