#include <LawyerRace/Core/SettingsState.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>

SettingsState::SettingsState()
{
  back.addTrigger(std::make_shared<lwe::KeyboardTrigger>(SDLK_ESCAPE));
  back.addTrigger(std::make_shared<lwe::GameControllerButtonTrigger>(SDL_CONTROLLER_BUTTON_B));
}

SettingsState::~SettingsState()
{
}

bool SettingsState::handleEvent(const SDL_Event& ev)
{
  if (back(ev))
  {
    getEngine()->setState(getGame<LawyerRace>()->getMenuState());
    return true;
  }

  return false;
}