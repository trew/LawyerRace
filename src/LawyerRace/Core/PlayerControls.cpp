#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/PlayerControls.hpp>
#include <LawyerRace/Core/Config.hpp>
#include <fstream>

#include <json/json.hpp>

std::map<std::string, SDL_Keycode> PlayerControls::__keymap;
std::map<std::string, SDL_GameControllerButton> PlayerControls::__gameControllerMap;
std::vector<PlayerControls> PlayerControls::__controls;

PlayerControls::PlayerControls()
{
}

PlayerControls::~PlayerControls()
{
}

void PlayerControls::initialize(const lwe::GameEngine* const engine)
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

  std::map<SDL_GameController*, Sint32> deviceToId;
  for (SDL_GameController* controller : engine->getControllers())
  {
    deviceToId[controller] = engine->getControllerDeviceID(controller);
  }
  __controls = loadControlsFromJsonFile(Config::getInstance().getControlsFile(), engine->getControllers(), deviceToId);
}

inline bool inrange(int x, int a, int b)
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
void PlayerControls::setControl(const int player,
                                const std::list<SDL_GameController*>& controllers,
                                const std::map<SDL_GameController*, Sint32>& controllerToDeviceId,
                                lwe::EventCondition& condition,
                                const std::string& keyname)
{
  std::string controllerKeyName = "";
  if (lwe::Utils::startsWith(keyname, "controller_"))
  {
    controllerKeyName = keyname.substr(11, keyname.size());
  }

  if (keyname.length() == 1)
  {
    /* Ascii? if so, ez convert to SDL_Keysym instantly.
     * see SDL_keysym.h for values mapped to SDL keys.
    */

    // TODO make this an "isValidAscii" method
    int comparekey = keyname[0];
    int customvalues[6] = {8,9,12,13,19,27};
    if (inrange(comparekey,91,127) || inrange(comparekey, 32, 64) || in(comparekey, customvalues))
    { //if valid ascii
      condition.addTrigger(std::make_shared<lwe::KeyboardTrigger>(comparekey, true));
    }
  }
  else if (__keymap.find(keyname) != __keymap.end())
  {
    condition.addTrigger(std::make_shared<lwe::KeyboardTrigger>(__keymap[keyname], true));
  }
  else if (__gameControllerMap.find(controllerKeyName) != __gameControllerMap.end())
  {
    auto it = controllers.begin();
    for (int i = 0; i < player; ++i)
    {
      it++;
    }

    auto controller = (*it);
    
    int device = controllerToDeviceId.at(controller);
    condition.addTrigger(std::make_shared<lwe::GameControllerButtonTrigger>(device, __gameControllerMap[controllerKeyName], true));
  }

  if (!condition.hasTriggers())
  {
    LOG_ERROR("%s was not set.", keyname.c_str());
  }
}

const PlayerControls& PlayerControls::getControls(const int player, const lwe::GameEngine* lwe)
{
  return PlayerControls::__controls.at(player);
}

void PlayerControls::setControl(const nlohmann::json& entry,
                                const std::string& key,
                                const int& player,
                                lwe::EventCondition& condition,
                                const std::list<SDL_GameController*>& controllers,
                                const std::map<SDL_GameController*, int>& controllerToDeviceId)
{
  if (entry[key].is_string())
  {
    setControl(player, controllers, controllerToDeviceId, condition, entry[key].get<std::string>());
  }
  else
  {
    if (entry[key].is_null())
    {
      LOG_ERROR("%s is not present", key.c_str());
    }
    else
    {
      LOG_ERROR("%s is not a string", key.c_str());
    }
  }
}

std::vector<PlayerControls> PlayerControls::loadControlsFromJsonFile(const std::string& _file,
                                                                     const std::list<SDL_GameController*>& controllers,
                                                                     const std::map<SDL_GameController*, int>& controllerToDeviceId)
{
	std::string file = Config::getInstance().getFile(_file);

	using json = nlohmann::json;

	std::vector<PlayerControls> controlsVector;
	json j;
	try
	{
		std::ifstream i(file);
		i >> j;
	}
	catch (const nlohmann::detail::parse_error& e)
	{
		LOG_ERROR("Error parsing controls json: %s", e.what());
		return controlsVector;
	}

  if (j.is_array())
  {
    for (const json& entry : j)
    {
      int player = controlsVector.size();
      if (entry.is_object())
      {
        PlayerControls controls;

        setControl(entry, "up", player, controls.up, controllers, controllerToDeviceId);
        setControl(entry, "left", player, controls.left, controllers, controllerToDeviceId);
        setControl(entry, "down", player, controls.down, controllers, controllerToDeviceId);
        setControl(entry, "right", player, controls.right, controllers, controllerToDeviceId);
        setControl(entry, "stop", player, controls.stop, controllers, controllerToDeviceId);

        controlsVector.push_back(controls);
      }
      else
      {
        LOG_ERROR("Entry in controls array must be a json object.");
      }
    }
  }
  else
  {
    LOG_ERROR("Controls configuration is not an array.");
  }

	return controlsVector;
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
