#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/Gameconfig.hpp>

#include <ctime>
#include <iostream>

#ifdef _WINDOWS
#define TCLAP_NAMESTARTSTRING "/"
#define TCLAP_FLAGSTARTSTRING "/"
#endif
#include <tclap\CmdLine.h>

bool parse_command_line(int argc, char* argv[]) {
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
		
	try {
		cmd.parse(argc, argv);
	} catch (TCLAP::ExitException) {
		// happens when arguments like --help or --version is provided
		return false;
	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for argument " << e.argId() << std::endl;
		return false;
	}

	/* First load path and config file */
	if (path.isSet()) {
		config::path = config::validatePath(path.getValue());
	} else {
		config::path = config::validatePath(lwe::filesys::cwd());
	}

	if (settingsFile.isSet()) {
		config::config_file = config::validateConfigFile(settingsFile.getValue());
	}
	config::parseConfigFile(config::path + config::config_file);

	if (keysetFile.isSet()) {
		if (lwe::filesys::fileExists(config::path + keysetFile.getValue())) {
			config::keyset_file = keysetFile.getValue();
		} else if (lwe::filesys::fileExists(config::path + "cfg/" + keysetFile.getValue())) {
			config::keyset_file = "cfg/" + keysetFile.getValue();
		} else {
		    LOG_ERROR("Error loading %s", keysetFile.getValue().c_str());
		}
	}
    LOG_DEBUG("Using keysets from %s", config::keyset_file.c_str());
	LOG_DEBUG("Loading keysets...");
	KeySet::LoadKeysetFromFile(config::KEYSET, config::keyset_file);


    /* Continue and override any variables that were provided in command line; they are more important than the config file */
	if (disableStop.getValue()) {
		config::PLAYER_STOP_ENABLED = false;
		LOG_DEBUG("CMDLINE: Disabling player stop");
	}

	if (oldDiagonalspeed.getValue()) {
        config::OLD_DIAGONAL_SPEED = true;
		LOG_DEBUG("CMDLINE: Enforcing old diagonal speed...");
	}

	if (players.isSet()) {
		int playerCount = players.getValue();
		if (playerCount < 5 && playerCount > 0) {
			config::NUM_OF_PLAYERS = playerCount;
            LOG_DEBUG("CMDLINE: Setting number of players to: ", config::NUM_OF_PLAYERS);
        } else {
            LOG_ERROR("Wrong number of players");
            config::NUM_OF_PLAYERS = 1;
        }
	}

	LOG_DEBUG("---COMMANDLINE PARSING DONE!---");
    return true;
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(NULL)));

  lwe::GameSettings settings;
  settings.WindowWidth = config::W_WIDTH;
  settings.WindowHeight = config::W_HEIGHT;
  settings.WindowTitle = config::WINDOW_TEXT;
  settings.MaxFPS = config::MAX_FPS;
  settings.MaxFrameSkip = config::MAX_FRAMESKIP;
  settings.EntityInterpolationEnabled = config::ENABLE_LERP;

	lwe::GameEngine engine(settings);

  LawyerRace* lw = new LawyerRace();

	if (!parse_command_line(argc, argv))
  {
#ifdef _WINDOWS
		std::cin.ignore(); // wait for keypress
#endif
    return 0;
	}

  try
  {
    engine.run(lw);
  }
  catch (const char* c)
  {
      std::cerr << "Error: " << c << std::endl;
  }

  return 0;
}

