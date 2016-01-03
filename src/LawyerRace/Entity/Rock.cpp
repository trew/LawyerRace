#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Entity/Rock.hpp>
#include <LawyerRace/Core/Config.hpp>

Rock::Rock(lwe::TextureRegion* region, const float x, const float y, const int _rockType)
  : AbstractEntity(region,
                   x,
                   y,
                   Config::getInstance().getRockWidth(_rockType - 1),
                   Config::getInstance().getRockHeight(_rockType - 1))
{
  if (_rockType < 1 || _rockType > 3)
  {
    LOG_ERROR("Tried to create rock of unsupported type.\n");
    return;
  }

  setVelocity(0, Config::getInstance().getRockVelocity(_rockType - 1));
}

Rock::~Rock()
{
}

void Rock::update(const float timeStep)
{
  setY(getY() + (getVelocityY() * timeStep));
  if (getY() > Config::getInstance().getGameHeight())
  {
    getManager()->remove(this);
  }
}