#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/PlayerControls.hpp>
#include <LawyerRace/Core/Config.hpp>
#include <LawyerRace/Utils/StringUtils.hpp>
#include <fstream>

#include <LuaBridge/LuaBridge.h>

std::map<std::string, SDL_Keycode> PlayerControls::__keymap;
std::map<std::string, SDL_GameControllerButton> PlayerControls::__gameControllerMap;
bool PlayerControls::keyMapInitialized = false;

PlayerControls::PlayerControls()
{
}

PlayerControls::~PlayerControls()
{
}

void PlayerControls::initializeKeyMap()
{
  LOG_DEBUG("Setting up keymap...");
  __keymap["up"] = SDLK_UP;
  __keymap["down"] = SDLK_DOWN;
  __keymap["left"] = SDLK_LEFT;
  __keymap["right"] = SDLK_RIGHT;
  __keymap["num_1"] = SDLK_KP_1;
  __keymap["num_2"] = SDLK_KP_2;
  __keymap["num_3"] = SDLK_KP_3;
  __keymap["num_4"] = SDLK_KP_4;
  __keymap["num_5"] = SDLK_KP_5;
  __keymap["num_6"] = SDLK_KP_6;
  __keymap["num_7"] = SDLK_KP_7;
  __keymap["num_8"] = SDLK_KP_8;
  __keymap["num_9"] = SDLK_KP_9;
  __keymap["num_0"] = SDLK_KP_0;
  __keymap["rctrl"] = SDLK_RCTRL;
  __keymap["lctrl"] = SDLK_LCTRL;
  __keymap["rshift"] = SDLK_RSHIFT;
  __keymap["lshift"] = SDLK_LSHIFT;
  __keymap["lalt"] = SDLK_LALT;
  __keymap["altgr"] = SDLK_MODE;
  __keymap["tab"] = SDLK_TAB;
  __keymap["insert"] = SDLK_INSERT;
  __keymap["delete"] = SDLK_DELETE;
  __keymap["home"] = SDLK_HOME;
  __keymap["end"] = SDLK_END;
  __keymap["pgup"] = SDLK_PAGEUP;
  __keymap["pgdown"] = SDLK_PAGEDOWN;
  __keymap["backspace"] = SDLK_BACKSPACE;
  __keymap["return"] = SDLK_RETURN;
  __keymap["space"] = SDLK_SPACE;

  __gameControllerMap["a"] = SDL_CONTROLLER_BUTTON_A;
  __gameControllerMap["b"] = SDL_CONTROLLER_BUTTON_B;
  __gameControllerMap["x"] = SDL_CONTROLLER_BUTTON_X;
  __gameControllerMap["y"] = SDL_CONTROLLER_BUTTON_Y;
  __gameControllerMap["up"] = SDL_CONTROLLER_BUTTON_DPAD_UP;
  __gameControllerMap["down"] = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
  __gameControllerMap["left"] = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
  __gameControllerMap["right"] = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
  __gameControllerMap["l1"] = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
  __gameControllerMap["r1"] = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
  __gameControllerMap["back"] = SDL_CONTROLLER_BUTTON_BACK;
  __gameControllerMap["guide"] = SDL_CONTROLLER_BUTTON_GUIDE;
  __gameControllerMap["start"] = SDL_CONTROLLER_BUTTON_START;
  keyMapInitialized = true;
}

inline bool inrange(int x,int a,int b)
{
  return (a <= x && x <= b);
} 

/**
 * @return true if x exist in list
 */
inline bool in(int x, int list[])
{
  const int listSize = sizeof(list);
  for (int i = 0; i < listSize; i++)
  {
    if (x == list[i])
    {
      return true;
    }
  }

  return false;
}

/**
 * Sets key to selected key in keymap
 * Defaults to SDLK_UNKNOWN if no key found in keymap or in Ascii table
 * Referencekey is used for debugging
 */
