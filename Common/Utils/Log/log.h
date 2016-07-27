#ifndef __LOG_H__
#define __LOG_H__

#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <windows.h>

inline void SetTextColor(WORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


inline std::string NowTime();

enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4};

class Log
{
public:
    Log();
    virtual ~Log();
    std::ostringstream& PrintLog(TLogLevel level = logINFO);

public:
    static TLogLevel& ReportingLevel();
    static std::string ToString(TLogLevel level);
    static TLogLevel FromString(const std::string& level);
protected:
    std::ostringstream os;
private:
    Log(const Log&);
    Log& operator =(const Log&);
};

inline Log::Log()
{
}

inline std::ostringstream& Log::PrintLog(TLogLevel level)
{
    os << "- " << NowTime();
    os << "  " << ToString(level) << ": ";
    os << std::string(level > logDEBUG ? level - logDEBUG : 0, '\t');
    return os;
}

inline Log::~Log()
{
    fprintf(stderr, "%s", os.str().c_str());
    fflush(stderr);
    SetTextColor(0xFF);
    std::cout << std::endl;
}

inline TLogLevel& Log::ReportingLevel()
{
    static TLogLevel reportingLevel = logDEBUG4;
    return reportingLevel;
}

inline std::string Log::ToString(TLogLevel level)
{
	static const char* const buffer[] = {"ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4"};
    return buffer[level];
}

inline TLogLevel Log::FromString(const std::string& level)
{
    if (level == "DEBUG4")
        return logDEBUG4;
    if (level == "DEBUG3")
        return logDEBUG3;
    if (level == "DEBUG2")
        return logDEBUG2;
    if (level == "DEBUG1")
        return logDEBUG1;
    if (level == "DEBUG")
        return logDEBUG;
    if (level == "INFO")
        return logINFO;
    if (level == "WARNING")
        return logWARNING;
    if (level == "ERROR")
        return logERROR;
    Log().PrintLog(logWARNING) << "Unknown logging level '" << level << "'. Using INFO level as default.";
    return logINFO;
}

typedef Log FILELog;

#define LOG(level) \
    SetTextColor(0xF0); \
    if (level > FILELog::ReportingLevel()); \
    else Log().PrintLog(level)

#define LOG_ERROR \
    SetTextColor(0xFC); \
    if (logERROR > FILELog::ReportingLevel()); \
    else Log().PrintLog(logERROR)

#define LOG_WARNING \
    SetTextColor(0xEC); \
    if (logWARNING > FILELog::ReportingLevel()); \
    else Log().PrintLog(logWARNING)

#define LOG_INFO \
    SetTextColor(0xF9); \
    if (logINFO > FILELog::ReportingLevel()); \
    else Log().PrintLog(logINFO)

#define LOG_DEBUG \
    SetTextColor(0xF0); \
    if (logDEBUG > FILELog::ReportingLevel()); \
    else Log().PrintLog(logDEBUG) \

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS

inline std::string NowTime()
{
    const int MAX_LEN = 200;
    char buffer[MAX_LEN];
    if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, 
            "HH':'mm':'ss", buffer, MAX_LEN) == 0)
        return "Error in NowTime()";

    //char result[100] = {0};
    //static DWORD first = GetTickCount();
    //std::printf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000); 
    return buffer;
}

#else

#include <sys/time.h>

inline std::string NowTime()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000); 
    return result;
}

#endif //WIN32

#endif //__LOG_H__