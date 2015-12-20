#ifndef LWR_LAWYERRACE_HPP
#define LWR_LAWYERRACE_HPP

#include <LawyerEngine/LawyerEngine.hpp>

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

public:
  static lua_State* LuaState; // TODO: change to non-static
};

#endif