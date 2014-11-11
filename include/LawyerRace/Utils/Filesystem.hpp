#ifndef LWR_FILESYSTEM_HPP
#define LWR_FILESYSTEM_HPP

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
