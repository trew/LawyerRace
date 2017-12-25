#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/Config.hpp>
#include <iostream>
#include <fstream>

#include <json/json.hpp>

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

  backgroundColor = {0, 0, 0, 255};
}

Config::~Config()
{
}

Uint8 getValueIfBetweenOrDefault(Uint8 value, Uint8 low, Uint8 high, Uint8 def)
{
  return (value >= low && value <= high) ? value : def;
}

bool Config::loadConfigFile()
{
	const std::string& configFileName = this->configFile;

	LOG_DEBUG("Parsing Config file %s", configFileName.c_str());

	std::ifstream i(configFileName.c_str());

	// load the json
	nlohmann::json config;
	try
	{
		i >> config;
	}
	catch (const nlohmann::detail::parse_error& e)
	{
		LOG_ERROR("Error parsing config file: %s", e.what());
		return false;
	}

	if (config["maxEnemy"].is_number())
	{
		maxEnemyCount = config["maxEnemy"].get<int>();
	}
	if (config["enemyCountBeforeRocks"].is_number())
	{
		enemyCountBeforeRocks = config["enemyCountBeforeRocks"].get<int>();
	}
	if (config["maxRocks"].is_number())
	{
		maxRockCount = config["maxRocks"].get<int>();
	}
	if (config["disableStop"].is_boolean())
	{
		playerStopEnabled = !config["disableStop"].get<bool>();
	}

	nlohmann::json velocity = config["velocity"];
	if (velocity.is_object())
	{
		if (velocity["gameSpeed"].is_number())
		{
			gameSpeed = velocity["gameSpeed"].get<float>();
		}
		if (velocity["player"].is_number())
		{
			playerVelocity = velocity["player"].get<float>();
		}
		if (velocity["enemy"].is_number())
		{
			enemyVelocity = velocity["enemy"].get<float>();
		}

		nlohmann::json rocks = velocity["rocks"];
		if (rocks.is_object())
		{
			if (rocks["small"].is_number())
			{
				rockVelocity[0] = rocks["small"].get<float>();
			}
			if (rocks["medium"].is_number())
			{
				rockVelocity[1] = rocks["medium"].get<float>();
			}
			if (rocks["large"].is_number())
			{
				rockVelocity[2] = rocks["large"].get<float>();
			}
		}
	}

	nlohmann::json bg = config["backgroundColor"];
	if (bg.is_array())
	{
		nlohmann::json r = bg[0];
		nlohmann::json g = bg[1];
		nlohmann::json b = bg[2];

		if (r.is_number())
		{
			backgroundColor.r = getValueIfBetweenOrDefault(r.get<int>(), 0, 255, backgroundColor.r);
		}

		if (g.is_number())
		{
			backgroundColor.g = getValueIfBetweenOrDefault(g.get<int>(), 0, 255, backgroundColor.g);
		}

		if (b.is_number())
		{
			backgroundColor.b = getValueIfBetweenOrDefault(b.get<int>(), 0, 255, backgroundColor.b);
		}
	}


	nlohmann::json system = config["system"];
	if (system.is_object())
	{
		nlohmann::json res = system["resolution"];
		if (res.is_object())
		{
			if (res["width"].is_number() && res["height"].is_number())
			{
				windowWidth = res["width"].get<int>();
				windowHeight = res["height"].get<int>();
			}
		}
	}

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

const SDL_Color& Config::getBackgroundColor() const
{
  return backgroundColor;
}

void Config::setBackgroundColor(const SDL_Color& color)
{
  backgroundColor = color;
}