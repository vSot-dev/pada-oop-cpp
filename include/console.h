// #pragma once
//? #pragma once is not standard so i used a header guard
#ifndef _console_h
#define _console_h

class Console
{
private:
    #if defined(_WIN32)
        //* Console handles for windows
        HANDLE stdoutHandle, stdinHandle;
        DWORD outModeInit, inModeInit;
    #elif defined(__unix__)
        //* Console handles for unix
        struct termios origin_term;
        struct termios new_term;
    #endif

public:
    Logger& out = Logger::getInstance();

protected:
    Console();

public:
    Console(const Console&) = delete;
    Console(Console&&) = delete;
    Console& operator = (const Console&) = delete;
    Console& operator = (Console&&) = delete;

    ~Console();

    static Console& getInstance();

    KEY_EVENT_RECORD getKey() const;
};

#endif
