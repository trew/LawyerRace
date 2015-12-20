#ifndef LWR_ABSTRACTSTATE_HPP
#define LWR_ABSTRACTSTATE_HPP

#include <SDL.h>
#include <LawyerEngine/LawyerEngine.hpp>

class AbstractState : public lwe::State
{
public:
  virtual ~AbstractState() {}
  virtual bool init() override { return true; }
  virtual void cleanup() override {}

  virtual void pause() override {}
  virtual void resume() override {}

  virtual bool handleEvent(const SDL_Event &ev) override { return false; }
  virtual void copyDataForInterpolation() override {}
  virtual void update(const float timeStep) override {}
  virtual void render(SDL_Renderer* const renderer, const float timeAlpha) override {}

protected:
  AbstractState() : lwe::State() {}
};

#endif
