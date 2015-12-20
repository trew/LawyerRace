#ifndef LWR_MENUSTATE_HPP
#define LWR_MENUSTATE_HPP

#include <LawyerRace/Core/Config.hpp>
#include <LawyerRace/Core/AbstractState.hpp>

class MenuState: public AbstractState
{
public:
  MenuState();
  virtual ~MenuState();

  /* STATE FUNCTIONS */
  bool init() override;
  void cleanup() override;

  void copyDataForInterpolation() override;

  void update(const float timeStep) override;
  bool handleEvent(const SDL_Event &ev) override;
  void render(SDL_Renderer* const renderer, const float timeAlpha) override;

  void pause() override;
  void resume() override;
};

#endif
