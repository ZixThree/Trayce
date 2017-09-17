#include "Trayce/LogService.h"
#include "Trayce/Time/TimePoint.h"
#include "InternalData.h"

#include <mutex>
#include <vector>
#include <algorithm>

#include <cstdarg>

namespace Trayce { namespace Log {

struct LogConsoleReceiver : public LogReceiver {
    void OnLog(const Trayce::Time::TimePoint& timestamp, LogLevel level, const char* category, const char* message) {
        fprintf(level > LogLevel::Normal ? stderr : stdout, "[todo-time] [%s] %s", category, message);
    }

    static LogConsoleReceiver& get() {
        static LogConsoleReceiver receiver;
        return receiver;
    }
};

struct LogService::LogServiceImpl {
    LogServiceImpl() {
        Categories.reserve(MaximumCategoryId);
        receivers.reserve(32);
        receivers.push_back(&LogConsoleReceiver::get());
    }

    ~LogServiceImpl() {}

    void registerReceiver(LogReceiver *receiver);
    void unregisterReceiver(LogReceiver *receiver);

    void sendLog(const Trayce::Time::TimePoint& timestamp, LogLevel level, const char* category, const char* message);
    void log(LogLevel level, LogCategoryId categoryId, const char* message, va_list args);

    std::mutex receiverMutex;
    std::vector<LogReceiver *> receivers;

    struct LogCategory {
        const std::string CategoryName;
    };

    std::mutex CategoriesMutex;
    const unsigned int MaximumCategoryId = 128;
    std::vector<LogCategory> Categories;

    LogCategoryId registerCategory(const char* Name);
};

void LogService::LogServiceImpl::registerReceiver(LogReceiver *receiver) {
    std::lock_guard<std::mutex> lock(receiverMutex);
    auto whereIt = std::find(std::begin(receivers), std::end(receivers), receiver);
    if (whereIt == receivers.end()) {
        receivers.push_back(receiver);
    }
}

void LogService::LogServiceImpl::unregisterReceiver(LogReceiver *receiver) {
    std::lock_guard<std::mutex> lock(receiverMutex);
    std::remove(std::begin(receivers), std::end(receivers), receiver);
}

void LogService::LogServiceImpl::sendLog(
        const Trayce::Time::TimePoint& timestamp,
        LogLevel level,
        const char* category,
        const char* message) {
    std::lock_guard<std::mutex> lock(receiverMutex);
    for(auto receiver : receivers) {
        receiver->OnLog(timestamp, level, category, message);
    }
}

void LogService::LogServiceImpl::log(LogLevel level, LogCategoryId categoryId, const char* message, va_list args) {

    auto timestamp = std::chrono::high_resolution_clock::now();
    Trayce::Time::TimePoint timePoint =
            Trayce::Time::TimePoint::fromEpoch(
                    Trayce::Time::TimeSpan::fromNanoseconds(
                            std::chrono::duration_cast<std::chrono::nanoseconds>(timestamp.time_since_epoch()).count()
                    )
            );

    char formattedMessage[8192];
#if _WIN32
    vsprintf_s(formattedMessage, 8192, message, args);
#else
    vsnprintf(formattedMessage, 8192, message, args);
#endif

    sendLog(timePoint, level, Categories[categoryId].CategoryName.c_str(), formattedMessage);
}

LogCategoryId LogService::LogServiceImpl::registerCategory(const char *Name) {
    std::lock_guard<std::mutex> lock(CategoriesMutex);
    if(Categories.size() == Categories.max_size())
    {
        LogService::get().log(LogLevel::Critical, GTrayceCoreCategoryId, "No more log category slot available.");
        return -1;
    }

    Categories.push_back(LogCategory{Name});
    return static_cast<LogCategoryId>(Categories.size() - 1);
}

LogService::LogService() = default;

LogService::~LogService() = default;

void LogService::registerReceiver(LogReceiver *receiver) {
    Impl->registerReceiver(receiver);
}

void LogService::unregisterReceiver(LogReceiver *receiver) {
    Impl->unregisterReceiver(receiver);
}

LogCategoryId LogService::registerCategory(const char *Name) {
    return Impl->registerCategory(Name);
}

void LogService::log(LogLevel level, LogCategoryId categoryId, const char *format, ...) {
    va_list args;
    va_start(args, format);
    Impl->log(level, categoryId, format, args);
    va_end(args);
}

}}