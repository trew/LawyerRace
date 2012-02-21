/*
*  
*
*/

#include <SDL.h>
#include <ctime>
#include "Game.h"
#include <iostream>
#include "config.h"
#include "Log.h"
#include <boost/program_options.hpp>
#include "Filesystem.hpp"

namespace po = boost::program_options;

bool parse_command_line(int argc, char* argv[]) {
/*
Allowed options:
  -h [ --help ]              produce help message
  -p [ --path ] arg          use this folder as base path
  -f [ --settings-file ] arg use this config file(using path)
  --disable-stop             disallows players to stop
  --players arg              sets number of players
*/
    try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("path,p", po::value<std::string>(), "use this folder as base path")
            ("settings-file,f", po::value<std::string>(), "use this config file")
            ("disable-stop", "disallows players to stop")
            ("players,n", po::value<int>()->default_value(1), "sets number of players");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("disable-stop"))
        {
            config::PLAYER_STOP_ENABLED = false;
            LOG_DEBUG("Disabling player stop ");
        }
        
        if (vm.count("players")) {
            if (vm["players"].as<int>() < 5 && vm["players"].as<int>() > 0) {
                config::NUM_OF_PLAYERS = vm["players"].as<int>();
            } else {
                LOG_ERROR("Wrong number of players");
                config::NUM_OF_PLAYERS = 1;
            }
        }
        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return false;
        }

        if (vm.count("settings-file")) {
            config::settings_file = vm["settings-file"].as<std::string>();
            std::cout << "Using \"" << vm["settings-file"].as<std::string>() << "\" as configuration file." << std::endl;
        }

        if (vm.count("path")) {
            config::path = config::validatePath(vm["path"].as<std::string>());
        } else {
            config::path = config::validatePath(get_exe_dir());
        }
        
    } catch (std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "unknown exception" << std::endl;
    }
    return true; 
}

int main(int argc, char* argv[]) {
	srand(static_cast<unsigned int>(time(NULL)));

    config::path = get_exe_dir();
    if(!parse_command_line(argc, argv))
        return 0;
	
    Game newGame;
    try 
    {
        newGame.Execute();
    } 
	catch (const char* c)
	{
		std::cerr << "Error: " << c << std::endl;
	}
	return 0;
}

