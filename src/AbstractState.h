#ifndef _ABSTRACTSTATE_H_
#define _ABSTRACTSTATE_H_

#include <SDL/SDL.h>

class AbstractState {
public:
	AbstractState() {}
	virtual ~AbstractState() {}

	virtual bool Init()=0;
	virtual int Execute()=0;
	virtual void Cleanup()=0;

};

#endif
