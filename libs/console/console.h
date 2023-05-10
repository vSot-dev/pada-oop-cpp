#ifndef _console_h
#define _console_h

#include <iostream>

//TODO: Add support for MacOS
// #elif defined(__APPLE__)

//? Includes for every supported os (Define CONSOLE_HANDLE_NOT_SUPPORTED and revert to fallbacks if not supported)
#if defined(_WIN32)
    #include <Windows.h>
#elif defined(__unix__)
    #include <termios.h>
    #include <unistd.h>
#else
    #define CONSOLE_HANDLE_NOT_SUPPORTED
#endif

namespace console
{

    struct KeyEvent
    {
        
    };
    
    class Console
    {
    private:
        std::ostream& m_Out;
    
    protected:
        Console(std::ostream& out = std::cout);

    public:
        Console(const Console&) = delete;
        Console(Console&&) = delete;
        Console& operator = (const Console&) = delete;
        Console& operator = (Console&&) = delete;

        ~Console();

        static Console& getInstance();

        KeyEvent getKey() const;

    //? OS based variables
    private:
        #if defined(_WIN32)
            HANDLE stdoutHandle, stdinHandle;
            DWORD outModeInit, inModeInit;
        #elif defined(__unix__)
            struct termios origin_term;
            struct termios new_term;
        #endif
    };

} // namespace console

#endif
