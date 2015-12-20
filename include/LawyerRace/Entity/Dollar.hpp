#ifndef LWR_DOLLAR_HPP
#define LWR_DOLLAR_HPP

#include <LawyerRace/Entity/AbstractEntity.hpp>

class Dollar: public AbstractEntity
{
public:
  Dollar(lwe::TextureRegion* region, float x, float y, float w, float h);
  virtual ~Dollar();
};

#endif
