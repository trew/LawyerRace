#ifndef LWR_MENUSTATE_HPP
#define LWR_MENUSTATE_HPP

#include <SDL.h>

#include "LawyerRace/Core/Gameconfig.hpp"
#include "LawyerRace/Graphics/Text.hpp"
#include "LawyerRace/Utils/FPS.hpp"
#include "LawyerRace/Graphics/TextureAtlas.hpp"

#include "LawyerRace/Core/AbstractState.hpp"
#include "LawyerRace/Core/GameEngine.hpp"

#include "LawyerRace/Entity/EntityManager.hpp"

class MenuState: public AbstractState {
public:
    MenuState();
    virtual ~MenuState();

    SDL_Window* window;
	SDL_Renderer* renderer;

public:

    /* STATE FUNCTIONS */

    bool init();
    void cleanup();

	void copyDataForInterpolation();

	void update(float timeStep);
    void handleEvent(SDL_Event &ev);
    void render(float timeAlpha);

	void pause();

	void resume();

    /* !STATE FUNCTIONS */
};

#endif
