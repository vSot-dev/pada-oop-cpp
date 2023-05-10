#ifndef _logger_h
#define _logger_h

#include <sstream>
#include <chrono>
#include <mutex>

namespace logger
{
    enum class LState : char { DEBUG, PRODUCTION };
    enum class LType : char { NONE, TRACE, INFO, DEBUG, WARNING, ERROR };

    //!TODO: Fix mutable etc...
    struct Timer
    {
        Timer();
        ~Timer();

        float getSec() const;
        float getMs() const;

    private:
        std::chrono::high_resolution_clock::time_point m_Start, m_End;
        std::chrono::duration<float> m_Duration;
    };

    struct LogMessage : public std::stringstream
    {
        LogMessage(LType type);
        ~LogMessage();

        static std::mutex& getMutex();

        LType getType() const;

        LogMessage& operator << (const LType& type);

    private:
        LType m_Type;
    };
    
} // namespace logger

#endif
