#include <LawyerRace/Core/LuaHelper.hpp>
#include <LawyerEngine/Utils/Log.hpp>

void logDebug(const char* str)
{
  LOG_DEBUG("LUA: %s", str);
}

LuaHelper::LuaHelper()
{
  luaState = luaL_newstate();
  luaL_openlibs(luaState);

  // TODO setup methods and stuff
  using namespace luabridge;

  getGlobalNamespace(luaState)
    .beginNamespace("lwr")
      .addFunction<void (*) (const char*)>("debug", logDebug)
      .beginClass<LuaHelper>("LuaHelper")
      .endClass()
    .endNamespace();
}

LuaHelper::~LuaHelper()
{
  lua_close(luaState);
  luaState = nullptr;
}

lua_State* LuaHelper::getState() const
{
  return luaState;
}

bool LuaHelper::load(const std::string& file)
{
  if (luaL_loadfile(luaState, file.c_str()))
  {
    return false;
  }

  if (lua_pcall(luaState, 0, 0, 0))
  {
    return false;
  }

  return true;
}