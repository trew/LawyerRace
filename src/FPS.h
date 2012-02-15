#ifndef _FPS_H_
#define _FPS_H_

#include <SDL.h>
#include "config.h"

class FPS {
public:
	FPS();
	virtual ~FPS();

public:
	static FPS FPSControl;

private:
	unsigned int oldTime;
	unsigned int lastTime;
	float speedFactor;
	unsigned int numFrames;
	unsigned int frames;

public:
	void Update();
	int GetFPS();
	float GetSpeedFactor();

};

#endif
