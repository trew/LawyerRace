#ifndef LWR_TRIGGER_HPP
#define LWR_TRIGGER_HPP

#include <SDL.h>

class Trigger
{
public:
  Trigger();
  virtual ~Trigger();

  virtual bool isTriggered(const SDL_Event& ev) = 0;
};

class KeyboardTrigger : public Trigger
{
public:
  KeyboardTrigger(SDL_Keycode key);
  KeyboardTrigger(SDL_Keycode key, bool keyUp);
  virtual ~KeyboardTrigger();

  bool isTriggered(const SDL_Event& ev);

private:
  bool keyUp{ false };
  SDL_Keycode key{ 0 };
};

class GameControllerButtonTrigger : public Trigger
{
public:

};

#endif