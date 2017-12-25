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
  -p [ --path ] arg          use this folder as base path
  -f [ --config-file ] arg   use this config file
  -c [ --controls-file ] arg use controls from this file
*/
  LOG_DEBUG("Parsing command line...");

  TCLAP::CmdLine cmd("Allowed options", ' ', "1.0");
  cmd.setExceptionHandling(false);

  TCLAP::ValueArg<std::string> path("p", "path", "use this folder as base path", false, "", "string", cmd);
  TCLAP::ValueArg<std::string> settingsFile("f", "config-file", "use this config file", false, "", "string", cmd);
  TCLAP::ValueArg<std::string> controlsFile("c", "controls-file", "use controls from this file", false, "", "string", cmd);

  Config& config = Config::getInstance();

  try
  {
    cmd.parse(argc, argv);
  }
  catch (TCLAP::ExitException& )
  {
    // happens when arguments like --help or --version is provided
    return false;
  }
  catch (TCLAP::ArgException& e)
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

  if (!config.loadConfigFile())
  {
    return false;
  }

  if (controlsFile.isSet())
  {
    const std::string& file = controlsFile.getValue();
    if (lwe::filesys::fileExists(config.getFile(file)))
    {
      config.setControlsFile(file);
    }
    else if (lwe::filesys::fileExists(config.getFile("cfg/" + file)))
    {
      config.setControlsFile("cfg/" + file);
    }
    else
    {
      LOG_ERROR("Error loading %s", file.c_str());
    }
  }

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
    return -1;
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

  LOG_DEBUG("Using controls from %s", config.getControlsFile().c_str());
  PlayerControls::initialize(&engine);

  try
  {
    engine.run();
  }
  catch (const char* c)
  {
    LOG_ERROR("Error: %s", c);
    return -1;
  }
  catch (std::exception& e)
  {
    LOG_ERROR("Error: %s", e.what());
    return -1;
  }

  return 0;
}

