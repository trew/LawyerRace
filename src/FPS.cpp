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


#include "FPS.hpp"

FPS FPS::FPSControl;

FPS::FPS() {
    oldTime = 0;
    lastTime = 0;
    frames = 0;
    numFrames = 0;
}

FPS::~FPS() {
}

void FPS::Update() {
    if (oldTime + 1000 < SDL_GetTicks()) {
        oldTime = SDL_GetTicks();
        numFrames = frames;
        frames = 0;
    }
//    speedFactor = ((SDL_GetTicks() - lastTime) / 1000.0f) * config::SPEED_FACTOR * config::GAME_SPEED;
    lastTime = SDL_GetTicks();
    frames++;
}

int FPS::GetFPS() {
    return numFrames;
}
