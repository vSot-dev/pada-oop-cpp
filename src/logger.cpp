#include <iostream>

#include "ansi.cpp"
#include "../include/logger.h"

Logger::Logger()
    : mStream(std::cout),
    mState(Logger::DEBUG),
    mTyped(false)
{
    *this << Logger::Debug << "(Logger) Constructor" << std::endl;
}

Logger::~Logger()
{
    *this << Logger::Debug << "(Logger) Destructor" << std::endl;
}

Logger& Logger::getInstance()
{
    static Logger sInstance;
    return sInstance;
}

Logger& Logger::setType(const LType type)
{
    mTyped = true;
    mType = type;
    mPrefixed = false;
    return *this;
}

Logger& Logger::operator << (const LType type)
{
    return setType(type);
}

inline Logger& Logger::cursor(const ansi::Cursor action)
{
    ansi::moveCursor(action);
    return *this;
}

inline Logger& Logger::cursor(const ansi::Cursor action, const int value)
{
    ansi::moveCursor(action, value);
    return *this;
}

Logger& Logger::operator << (const ansi::Cursor action)
{
    return cursor(action);
}

inline Logger& Logger::moveCursor(const int row, const int column)
{
    ansi::moveCursor(row, column);
    return *this;
}

inline Logger& Logger::clear(const ansi::Clear type)
{
    ansi::clear(type);
    return *this;
}

Logger& Logger::operator << (const ansi::Clear type)
{
    return clear(type);
}

inline Logger& Logger::setMode(const ansi::Mode mode)
{
    ansi::setMode(mode);
    return *this;
}

Logger& Logger::operator << (const ansi::Mode mode)
{
    return setMode(mode);
}

inline Logger& Logger::setColor(const ansi::Color color)
{
    ansi::setColor(color);
    return *this;
}

Logger& Logger::operator << (const ansi::Color color)
{
    return setColor(color);
}

//* Handle std:: params
//? Make it inline
Logger& Logger::operator << (std::ostream& (*data)(std::ostream&))
{
    if (mTyped)
    {
        mType = Logger::None;
        mTyped = false;
        mPrefixed = false;
    }

    setMode(ansi::RESET);
    mStream << data;
        
    return *this;
}

//* Handle generic stream data
//? Make it inline
template<typename T>           
Logger& Logger::operator << (const T& data)
{
    if (mState == Logger::PRODUCTION && mType > Logger::Warning)
    {
        return *this;
    }

    //TODO: Check for (\n std::flush) instead of std::endl
    if (mTyped && !mPrefixed)
    {
        mStream << types[mType] << data;
        mPrefixed = true;
    }
    else
        mStream << data;
    
    return *this;
}
