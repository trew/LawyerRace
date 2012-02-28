/*
    Lawyer Race - A game about escaping the law
    Copyright (C) 2012 Samuel Andersson

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "Log.hpp"
#include <ctime>

namespace lg {

Logger Logger::log_debug("DEBUG");
Logger Logger::log_error("ERROR");

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
#pragma warning (disable : 4996) //disable warning for localtime()
    tm* lt = localtime(&t);
    if (lt) {
        strftime(buf, 100, format.c_str(), lt);
    }
    return buf;
}

Logger::Logger(std::string name): m_name(name) 
{
}

void Logger::set_ostream(std::ostream* os)
{
    output_stream = os;
}

std::ostream& Logger::operator()()
{
    std::ostream& stream = output();
    stream << m_name << " - " << get_timestamp(time(NULL)) << ": ";
    return stream;
}

Logger::~Logger()
{
}

} //namespace lg
