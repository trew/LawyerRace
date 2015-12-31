#include <LawyerRace/Event/Trigger.hpp>

KeyboardTrigger::KeyboardTrigger(const SDL_Keycode key)
  : key(key)
{
}

KeyboardTrigger::KeyboardTrigger(const SDL_Keycode key, const bool keyUp)
  : keyUp(keyUp), key(key)
{
}

KeyboardTrigger::~KeyboardTrigger()
{
}

bool KeyboardTrigger::isTriggered(const SDL_Event& ev)
{
  if ((keyUp && ev.type == SDL_KEYUP) || (!keyUp && ev.type == SDL_KEYDOWN))
  {
    return (ev.key.keysym.sym == key);
  }

  return false;
}