void PlayerControls::setControl(lwe::EventCondition& condition, std::string referencekey, std::string keyname)
{
  std::string controllerKeyName = "";
  if (StringUtils::startsWith(keyname, "controller_"))
  {
    controllerKeyName = keyname.substr(11, keyname.size());
    LOG_DEBUG("Controller Key name: %s", controllerKeyName.c_str());
  }

  if (keyname.length() == 1)
  {
    /* Ascii? if so, ez convert to SDL_Keysym instantly.
     * see SDL_keysym.h for values mapped to SDL keys.
    */

    int comparekey = keyname[0];
    int customvalues[6] = {8,9,12,13,19,27};
    if (inrange(comparekey,91,127) || inrange(comparekey, 32, 64) || in(comparekey, customvalues))
    { //if valid ascii
      condition.addTrigger(new lwe::KeyboardTrigger(comparekey, true));
    }
  }
  else if (__keymap.find(keyname) != __keymap.end())
  {
    condition.addTrigger(new lwe::KeyboardTrigger(__keymap[keyname], true));
  }
  else if (__gameControllerMap.find(controllerKeyName) != __gameControllerMap.end())
  {
    condition.addTrigger(new lwe::GameControllerButtonTrigger(__gameControllerMap[controllerKeyName], true));
  }

  if (!condition.hasTriggers())
  {
    LOG_ERROR("%s was not set.", referencekey.c_str());
  }
}

void PlayerControls::setControlsFromLuaTable(const luabridge::LuaRef& table, std::string action, std::string playerNum, lwe::EventCondition& condition)
{
  if (table[action].isString())
  {
    setControl(condition, "player" + playerNum + "." + action, table[action].cast<std::string>());
  }
  else if (table[action].isTable())
  {
    luabridge::LuaRef actionTable = table[action];
    luabridge::LuaRef ref = actionTable[1];
    if (ref.isNil())
    {
      LOG_ERROR("WTF");
    }
    for (int i = 2; !ref.isNil(); i++)
    {
      if (ref.isString())
      {
        setControl(condition, "player" + playerNum + "." + action, ref.cast<std::string>());
      }

      ref = actionTable[i];
    }
  }
  
}

void PlayerControls::setControlsForPlayer(int playerNumber, PlayerControls& controls, luabridge::LuaRef table)
{
  if (playerNumber < 1 || playerNumber > 4)
  {
    LOG_ERROR("Setting keys for player %i is not supported.", playerNumber);
    return; // TODO log?
  }

  using namespace luabridge;

  if (!table.isTable())
  {
    return;
  }

  std::string n = std::to_string(playerNumber);
  setControlsFromLuaTable(table, "down", n, controls.down);
  setControlsFromLuaTable(table, "up", n, controls.up);
  setControlsFromLuaTable(table, "right", n, controls.right);
  setControlsFromLuaTable(table, "left", n, controls.left);
  setControlsFromLuaTable(table, "stop", n, controls.stop);
}

bool PlayerControls::loadControlsFromFile(PlayerControls controls[], std::string _file)
{
  if (!keyMapInitialized) initializeKeyMap(); //make sure keymap is filled.

  LOG_DEBUG("---PARSING KEYSET FILE---");
  _file = Config::getInstance().getFile(_file);
  lua_State* L = LawyerRace::LuaState;

  if (luaL_loadfile(L, _file.c_str()))
  {
    LOG_ERROR("Couldn't read keysets from file %s", _file.c_str());
  }

  if (lua_pcall(L, 0, 0, 0))
  {
    LOG_ERROR("Error calling keysets file");
  }

  using namespace luabridge;

  LuaRef keysets = getGlobal(L, "controls");
  if (keysets.isTable())
  {
    setControlsForPlayer(1, controls[0], keysets["player1"]);
    setControlsForPlayer(2, controls[1], keysets["player2"]);
    setControlsForPlayer(3, controls[2], keysets["player3"]);
    setControlsForPlayer(4, controls[3], keysets["player4"]);

    // ultraexception for player 1
    if (Config::getInstance().getPlayerCount() == 1)
    {
      LuaRef p1 = keysets["player1"];
      if (p1.isTable())
      {
        if (p1["one"].isTable())
        {
          LuaRef ref = p1["one"];
          if (ref.isTable())
          {
            setControlsFromLuaTable(ref, "stop", "1", controls[0].stop);
          }
        }
      }
    }
  }

  return true;
}

const lwe::EventCondition& PlayerControls::getUp() const
{
  return up;
}

const lwe::EventCondition& PlayerControls::getDown() const
{
  return down;
}

const lwe::EventCondition& PlayerControls::getLeft() const
{
  return left;
}

const lwe::EventCondition& PlayerControls::getRight() const
{
  return right;
}

const lwe::EventCondition& PlayerControls::getStop() const
{
  return stop;
}
