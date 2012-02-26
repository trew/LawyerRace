#ifndef _GAME_H_
#define _GAME_H_

#include <SDL/SDL.h>
#include "GameState.hpp"
//#include "MenuState.hpp"

class Game {
public:
    Game();                         ///< Constructor
    virtual ~Game();                ///< Destructor
    static Game StateControl;       ///< Singleton instance for state management
    static SDL_Surface* mainScreen; ///< the one and only main screen surface

    virtual int Execute();          ///< Starts the game

    bool Init();                    ///< Starts up SDL and other dependencies
    void Cleanup();                 ///< Deletes instances and shut down

    void setState(AbstractState* _newState);    ///< To be used with StateControl. Sets nextState and
    AbstractState* gameState;                   ///< Pointer to the initialized GameState
//  AbstractState* menuState;                   ///< Pointer to the initialized MenuState
private:
    static AbstractState* nextState;            ///< Holds next state (we want to be able to change the state at any point, but a state must run it's full loop until it can switch)
    static AbstractState* currentState;     ///< Holds the current state

};

#endif
