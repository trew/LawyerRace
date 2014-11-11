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
std::string cwd();


/**
 *  Get the execution directory, same as get_cwd() if not in windows.
 *
 *  @return Full path to the current execution directory
 */
std::string executionDirectory();


/**
 *  Checks if a file exists.
 *
 *  @param name Full path to a file
 *  @return True if the file is found, False otherwise
 */
bool fileExists(const std::string& name);

} // namespace filesys

#endif
