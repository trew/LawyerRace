#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <string>

std::string get_cwd();

std::string get_exe_dir();

bool file_exists(const std::string& name);

#endif
