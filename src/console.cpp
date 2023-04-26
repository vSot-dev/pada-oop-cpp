#include <iostream>

//* Includes for every os (Define KEYBOARD_HANDLE_NOT_SUPPORTED if os not supported)
#if defined(_WIN32)
    #include <Windows.h>
#elif defined(__unix__)
    #include <termios.h>
    #include <unistd.h>
// #elif defined(__APPLE__)
//TODO:  Support for MacOS
#else
    #define KEYBOARD_HANDLE_NOT_SUPPORTED
#endif

#include "logger.cpp"
#include "../include/console.h"

#if defined(_WIN32)
//* Console setup/handles for windows

Console::Console()
{
    out << Logger::Debug << "(Console) Constructor" << std::endl;

    DWORD outMode = 0;
        // inMode = 0;

    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    stdinHandle = GetStdHandle(STD_INPUT_HANDLE);

    if (stdoutHandle == INVALID_HANDLE_VALUE || stdinHandle == INVALID_HANDLE_VALUE)
        exit(GetLastError());
    
    if (!GetConsoleMode(stdoutHandle, &outMode))
        // || !GetConsoleMode(stdinHandle, &inMode))
        exit(GetLastError());

    outModeInit = outMode;
    // inModeInit = inMode;

    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    // inMode |= ENABLE_VIRTUAL_TERMINAL_INPUT;

    if(!SetConsoleMode(stdoutHandle, outMode))
        // || !SetConsoleMode(stdinHandle, inMode))
        exit(GetLastError());
}

Console::~Console()
{
    out << Logger::Debug << "(Console) Destructor" << std::endl;

    if(!SetConsoleMode(stdoutHandle, outModeInit))
        // || !SetConsoleMode(stdinHandle, inModeInit))
        exit(GetLastError());
}

#elif defined(__unix__)
//* Console setup/handles for unix

Console::Console()
{
    lout << Logger::Debug << "(Console) Constructor" << std::endl;

    tcgetattr(STDIN_FILENO, &origin_term);
    new_term = origin_term;

    new_term.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

Console::~Console()
{
    lout << Logger::Debug << "(Console) Destructor" << std::endl;

    tcsetattr(STDIN_FILENO, TCSANOW, &origin_term);
}

#endif

Console& Console::getInstance()
{
    static Console sInstance;
    return sInstance;
}

KEY_EVENT_RECORD Console::getKey() const
{
    INPUT_RECORD lpBuffer;
    DWORD nLength;

    //? Is there a better way other than infinite for
    //? Propably its not infinite loop
    for(;;)
    {
        ReadConsoleInput(stdinHandle, &lpBuffer, 1, &nLength);
        if(lpBuffer.EventType == KEY_EVENT)
        {
            KEY_EVENT_RECORD keyEvent = lpBuffer.Event.KeyEvent;

            if (keyEvent.bKeyDown)
            // && ! (keyEvent.wRepeatCount )
                return keyEvent;
        }
    }
}

int main()
{
    auto& console = Console::getInstance();

    console.out << console.getKey().wVirtualKeyCode;
    console.out << "test";

    LInfo("asdf");

    return 0;
}
