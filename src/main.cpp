/*
*  
*
*/

#include <SDL.h>
#include <ctime>
#include "Game.h"
#include <iostream>
#include <fstream>
#include "config.h"
#include "Log.h"
#include <boost/program_options.hpp>
#include "Filesystem.hpp"

namespace po = boost::program_options;

bool parse_config_file(std::string _file) {
	try {
        po::options_description desc("Allowed options");
		desc.add_options()
			("name",                     po::value<std::string>()->default_value("noname"), "")
			("max_enemies",              po::value<int>()->        default_value(4), "")
			("enemies_before_rock",      po::value<int>()->        default_value(4), "")
			("max_rocks",                po::value<int>()->        default_value(10), "")
			("velocity.gamespeed",       po::value<float>()->      default_value(1.0f), "")
			("velocity.player",          po::value<float>()->      default_value(1.0f), "")
			("velocity.enemy",           po::value<float>()->      default_value(0.43f), "")
			("velocity.rocks.small",     po::value<float>()->      default_value(0.9f), "")
			("velocity.rocks.medium",    po::value<float>()->      default_value(0.7f), "")
			("velocity.rocks.large",     po::value<float>()->      default_value(0.4f), "")
			("system.resolution_width",  po::value<int>()->        default_value(1024), "")
			("system.resolution_height", po::value<int>()->        default_value(768), "");
		po::variables_map vm;
		std::ifstream is(_file.c_str());
		po::store(po::parse_config_file(is, desc), vm);
        po::notify(vm);

		config::MAX_ENEMIES         = vm["max_enemies"].as<int>();
		config::ENEMIES_BEFORE_ROCK = vm["enemies_before_rock"].as<int>();
		config::MAX_ROCKS           = vm["max_rocks"].as<int>();
		config::GAME_SPEED		    = vm["velocity.gamespeed"].as<float>();
		config::P_VELOCITY			= vm["velocity.player"].as<float>();
		config::E_VELOCITY			= vm["velocity.enemy"].as<float>();
		config::R_VELOCITY[0]		= vm["velocity.rocks.small"].as<float>();
		config::R_VELOCITY[1]		= vm["velocity.rocks.medium"].as<float>();
		config::R_VELOCITY[2]		= vm["velocity.rocks.large"].as<float>();
		config::W_WIDTH				= vm["system.resolution_width"].as<int>();
		config::W_HEIGHT			= vm["system.resolution_height"].as<int>();

	} catch (boost::program_options::error &e) {
        std::cerr << "error parsing config file: \"" << _file << "\". Error: " << e.what() << std::endl;
		return false;
    } catch (...) {
        std::cerr << "unknown exception" << std::endl;
		return false;
    }
	return true;
}

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
			("disable-stop",po::value<bool>()->default_value(false), "disallows players to stop")
            ("players,n", po::value<int>()->default_value(1), "sets number of players");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

        if (vm.count("path")) {
            config::path = config::validatePath(vm["path"].as<std::string>());
        } else {
            config::path = config::validatePath(get_exe_dir());
        }

		if (vm.count("settings-file")) {
            config::config_file = config::validateConfigFile(vm["settings-file"].as<std::string>());
        } 
		
		parse_config_file(config::path + config::config_file);
		
        if (vm.count("disable-stop"))
        {
			if ( vm["disable-stop"].as<bool>()) {
				config::PLAYER_STOP_ENABLED = false;
				LOG_DEBUG("Disabling player stop ");
			}
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
	catch (boost::program_options::error &e)
	{
		std::cerr << "Program option error: " << e.what() << std::endl;
	}
	catch (const char* c)
	{
		std::cerr << "Error: " << c << std::endl;
	}
	return 0;
}

