#ifndef LWR_ABSTRACTSTATE_HPP
#define LWR_ABSTRACTSTATE_HPP

#include <SDL.h>

class GameEngine;

class AbstractState {
	friend class GameEngine;

public:
	virtual ~AbstractState();
    virtual bool init()=0;

	virtual void cleanup() = 0;
	
	virtual void pause();
	virtual void resume();

	virtual void handleEvent(SDL_Event &ev) = 0;
	virtual void copyDataForInterpolation();
	virtual void update(float timeStep) = 0;
	virtual void render(float timeAlpha) = 0;

	GameEngine* getEngine();
protected:
	AbstractState();

private:
	GameEngine* m_engine;

};

#endif
