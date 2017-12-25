#ifndef LWR_PLAYERCONTROLS_HPP
#define LWR_PLAYERCONTROLS_HPP

#include <SDL.h>

#include <LawyerEngine/LawyerEngine.hpp>

#include <string>
#include <map>

#include <json/json.hpp>

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

  static void initialize(const lwe::GameEngine* engine);
  static const PlayerControls& getControls(int player, const lwe::GameEngine*);

private:
  lwe::EventCondition up;
  lwe::EventCondition down;
  lwe::EventCondition left;
  lwe::EventCondition right;
  lwe::EventCondition stop;

private:
  static std::vector<PlayerControls> loadControlsFromJsonFile(const std::string& _file, const std::list<SDL_GameController*>& controllers, const std::map<SDL_GameController*, int>& controllerToDeviceId);

  static void setControl(const nlohmann::json& entry,
                         const std::string& key,
                         const int& player,
                         lwe::EventCondition& condition,
                         const std::list<SDL_GameController*>& controllers,
                         const std::map<SDL_GameController*, int>& controllerToDeviceId);
  
  static void setControl(int player,
                         const std::list<SDL_GameController*>& controllers,
                         const std::map<SDL_GameController*, int>& controllerToDeviceId,
                         lwe::EventCondition& condition,
                         const std::string& keyname);


  static std::map<std::string, SDL_Keycode> __keymap;
  static std::map<std::string, SDL_GameControllerButton> __gameControllerMap;
  static std::vector<PlayerControls> __controls;
};

#endif
