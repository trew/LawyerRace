#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/Config.hpp>
#include <iostream>
#include <fstream>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

Config::Config()
{
  rockWidth[0] = 17.f;
  rockWidth[1] = 26.f;
  rockWidth[2] = 58.f;

  rockHeight[0] = 14.f;
  rockHeight[1] = 25.f;
  rockHeight[2] = 49.f;

  rockVelocity[0] = 250.f;
  rockVelocity[1] = 187.f;
  rockVelocity[2] = 125.f;

  playerRegion[0] = "player1";
  playerRegion[1] = "player2";
  playerRegion[2] = "player3";
  playerRegion[3] = "player4";

  rockRegion[0] = "stone1-17x14";
  rockRegion[1] = "stone2-26x25";
  rockRegion[2] = "stone3-58x49";
}

Config::~Config()
{
}

bool Config::loadConfigFile()
{
  LOG_DEBUG("---PARSING CONFIG---");
  const std::string& _file = this->configFile;

  lua_State* L = LawyerRace::LuaState;
  LOG_DEBUG("Reading \"%s\"", _file.c_str());
  if (luaL_loadfile(L, _file.c_str())) {
    LOG_ERROR("Couldn't read config file %s", _file);
    return false;
  }
  if (lua_pcall(L, 0, 0, 0))
  {
    LOG_ERROR("Error calling config file %s", _file);
  }

  using namespace luabridge;

  LuaRef config = getGlobal(L, "config");
  if (config.isTable())
  {
    if (config["max_enemies"].isNumber())
    {
      maxEnemyCount = config["max_enemies"].cast<int>();
    }
    if (config["enemies_before_rock"].isNumber())
    {
      enemyCountBeforeRocks = config["enemies_before_rock"].cast<int>();
    }
    if (config["max_rocks"].isNumber())
    {
      maxRockCount = config["max_rocks"].cast<int>();
    }

    LuaRef velocity = config["velocity"];
    if (velocity.isTable())
    {
      if (velocity["gamespeed"].isNumber())
      {
        gameSpeed = velocity["gamespeed"].cast<float>();
      }
      if (velocity["player"].isNumber())
      {
        playerVelocity = velocity["player"].cast<float>();
      }
      if (velocity["enemy"].isNumber())
      {
        enemyVelocity = velocity["enemy"].cast<float>();
      }

      LuaRef rocks = velocity["rocks"];
      if (rocks.isTable())
      {
        if (rocks["small"].isNumber())
        {
          rockVelocity[0] = rocks["small"].cast<float>();
        }
        if (rocks["medium"].isNumber())
        {
          rockVelocity[1] = rocks["medium"].cast<float>();
        }
        if (rocks["large"].isNumber())
        {
          rockVelocity[2] = rocks["large"].cast<float>();
        }
      }
    }

    LuaRef system = config["system"];
    if (system.isTable())
    {
      if (system["resolution_width"].isNumber() && system["resolution_height"].isNumber())
      {
        windowWidth = system["resolution_width"].cast<int>();
        windowHeight = system["resolution_height"].cast<int>();
      }
    }

    if (config["skip_menu"].isBool())
    {
      skipMenu = config["skip_menu"].cast<bool>();
    }
  }
  LOG_DEBUG("---PARSING CONFIG DONE!---");
  return true;
}

std::string Config::validateConfigFile(const std::string& _file)
{
  std::string file = _file;
  if (lwe::filesys::fileExists(path + file))
  {
    LOG_DEBUG("Using config: %s", file.c_str());
  }
  else if (lwe::filesys::fileExists(path + "cfg/" + file))
  {
    file = "cfg/" + file;
    LOG_DEBUG("Using config: %s", file.c_str());
  }
  else
  {
    LOG_ERROR("Error finding config: [%s]. Instead using [%s].", file.c_str(), configFile.c_str());
    return configFile;
  }

  return file;
}

