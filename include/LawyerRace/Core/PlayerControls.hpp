#ifndef LWR_PLAYERCONTROLS_HPP
#define LWR_PLAYERCONTROLS_HPP

#include <SDL.h>

#include <LawyerEngine/LawyerEngine.hpp>

#include <string>
#include <map>

namespace luabridge
{
  class LuaRef;
}

class PlayerControls
{
public:
  PlayerControls();
  virtual ~PlayerControls();

  const lwe::EventCondition& getUp() const;
  const lwe::EventCondition& getDown() const;
  const lwe::EventCondition& getLeft() const;
  const lwe::EventCondition& getRight() const;
  const lwe::EventCondition& getStop() const;

  static void initialize();
  static const PlayerControls getControls(int player, const lwe::GameEngine*);

private:
  lwe::EventCondition up;
  lwe::EventCondition down;
  lwe::EventCondition left;
  lwe::EventCondition right;
  lwe::EventCondition stop;

private:
  static bool loadControlsLuaMethodFromFile(const std::string& file); 

  static void setControlsFromLuaTable(const luabridge::LuaRef& ref,
                                      const lwe::GameEngine* lwe,
                                      const std::string& action,
                                      int playerNum,
                                      lwe::EventCondition& condition);
  static void setControl(int player,
                         const lwe::GameEngine*,
                         lwe::EventCondition&,
                         const std::string& referencekey,
                         const std::string& keyname);

  static bool initialized;
  static std::map<std::string, SDL_Keycode> __keymap;
  static std::map<std::string, SDL_GameControllerButton> __gameControllerMap;
};

#endif
