#ifndef LWR_PLAYERCONTROLS_HPP
#define LWR_PLAYERCONTROLS_HPP

#include <SDL.h>

#include <LawyerRace/Event/EventCondition.hpp>

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

  const EventCondition& getUp() const;
  const EventCondition& getDown() const;
  const EventCondition& getLeft() const;
  const EventCondition& getRight() const;
  const EventCondition& getStop() const;

private:
  EventCondition up;
  EventCondition down;
  EventCondition left;
  EventCondition right;
  EventCondition stop;

  PlayerControls(const PlayerControls& copy) = delete;

private:
  static void setControlsFromLuaTable(const luabridge::LuaRef& ref, std::string action, std::string playerNum, EventCondition& condition);
  static void setControlsForPlayer(int playerNumber, PlayerControls&, luabridge::LuaRef table);
  static void setControl(EventCondition&, std::string referencekey, std::string keyname);

  static void initializeKeyMap();
  static bool keyMapInitialized;
  static std::map<std::string, SDL_Keycode> __keymap;
  static std::map<std::string, SDL_GameControllerButton> __gameControllerMap;
};

#endif
