#ifndef LWR_LUAHELPER_HPP
#define LWR_LUAHELPER_HPP

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

class LuaHelper
{
public:
  static LuaHelper& getInstance()
  {
    static LuaHelper luaHelper;
    return luaHelper;
  }

  lua_State* getState() const;

  bool load(const std::string& file);

private:
  LuaHelper();
  ~LuaHelper();

  lua_State* luaState;

};

#endif