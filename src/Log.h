#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <iostream>

namespace lg
{

std::string get_timestamp(const time_t& t, const std::string& format="%Y-%m-%d %H:%M:%S");
class Logger {
public:
    static Logger log_debug;

    std::ostream& operator()(std::string msg);
    void set_ostream(std::ostream* os);
private:
    Logger();
    ~Logger();
};

} //namespace lg

#define LOG_DEBUG(a) lg::Logger::log_debug(a)

#endif
