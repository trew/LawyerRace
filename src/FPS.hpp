/*
    Lawyer Race - A game about escaping the law
    Copyright (C) 2012 Samuel Andersson

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _FPS_H_
#define _FPS_H_

#include <SDL/SDL.h>
#include "Gameconfig.hpp"

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
