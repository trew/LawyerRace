#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/GameState.hpp>

lua_State* LawyerRace::LuaState { nullptr }; // TODO: change to non-static

LawyerRace::LawyerRace()
{
  if (LuaState == nullptr)
  {
    LuaState = luaL_newstate();
    luaL_openlibs(LuaState);
  }
}

LawyerRace::~LawyerRace()
{
  if (LuaState != nullptr)
  {
    lua_close(LuaState);
  }
}

void LawyerRace::init()
{
  LawyerText::textRenderer = getEngine()->getRenderer();
  getEngine()->setState(new GameState());
}