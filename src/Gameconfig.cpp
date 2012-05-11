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


#include "Gameconfig.hpp"
#include "KeySet.hpp"
#include "Filesystem.hpp"
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include "Log.hpp"

namespace po = boost::program_options;

namespace config
{

    bool parseConfigFile(std::string _file) {
        LOG_DEBUG << "---PARSING CONFIG---\n";
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
            config::GAME_SPEED          = vm["velocity.gamespeed"].as<float>();
            config::P_VELOCITY          = vm["velocity.player"].as<float>();
            config::E_VELOCITY          = vm["velocity.enemy"].as<float>();
            config::R_VELOCITY[0]       = vm["velocity.rocks.small"].as<float>();
            config::R_VELOCITY[1]       = vm["velocity.rocks.medium"].as<float>();
            config::R_VELOCITY[2]       = vm["velocity.rocks.large"].as<float>();
            config::W_WIDTH             = vm["system.resolution_width"].as<int>();
            config::W_HEIGHT            = vm["system.resolution_height"].as<int>();

        } catch (boost::program_options::error &e) {
            std::cerr << "error parsing config file: \"" << _file << "\". Error: " << e.what() << std::endl;
            return false;
        } catch (...) {
            std::cerr << "unknown exception" << std::endl;
            return false;
        }
        LOG_DEBUG << "---PARSING CONFIG DONE!---\n";
        return true;
    }

    std::string validateConfigFile(std::string _file)
    {
        if (filesys::file_exists(config::path + _file))
        {
            LOG_DEBUG << "Using config: " << _file << "\n";
        } else {
            LOG_ERROR << "Error finding config: \"" << _file << "\". Instead using \"" << config::config_file << "\".\n";
            return config::config_file;
        }
        return _file;
    }

    std::string validatePath(std::string _path) {
        std::string path;
        if (filesys::file_exists(_path))
        {
            path = _path;
            LOG_DEBUG << "Using path: " << path << "\n";
        } else {
            path = filesys::get_cwd();
            LOG_ERROR << "Loading Path. \"" << _path << "\". Using \"" << path << "\".\n";
        }
        if (*path.rbegin() != '/')
            path.append("/");
        return path;
    }

    std::string path = ""; // reloaded during command line parsing
    std::string config_file = "cfg/ez"; //standard
    std::string keyset_file = "cfg/keysets"; //standard

    const std::string WINDOW_TEXT = "Lawyer Race";
    int W_WIDTH = 1024; ///<Window Width
    int W_HEIGHT = 768; ///<Window Height

    const int W_BPP = 32;       ///<Window Depth

    const int MAXNUM_OF_PLAYERS = 4; ///< Maximum amount of players that the game supports
    int NUM_OF_PLAYERS = 0;

    const int P_WIDTH = 30;     ///<Size of Player sprite width
    const int P_HEIGHT = 30;    ///<Size of Player sprite height
    const std::string P_SRC[4] = {"img/player1x30.png", "img/player2x30.png",
                                    "img/player3x30.png", "img/player4x30.png" };

    const int E_WIDTH = 30;     ///<Size of Enemy sprite width
    const int E_HEIGHT = 30;    ///<Size of Enemy sprite height
    const std::string E_SRC = "img/enemyx30.png";

    const int D_WIDTH = 30;     ///<Size of Dollar sprite width
    const int D_HEIGHT = 15;    ///<Size of Dollar sprite height
    const std::string D_SRC = "img/dollar.png";

    const int MAX_R_WIDTH = 58;
    const int MAX_R_HEIGHT = 49;

    const int R_WIDTH[3] = {17, 26, 58};
    const int R_HEIGHT[3] = {14, 25, 49};
    const std::string R_SRC[3] = {"img/stone1-17x14.png", "img/stone2-26x25.png", "img/stone3-58x49.png"};

    bool PLAYER_STOP_ENABLED = true;
    bool OLD_DIAGONAL_SPEED = false; //see enemy movement phase in Enemy.cpp
    int MAX_ENEMIES = 5;
    int ENEMIES_BEFORE_ROCK = 3;
    int MAX_ROCKS = 10;

    /**
    * SPEED_FACTOR is used in FPS.cpp to control speed of the game.
    * Based on width of screen, because I think it should take the same amount of time to travel from side to side regardless of screensize.
    * Tweaks also allows the entities default speed to be 1.0.
    */
    float SPEED_FACTOR = (static_cast<float>(W_WIDTH) / 4.0f) * 1.0f;
    float GAME_SPEED = 1.0f;        ///< Gamespeed, configurable in config file
    float P_VELOCITY = 1.0f;        ///< Player velocity
    float E_VELOCITY = 0.4f;        ///< Enemy velocity

    float R_VELOCITY[3] = {1.0f, 0.75f, 0.5f}; //Rock velocities

    KeySet KEYSET[4];

} //namespace config
