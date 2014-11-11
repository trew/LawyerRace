#ifndef LWR_ROCK_HPP
#define LWR_ROCK_HPP

#include "LawyerRace/Entity/Entity.hpp"

class Rock: public Entity {
public:
	Rock(TextureRegion* region, const float x, const float y, const int _rockType);
    virtual ~Rock();

    void update(float timeStep) override;
};

#endif
