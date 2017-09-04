#ifndef TRAYCE_LOGSERVICE_H
#define TRAYCE_LOGSERVICE_H

#include <memory>

namespace Trayce { namespace Time {
    struct TimePoint;
}}

namespace Trayce { namespace Log {

enum class LogLevel {
    VeryVerbose = -20,
    Verbose = -10,
    Normal = 0,
    Warning = 10,
    Error = 20,
    Critical = 30
};

typedef int LogCategoryId;

class LogReceiver {
public:
    virtual void OnLog(const Trayce::Time::TimePoint& timestamp, LogLevel level, const char* category, const char* message) = 0;
};

class LogService final {

public:
    static LogService& get() {
        static LogService service;
        return service;
    }

private:
    LogService();

public:
    ~LogService();

    LogService(const LogService&) = delete;

    void registerReceiver(LogReceiver* receiver);
    void unregisterReceiver(LogReceiver* receiver);

    LogCategoryId registerCategory(const char* Name);

    void log(LogLevel level, LogCategoryId categoryId, const char* format, ...);

private:

    struct LogServiceImpl;
    std::unique_ptr<LogServiceImpl> Impl;
};



}}

#endif //TRAYCE_LOGSERVICE_H
