// #pragma once
//? #pragma once is not standard so i used a header guard
#ifndef _logger_h
#define _logger_h

#include "ansi.h"

namespace ansi = ansi_escape_codes;

class Logger
{
public:
    enum LState : char { DEBUG, PRODUCTION };
    enum LType : char { None, Info, Success, Warning, Error, Debug };
    
private:
    const char* types[6] = { "\u001b[0m", "\u001b[37;1m[Info]: \u001b[0m", "\u001b[32;1m[Success]: ", "\u001b[33;1m[Warning]: ", "\u001b[31m[Error]: ", "\u001b[36;1m[Debug]: " };

    std::ostream& mStream;
    LState mState;
    LType mType;
    bool mTyped, mPrefixed;

protected:
    Logger();

public:
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator = (const Logger&) = delete;
    Logger& operator = (Logger&&) = delete;

    ~Logger();

    static Logger& getInstance();

    Logger& setType(const LType type);
    Logger& operator << (const LType type);

    inline Logger& cursor(const ansi::Cursor action);
    inline Logger& cursor(const ansi::Cursor action, const int value);
    Logger& operator << (const ansi::Cursor action);

    inline Logger& moveCursor(const int row, const int column);

    inline Logger& clear(const ansi::Clear type);
    Logger& operator << (const ansi::Clear type);

    inline Logger& setMode(const ansi::Mode mode);
    Logger& operator << (const ansi::Mode mode);

    inline Logger& setColor(const ansi::Color color);
    Logger& operator << (const ansi::Color color);

    //* Handle std:: params
    //? Make it inline
    Logger& operator << (std::ostream& (*data)(std::ostream&));

    //* Handle generic stream data
    //? Make it inline
    template<typename T>         
    Logger& operator << (const T& data);

    #define LInfo(msg) Logger::getInstance().setType(Logger::Info) << msg << std::endl
    #define LSuccess(msg) Logger::getInstance().setType(Logger::Success) << msg << std::endl
    #define LWarning(msg) Logger::getInstance().setType(Logger::Warning) << msg << std::endl
    #define LError(msg) Logger::getInstance().setType(Logger::Error) << msg << std::endl
    #define LDebug(msg) Logger::getInstance().setType(Logger::Debug) << msg << std::endl
};

#endif
