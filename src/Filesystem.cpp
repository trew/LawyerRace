#include "Filesystem.hpp"

#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#include <algorithm>
#else /* !_WIN32 */
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#endif /* !_WIN32 */

std::string get_cwd()
{
    char buf[1024];
    const char* const res = _getcwd(buf,sizeof(buf));
    if(res != NULL) {
        std::string str(res);

#ifdef _WIN32
        std::replace(str.begin(),str.end(),'\\','/');
#endif

        return str;
    } else {
        return "";
    }
}

std::string get_exe_dir()
{
#ifndef _WIN32
    char buf[1024];
    size_t path_size = readlink("/proc/self/exe", buf, 1024);
    if(path_size == static_cast<size_t>(-1))
        return std::string();
    buf[path_size] = 0;
    return std::string(dirname(buf));
#else
    return get_cwd();
#endif
}

bool file_exists(const std::string& name)
{
#ifdef _WIN32
       struct stat st;
       return (::stat(name.c_str(), &st) == 0);
#else
    struct stat st;
    return (::stat(name.c_str(), &st) != -1);
#endif
}
