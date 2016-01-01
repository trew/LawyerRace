#ifndef LWR_SETTINGSSTATE_HPP
#define LWR_SETTINGSSTATE_HPP

#include <LawyerRace/Core/AbstractState.hpp>

class SettingsState : public AbstractState
{
public:
  SettingsState();
  virtual ~SettingsState();

  bool handleEvent(const SDL_Event& ev) override;

private:
  lwe::EventCondition back;
};

#endif