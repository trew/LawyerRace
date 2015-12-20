#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/KeySet.hpp>
#include <LawyerRace/Core/Config.hpp>
#include <fstream>

#include <LuaBridge/LuaBridge.h>

std::map<std::string, SDL_Keycode> KeySet::__keymap;
bool KeySet::keymap_setup = false;

void KeySet::SetupKeymap()
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
  keymap_setup = true;
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

void KeySet::setKey(SDL_Keycode& key, std::string _referencekey, std::string _keyname)
{
  /* Sets key to selected key in keymap
   * Defaults to SDLK_UNKNOWN if no key found in keymap or in Ascii table
   * Referencekey is used for debugging
   */
  if (_keyname.length() == 1)
  {
    /* Ascii? if so, ez convert to SDL_Keysym instantly.
     * see SDL_keysym.h for values mapped to SDL keys.
    */

    int comparekey = _keyname[0];
    int customvalues[6] = {8,9,12,13,19,27};
    if (inrange(comparekey,91,127) || inrange(comparekey, 32, 64) || in(comparekey, customvalues))
    { //if valid ascii
      key = comparekey;
    }
    else
    {
      key = SDLK_UNKNOWN;
    }
  }
  else if (__keymap.find(_keyname) != __keymap.end())
  {
    key = __keymap[_keyname];
  }
  else
  {
    key = SDLK_UNKNOWN; // == 0
  }

  if (key == SDLK_UNKNOWN)
  {
    LOG_ERROR("Warning: %s was not set.", _referencekey.c_str());
  }
}

void KeySet::setKeysForPlayer(int playerNumber, KeySet* _ks, luabridge::LuaRef table)
{
  if (playerNumber < 1 || playerNumber > 4)
  {
    return; // TODO log?
  }

  using namespace luabridge;

  if (!table.isTable())
  {
    return;
  }

  std::string n = std::to_string(playerNumber);
  if (table["down"].isString())
    setKey(_ks[playerNumber - 1].K_DOWN, "player" + n + ".down", table["down"].cast<std::string>());
  if (table["up"].isString())
    setKey(_ks[playerNumber - 1].K_UP, "player" + n + ".up", table["up"].cast<std::string>());
  if (table["right"].isString())
    setKey(_ks[playerNumber - 1].K_RIGHT, "player" + n + ".right", table["right"].cast<std::string>());
  if (table["left"].isString())
    setKey(_ks[playerNumber - 1].K_LEFT, "player" + n + ".left", table["left"].cast<std::string>());
  if (table["stop"].isString())
    setKey(_ks[playerNumber - 1].K_STOP, "player" + n + ".stop", table["stop"].cast<std::string>());
}

bool KeySet::LoadKeysetFromFile(KeySet* _ks, std::string _file)
{
  if (!keymap_setup) SetupKeymap(); //make sure keymap is filled.

  LOG_DEBUG("---PARSING KEYSET FILE---");
  _file = config::path + _file;
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

  LuaRef keysets = getGlobal(L, "keysets");
  if (keysets.isTable())
  {
    setKeysForPlayer(1, _ks, keysets["player1"]);
    setKeysForPlayer(2, _ks, keysets["player2"]);
    setKeysForPlayer(3, _ks, keysets["player3"]);
    setKeysForPlayer(4, _ks, keysets["player4"]);

    // ultraexception for player 1
    if (config::NUM_OF_PLAYERS == 1)
    {
      LuaRef p1 = keysets["player1"];
      if (p1.isTable())
      {
        if (p1["one"].isTable())
        {
          LuaRef ref = p1["one"];
          if (ref.isTable())
          {
            if (ref["stop"].isString())
              setKey(_ks[0].K_STOP, "player1.stop", ref["stop"].cast<std::string>());
          }
        }
      }
    }
  }

  return true;
}
