#ifndef LWR_FPS_HPP
#define LWR_FPS_HPP

#include <SDL.h>
#include "LawyerRace/Core/Gameconfig.hpp"

class FPS {
public:
	FPS() {}
	virtual ~FPS() {}
    void Update();
    int GetFPS();

private:
	unsigned int oldTime{ 0 };
	unsigned int frames{ 0 };
};

#endif
