#include "Log.h"
#include <ctime>


namespace lg {

Logger Logger::log_debug;
Logger Logger::log_error;

static std::ostream* output_stream = NULL;

static std::ostream& output()
{
    if (output_stream) {
        return *output_stream;
    }
    return std::cout;
}

std::string get_timestamp(const time_t& t, const std::string& format) {
    char buf[100] = {0};
    tm* lt = localtime(&t);
    if (lt) {
        strftime(buf, 100, format.c_str(), lt);
    }
    return buf;
}

Logger::Logger() 
{
}

void Logger::set_ostream(std::ostream* os)
{
    output_stream = os;
}

std::ostream& Logger::operator()(std::string msg)
{
    std::ostream& stream = output();
    stream << get_timestamp(time(NULL)) << ": " << msg << std::endl;
    return stream;
}

Logger::~Logger()
{
}

} //namespace lg
