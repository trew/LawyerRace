#ifndef LWR_FILESYSTEM_HPP
#define LWR_FILESYSTEM_HPP

#include <string>
#include <memory>

class Path {
public:
	Path() {}
	Path(std::string path);

	const std::string getPath() { return path; }
private:
	std::string path;
};


class File {
public:
	File(Path path, std::string fileName);
	~File() {}

	const Path& getPath() { return m_path; }
	const std::string getFileName() { return m_fileName; }
	const std::string getExtension() { return m_extension; }
private:
	Path m_path;
	std::string m_fileName;
	std::string m_extension;
};

namespace filesys 
{
/**
 *  Gets the current working directory
 *
 *  @return Full path to the current working directory, empty string if anything went wrong.
 */
Path cwd();


/**
 *  Get the execution directory, same as get_cwd() if not in windows.
 *
 *  @return Full path to the current execution directory
 */
Path executionDirectory();


std::unique_ptr<File> getFile(std::string fileName);

/**
 *  Checks if a file exists.
 *
 *  @param name Full path to a file
 *  @return True if the file is found, False otherwise
 */
bool fileExists(const std::string& name);

} // namespace filesys



#endif
