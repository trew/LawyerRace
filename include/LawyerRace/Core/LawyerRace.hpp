#ifndef LWR_LAWYERRACE_HPP
#define LWR_LAWYERRACE_HPP

#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/MenuState.hpp>
#include <LawyerRace/Core/GameState.hpp>
#include <memory>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}


class LawyerRace : public lwe::Game
{
public:
  LawyerRace();
  virtual ~LawyerRace();

  virtual void init() override;

  MenuState* getMenuState() const;
  GameState* getGameState() const;

private:
  std::shared_ptr<MenuState> menuState;
  std::shared_ptr<GameState> gameState;

public:
  static lua_State* LuaState; // TODO: change to non-static
  static std::unique_ptr<lwe::Font> standardFont;
};

#endif