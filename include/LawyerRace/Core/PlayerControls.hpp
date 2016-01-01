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

  static bool loadControlsFromFile(PlayerControls controls[], std::string file); 

  const lwe::EventCondition& getUp() const;
  const lwe::EventCondition& getDown() const;
  const lwe::EventCondition& getLeft() const;
  const lwe::EventCondition& getRight() const;
  const lwe::EventCondition& getStop() const;

private:
  lwe::EventCondition up;
  lwe::EventCondition down;
  lwe::EventCondition left;
  lwe::EventCondition right;
  lwe::EventCondition stop;

  PlayerControls(const PlayerControls& copy) = delete;

private:
  static void setControlsFromLuaTable(const luabridge::LuaRef& ref, std::string action, std::string playerNum, lwe::EventCondition& condition);
  static void setControlsForPlayer(int playerNumber, PlayerControls&, luabridge::LuaRef table);
  static void setControl(lwe::EventCondition&, std::string referencekey, std::string keyname);

  static void initializeKeyMap();
  static bool keyMapInitialized;
  static std::map<std::string, SDL_Keycode> __keymap;
  static std::map<std::string, SDL_GameControllerButton> __gameControllerMap;
};

#endif
