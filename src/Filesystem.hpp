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

/* Basic file system handling */

#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <string>

namespace filesys 
{
    /**
     *  Gets the current working directory
     *
     *  @return Full path to the current working directory, empty string if anything went wrong.
     */
    std::string get_cwd();


    /**
     *  Get the execution directory, same as get_cwd() if not in windows.
     *
     *  @return Full path to the current execution directory
     */
    std::string get_exe_dir();


    /**
     *  Checks if a file exists.
     *
     *  @param name Full path to a file
     *  @return True if the file is found, False otherwise
     */
    bool file_exists(const std::string& name);
}

#endif
