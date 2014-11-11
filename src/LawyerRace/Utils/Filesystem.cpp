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

#include <memory>

Path::Path(std::string filePath) {
	path = filePath;
}

File::File(Path path, std::string fileName) {
	m_path = path;
	m_fileName = fileName;
}

namespace filesys
{

std::unique_ptr<File> getFile(std::string fileName) {
	Path path = cwd();
	return std::unique_ptr<File>(new File(path, fileName));
}

Path cwd()
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
        return Path(str);
    } else { // res == NULL
        return Path("");
    }
}

Path executionDirectory()
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

} // namespace filesys
