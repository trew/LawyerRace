#ifndef LWR_DOLLAR_HPP
#define LWR_DOLLAR_HPP

#include "LawyerRace/Entity/Entity.hpp"

class Dollar: public Entity {
public:
	Dollar(TextureRegion* region, const float x, const float y, const float w, const float h);

public:
    /**
     *  Destructor
     */
    virtual ~Dollar();
};

#endif
