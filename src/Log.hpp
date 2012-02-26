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
    static Logger log_error;

    std::ostream& operator()();
    void set_ostream(std::ostream* os);
private:
    Logger():m_name("-unknown-") {} //this shouldn't happen
    Logger(std::string name);
    ~Logger();
    std::string m_name;
};

} //namespace lg

#define LOG_DEBUG lg::Logger::log_debug()
#define LOG_ERROR lg::Logger::log_error()

#endif
