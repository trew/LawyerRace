#include "LawyerRace/Utils/FPS.hpp"

void FPS::Update() {
    if (oldTime + 1000 < SDL_GetTicks()) {
        oldTime = SDL_GetTicks();
		frames = 0;
    }
	frames++;
}

int FPS::GetFPS() {
	return (int)(frames / ((float)(SDL_GetTicks() - oldTime) / 1000.f));
}
