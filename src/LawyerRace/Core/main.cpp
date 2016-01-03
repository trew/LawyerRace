#include <LawyerEngine/LawyerEngine.hpp>

#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/Config.hpp>

#include <ctime>
#include <iostream>

#ifdef _WIN32
#define TCLAP_NAMESTARTSTRING "/"
#define TCLAP_FLAGSTARTSTRING "/"
#endif

#include <tclap\CmdLine.h>

bool parseCommandLine(int argc, char* argv[])
{
/*
  Allowed options:
  -h [ --help ]              produce help message
  -n [ --players ] arg       sets number of players
  -p [ --path ] arg          use this folder as base path
  -f [ --settings-file ] arg use this config file(using path)
  --disable-stop             disallows players to stop
  --old-diagonalspeed        use the old diagonal speed. (instead of modifying by 0.7~)
*/
  LOG_DEBUG("---PARSING COMMAND LINE!---");

  TCLAP::CmdLine cmd("Allowed options", ' ', "1.0");
  cmd.setExceptionHandling(false);

  TCLAP::ValueArg<int> players("n", "players", "sets number of players", false, 1, "integer", cmd);
  TCLAP::ValueArg<std::string> path("p", "path", "use this folder as base path", false, "", "string", cmd);
  TCLAP::ValueArg<std::string> settingsFile("f", "settings-file", "use this config file", false, "", "string", cmd);
  TCLAP::ValueArg<std::string> keysetFile("k", "keyset-file", "use keysets from this file", false, "", "string", cmd);
  TCLAP::SwitchArg disableStop("", "disable-stop", "disallows players to stop", cmd);
  TCLAP::SwitchArg oldDiagonalspeed("", "old-diagonalspeed", "use the old diagonal speed. (instead of modifying by 0.7~)", cmd);

  Config& config = Config::getInstance();

  try
  {
    cmd.parse(argc, argv);
  }
  catch (TCLAP::ExitException)
  {
    // happens when arguments like --help or --version is provided
    return false;
  }
  catch (TCLAP::ArgException &e)
  {
    LOG_ERROR("Error: %s for argument %s", e.error().c_str(), e.argId().c_str());
    return false;
  }

  /* First load path and config file */
  if (path.isSet())
  {
    config.setPath(path.getValue());
  }
  else
  {
    config.setPath(std::string(lwe::filesys::cwd()));
  }

  if (settingsFile.isSet())
  {
    config.setConfigFile(settingsFile.getValue());
  }

  config.loadConfigFile();

  if (keysetFile.isSet())
  {
    if (lwe::filesys::fileExists(config.getFile(keysetFile.getValue())))
    {
      config.setControlsFile(keysetFile.getValue());
    }
    else if (lwe::filesys::fileExists(config.getFile("cfg/" + keysetFile.getValue())))
    {
      config.setControlsFile("cfg/" + keysetFile.getValue());
    }
    else
    {
      LOG_ERROR("Error loading %s", keysetFile.getValue().c_str());
    }
  }
  LOG_DEBUG("Using controls from %s", config.getControlsFile().c_str());
  LOG_DEBUG("Loading control configuration...");
  PlayerControls::loadControlsFromFile(config.getPlayerControls(), config.getControlsFile());

  /* Continue and override any variables that were provided in command line; they are more important than the config file */
  if (disableStop.getValue())
  {
    config.setPlayerStopEnabled(false);
    LOG_DEBUG("CMDLINE: Disabling player stop");
  }

  if (oldDiagonalspeed.getValue())
  {
    config.setOldDiagonalSpeedEnabled(true);
    LOG_DEBUG("CMDLINE: Enforcing old diagonal speed...");
  }

  if (players.isSet())
  {
    int playerCount = players.getValue();
    if (playerCount < 5 && playerCount > 0)
    {
      config.setPlayerCount(playerCount);
      LOG_DEBUG("CMDLINE: Setting number of players to: ", config.getPlayerCount());
    }
    else
    {
      LOG_ERROR("Wrong number of players");
      config.setPlayerCount(1);
    }
  }

  LOG_DEBUG("---COMMANDLINE PARSING DONE!---");
  return true;
}

int main(int argc, char* argv[])
{
  srand((unsigned int)(time(NULL)));

#ifdef DEBUG
  lwe::Log::getLogger().setLoggingLevel(lwe::LEVEL_DEBUG);
#else
  lwe::Log::getLogger().setLoggingLevel(lwe::LEVEL_INFO);
#endif

  // This class needs to be created before before parsing commandline so lua is initialized.
  LawyerRace* lr = new LawyerRace();

  if (!parseCommandLine(argc, argv))
  {
    return 0;
  }

  Config& config = Config::getInstance();

  lwe::GameSettings settings;
  settings.WindowWidth = config.getWindowWidth();
  settings.WindowHeight = config.getWindowHeight();
  settings.LogicalWidth = config.getGameWidth();
  settings.LogicalHeight = config.getGameHeight();
  settings.WindowTitle = config.getWindowText();
  settings.MaxFPS = config.getMaxFPS();
  settings.MaxFrameSkip = config.getMaxFrameSkip();
  settings.EntityInterpolationEnabled = config.isLinearInterpolationEnabled();

  lwe::GameEngine engine(settings, lr);

  try
  {
    engine.run();
  }
  catch (const char* c)
  {
    LOG_ERROR("Error: %s", c);
    return -1;
  }

  return 0;
}

