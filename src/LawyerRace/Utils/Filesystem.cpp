#include "LawyerRace/Utils/Filesystem.hpp"

#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#include <algorithm>
#else /* !_WIN32 */
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#endif /* !_WIN32 */

namespace filesys
{

std::string cwd()
{
    char buf[1024];
#ifdef _WIN32
    const char* const res = _getcwd(buf,sizeof(buf));
#else
    const char* const res = getcwd(buf,sizeof(buf));
#endif
    if(res != NULL) {
        std::string str(res);
#ifdef _WIN32
        std::replace(str.begin(),str.end(),'\\','/');
#endif
        return str;
    } else { // res == NULL
        return "";
    }
}

std::string executionDirectory()
{
#ifndef _WIN32
    char buf[1024];
    size_t path_size = readlink("/proc/self/exe", buf, 1024);
    if(path_size == static_cast<size_t>(-1))
        return std::string();
    buf[path_size] = 0;
    return std::string(dirname(buf));
#else
    return cwd();
#endif
}

bool fileExists(const std::string& name)
{
#ifdef _WIN32
        struct stat st;
        return (::stat(name.c_str(), &st) == 0);
#else
    struct stat st;
    return (::stat(name.c_str(), &st) != -1);
#endif
}

}
