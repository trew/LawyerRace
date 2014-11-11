#ifndef LWR_LOG_HPP
#define LWR_LOG_HPP

#include <string>
#include <iostream>

namespace lg
{

std::string get_timestamp(const time_t& t, const std::string& format="%Y-%m-%d %H:%M:%S");


class Logger {
public:
    static Logger log_debug;
    static Logger log_error;

    /**
     *  Operator()
     *
     *  @return The outstream of the current Logger. If no outstream is set, std::cout is returned.
     */
    std::ostream& operator()();


    /**
     *  Sets the outstream.
     *
     *  @param os The outstream.
     */
    void set_ostream(std::ostream* os);

private:
    Logger():m_name("-unknown-") {} //this cannot be called.

    /**
     *  Constructor
     *
     *  @param name Name of the logger
     */
    Logger(std::string name);


    /**
     *  Destructor
     */
    ~Logger();

    std::string m_name;  ///< Name of the logger
};

} //namespace lg

#define LOG_DEBUG lg::Logger::log_debug()
#define LOG_ERROR lg::Logger::log_error()

#endif
