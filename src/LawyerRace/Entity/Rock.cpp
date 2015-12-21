#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Entity/Rock.hpp>
#include <LawyerRace/Core/Config.hpp>

Rock::Rock(lwe::TextureRegion* region, const float x, const float y, const int _rockType)
	: AbstractEntity(region, x, y, config::R_WIDTH[_rockType - 1], config::R_HEIGHT[_rockType - 1])
{
  if (_rockType < 1 || _rockType > 3)
  {
    LOG_ERROR("Tried to create rock of unsupported type.\n");
    return;
  }
	setVelocity(0, config::R_VELOCITY[_rockType - 1]);
}

Rock::~Rock()
{
}

void Rock::update(float timeStep)
{
	setY(getY() + (getVelocityY() * timeStep));
	if (getY() > config::W_HEIGHT) getManager()->remove(this);
}