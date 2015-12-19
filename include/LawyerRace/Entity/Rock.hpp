#ifndef LWR_ROCK_HPP
#define LWR_ROCK_HPP

#include <LawyerRace/Entity/AbstractEntity.hpp>

class Rock: public AbstractEntity {
public:
	Rock(lwe::TextureRegion* const region, float x, float y, int _rockType);
    virtual ~Rock();

    void update(float timeStep) override;
};

#endif
