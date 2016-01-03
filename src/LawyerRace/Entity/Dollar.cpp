#include <LawyerRace/Entity/Dollar.hpp>

Dollar::Dollar(lwe::TextureRegion* const region,
               const float x,
               const float y,
               const float w,
               const float h)
  : AbstractEntity(region, x, y, w, h)
{
}

Dollar::~Dollar()
{
}
