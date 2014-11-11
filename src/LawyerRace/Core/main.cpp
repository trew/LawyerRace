#include <SDL.h>
#include "LawyerRace/Core/GameEngine.hpp"
#include "LawyerRace/Core/Gameconfig.hpp"
#include "LawyerRace/Utils/Log.hpp"
#include "LawyerRace/Utils/Filesystem.hpp"

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
	using namespace TCLAP;
    LOG_DEBUG << "---PARSING COMMAND LINE!---\n";

	CmdLine cmd("Allowed options", ' ', "1.0");
	cmd.setExceptionHandling(false);

	ValueArg<int> players("n", "players", "sets number of players", false, 1, "integer", cmd);
	ValueArg<std::string> path("p", "path", "use this folder as base path", false, "", "string", cmd);
	ValueArg<std::string> settingsFile("f", "settings-file", "use this config file", false, "", "string", cmd);
	ValueArg<std::string> keysetFile("k", "keyset-file", "use keysets from this file", false, "", "string", cmd);
	SwitchArg disableStop("", "disable-stop", "disallows players to stop", cmd);
	SwitchArg oldDiagonalspeed("", "old-diagonalspeed", "use the old diagonal speed. (instead of modifying by 0.7~)", cmd);
		
	try {
		cmd.parse(argc, argv);
	} catch (ExitException) {
		// happens when arguments like --help or --version is provided
		return false;
	} catch (ArgException &e) {
		std::cerr << "error: " << e.error() << " for argument " << e.argId() << std::endl;
		return false;
	}

	/* First load path and config file */
	if (path.isSet()) {
		config::path = config::validatePath(path.getValue());
	} else {
		config::path = config::validatePath(filesys::cwd());
	}

	if (settingsFile.isSet()) {
		config::config_file = config::validateConfigFile(settingsFile.getValue());
	}
	config::parseConfigFile(config::path + config::config_file);

	if (keysetFile.isSet()) {
		if (filesys::fileExists(config::path + keysetFile.getValue())) {
			config::keyset_file = keysetFile.getValue();
		} else if (filesys::fileExists(config::path + "cfg/" + keysetFile.getValue())) {
			config::keyset_file = "cfg/" + keysetFile.getValue();
		} else {
		    LOG_ERROR << "Error loading " << keysetFile.getValue() << "\n";
		}
	}
    LOG_DEBUG << "Using keysets from " << config::keyset_file << "\n";
	LOG_DEBUG << "Loading keysets...\n";
	KeySet::LoadKeysetFromFile(config::KEYSET, config::keyset_file);


    /* Continue and override any variables that were provided in command line; they are more important than the config file */
	if (disableStop.getValue()) {
		config::PLAYER_STOP_ENABLED = false;
		LOG_DEBUG << "CMDLINE: Disabling player stop\n";
	}

	if (oldDiagonalspeed.getValue()) {
        config::OLD_DIAGONAL_SPEED = true;
		LOG_DEBUG << "CMDLINE: Enforcing old diagonal speed...\n";
	}

	if (players.isSet()) {
		int playerCount = players.getValue();
		if (playerCount < 5 && playerCount > 0) {
			config::NUM_OF_PLAYERS = playerCount;
            LOG_DEBUG << "CMDLINE: Setting number of players to: " << config::NUM_OF_PLAYERS << "\n";
        } else {
            LOG_ERROR << "Wrong number of players\n";
            config::NUM_OF_PLAYERS = 1;
        }
	}

	LOG_DEBUG << "---COMMANDLINE PARSING DONE!---\n";
    return true;
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(NULL)));

	GameEngine engine;
	
	if (!parse_command_line(argc, argv)) {
#ifdef _WINDOWS
		std::cin.ignore(); // wait for keypress
#endif
        return 0;
	}

    try
    {
        engine.run();
    }
    catch (const char* c)
    {
        std::cerr << "Error: " << c << std::endl;
    }
    return 0;
}

