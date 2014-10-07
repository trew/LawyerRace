/*
    Lawyer Race - A game about escaping the law
    Copyright (C) 2012 Samuel Andersson

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <SDL.h>
#include "GameEngine.hpp"
#include "Gameconfig.hpp"
#include "Log.hpp"
#include "Filesystem.hpp"

#include <ctime>
#include <iostream>

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

    LOG_DEBUG << "---PARSING COMMAND LINE!---\n";
//    try {
//        po::options_description desc("Allowed options");
//        desc.add_options()
//            ("help,h", "produce help message")
//            ("players,n", po::value<int>()->default_value(1), "sets number of players")
//            ("path,p", po::value<std::string>(), "use this folder as base path")
//            ("settings-file,f", po::value<std::string>(), "use this config file")
//            ("keyset-file,k", po::value<std::string>(), "use keysets from this file")
//            ("disable-stop", "disallows players to stop")
//            ("old-diagonalspeed", "use the old diagonal speed. (instead of modifying by 0.7~)")
//            ;
//
//        po::variables_map vm;
//        po::store(po::parse_command_line(argc, argv, desc), vm);
//        po::notify(vm);
//
//        if (vm.count("help")) {
//            std::cout << desc << std::endl;
//            return false;
//        }
//
//        /* First load path and config file */
//        if (vm.count("path")) {
//            config::path = config::validatePath(vm["path"].as<std::string>());
//        } else {
            config::path = config::validatePath(filesys::get_cwd());
//        }

//        if (vm.count("settings-file")) {
//            config::config_file = config::validateConfigFile(vm["settings-file"].as<std::string>());
//        }
//        /* Then parse that file */
//        config::parseConfigFile(config::path + config::config_file);

//        if (vm.count("keyset-file")) {
//            if (filesys::file_exists(config::path + vm["keyset-file"].as<std::string>())) {
//                config::keyset_file = vm["keyset-file"].as<std::string>();
//            } else {
//                LOG_ERROR << "Error loading " << vm["keyset-file"].as<std::string>() << "\n";
//            }
//        }
//        LOG_DEBUG << "Using keysets from" << config::keyset_file << "\n";


        /* Continue and override any variables that were provided in command line; they are more important than the config file */
//        if (vm.count("disable-stop"))
//        {
//            config::PLAYER_STOP_ENABLED = false;
//            LOG_DEBUG << "CMDLINE: Disabling player stop\n";
//        }
//
//        if (vm.count("old-diagonalspeed")) {
//            config::OLD_DIAGONAL_SPEED = true;
//            LOG_DEBUG << "CMDLINE: Enforcing old diagonal speed...\n";
//        }
//
//        if (vm.count("players")) {
//            if (vm["players"].as<int>() < 5 && vm["players"].as<int>() > 0) {
//                config::NUM_OF_PLAYERS = vm["players"].as<int>();
//                LOG_DEBUG << "CMDLINE: Setting number of players to: " << config::NUM_OF_PLAYERS << "\n";
//            } else {
//                LOG_ERROR << "Wrong number of players\n";
//                config::NUM_OF_PLAYERS = 1;
//            }
//        }
//
//        LOG_DEBUG << "Loading keysets...\n";
        KeySet::LoadKeysetFromFile(config::KEYSET, config::keyset_file);

//    } catch (std::exception& e) {
//        std::cerr << "error: " << e.what() << std::endl;
//    } catch (...) {
//        std::cerr << "unknown exception" << std::endl;
//    }
//    LOG_DEBUG << "---COMMANDLINE PARSING DONE!---\n";
    return true;
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(NULL)));

	GameEngine engine;
	
	config::path = filesys::get_exe_dir();
    if(!parse_command_line(argc, argv))
        return 0;

    try
    {
        engine.Run();
    }
    catch (const char* c)
    {
        std::cerr << "Error: " << c << std::endl;
    }
    return 0;
}