std::string Config::validatePath(const std::string& _path)
{
  std::string path;
  if (lwe::filesys::fileExists(_path))
  {
    path = _path;
    LOG_DEBUG("Using path: %s", path.c_str());
  }
  else
  {
    path = lwe::filesys::cwd();
    LOG_ERROR("Loading Path [%s] failed. Using [%s].", _path.c_str(), path.c_str());
  }

  if (*path.rbegin() != '/')
  {
    path.append("/");
  }

  return path;
}

const std::string& Config::getPath() const
{
  return path;
}

void Config::setPath(const std::string& path)
{
  this->path = validatePath(path);
}

void Config::setConfigFile(const std::string& file)
{
  configFile = validateConfigFile(file);
}

std::string Config::getFile(const std::string& fileName)
{
  return path + fileName;
}

int Config::getWindowWidth() const
{
  return windowWidth;
}

int Config::getWindowHeight() const
{
  return windowHeight;
}

int Config::getGameWidth() const
{
  return gameWidth;
}

int Config::getGameHeight() const
{
  return gameHeight;
}

const std::string& Config::getWindowText() const
{
  return windowText;
}

int Config::getMaximumPlayerCount() const
{
  return maxPlayerCount;
}

int Config::getPlayerCount() const
{
  return playerCount;
}

void Config::setPlayerCount(const int count)
{
  playerCount = count;
}

float Config::getPlayerWidth() const
{
  return playerWidth;
}

float Config::getPlayerHeight() const
{
  return playerHeight;
}

float Config::getEnemyWidth() const
{
  return enemyWidth;
}

float Config::getEnemyHeight() const
{
  return enemyHeight;
}

float Config::getDollarWidth() const
{
  return dollarWidth;
}

float Config::getDollarHeight() const
{
  return dollarHeight;
}

float Config::getMaxRockWidth() const
{
  return maxRockWidth;
}

float Config::getMaxRockHeight() const
{
  return maxRockHeight;
}

float Config::getRockWidth(const int type) const
{
  return rockWidth[type];
}

float Config::getRockHeight(const int type) const
{
  return rockHeight[type];
}

bool Config::isPlayerStopEnabled() const
{
  return playerStopEnabled;
}

void Config::setPlayerStopEnabled(const bool enabled)
{
  playerStopEnabled = enabled;
}

bool Config::isOldDiagonalSpeedEnabled() const
{
  return oldDiagonalSpeed;
}

void Config::setOldDiagonalSpeedEnabled(const bool enabled)
{
  oldDiagonalSpeed = enabled;
}

int Config::getMaxEnemyCount() const
{
  return maxEnemyCount;
}

int Config::getEnemyCountBeforeRocks() const
{
  return enemyCountBeforeRocks;
}

int Config::getMaxRockCount() const
{
  return maxRockCount;
}

float Config::getGameSpeed() const
{
  return gameSpeed;
}

float Config::getPlayerVelocity() const
{
  return playerVelocity;
}

float Config::getEnemyVelocity() const
{
  return enemyVelocity;
}

float Config::getRockVelocity(const int type) const
{
  return rockVelocity[type];
}

PlayerControls* Config::getPlayerControls()
{
  return controls;
}

const PlayerControls& Config::getPlayerControls(int player) const
{
  return controls[player];
}

const std::string& Config::getControlsFile() const
{
  return controlsFile;
}

void Config::setControlsFile(const std::string& file)
{
  controlsFile = file;
}

bool Config::isLinearInterpolationEnabled() const
{
  return enableLinearInterpolation;
}

int Config::getMaxFrameSkip() const
{
  return maxFrameSkip;
}

int Config::getMaxFPS() const
{
  return maxFps;
}

bool Config::isSkipMenu() const
{
  return skipMenu;
}

const std::string& Config::getDollarRegion() const
{
  return dollarRegion;
}

const std::string& Config::getPlayerRegion(const int player) const
{
  return playerRegion[player];
}

const std::string& Config::getEnemyRegion() const
{
  return enemyRegion;
}

const std::string& Config::getRockRegion(int type) const
{
  return rockRegion[type];
}