#ifndef LWR_LAWYERRACE_HPP
#define LWR_LAWYERRACE_HPP

#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/MenuState.hpp>
#include <LawyerRace/Core/GameState.hpp>
#include <LawyerRace/Core/SettingsState.hpp>
#include <memory>

class LawyerRace : public lwe::Game
{
public:
  LawyerRace();
  virtual ~LawyerRace();

  virtual void init() override;

  MenuState* getMenuState() const;
  GameState* getGameState() const;
  SettingsState* getSettingsState() const;

private:
  std::unique_ptr<MenuState> menuState;
  std::unique_ptr<GameState> gameState;
  std::unique_ptr<SettingsState> settingsState;

public:
  static std::unique_ptr<lwe::Font> standardFont;
};

#endif