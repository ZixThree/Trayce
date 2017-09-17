#include "Trayce/Time.h"

namespace Trayce { namespace Time
{

struct DateTime final
{
    constexpr DateTime();

    constexpr DateTime(int year, int month, int day);
    constexpr DateTime(int year, int month, int day, const TimeSpan& time);
    constexpr DateTime(int year, int month, int day, int hour, int minute, int seconds);

    ~DateTime() = default;

    constexpr int getYear() const;
    constexpr int getMonth() const;
    constexpr int getDay() const;
    constexpr int getHour() const;
    constexpr int getMinute() const;
    constexpr int getSecond() const;
    constexpr int getMillisecond() const;
    constexpr int getMicrosecond() const;
    constexpr int getNanosecond() const;

    constexpr TimeSpan getTimeComponent() const;

private:
    static const unsigned long long nanosecondsToMicroseconds = 1000;
    static const unsigned long long nanosecondsToMilliseconds = nanosecondsToMicroseconds * 1000;
    static const unsigned long long nanosecondsToSeconds = nanosecondsToMilliseconds * 1000;
    static const unsigned long long nanosecondsToMinutes = nanosecondsToSeconds * 60;
    static const unsigned long long nanosecondsToHours = nanosecondsToMinutes * 60;
    int year;
    int month;
    int day;
    TimeSpan time;
};

constexpr DateTime::DateTime()
    : year(1900)
    , month(01)
    , day(01)
    , time()
{
}

constexpr DateTime::DateTime(int year, int month, int day)
        : year(year)
        , month(month)
        , day(day)
        , time(TimeSpan())
{
}

constexpr DateTime::DateTime(int year, int month, int day, const TimeSpan& time)
    : year(year)
    , month(month)
    , day(day)
    , time(time)
{

}

constexpr DateTime::DateTime(int year, int month, int day, int hour, int minute, int seconds)
        : year(year)
        , month(month)
        , day(day)
        , time(
                TimeSpan::fromHours(hour)+
                TimeSpan::fromMinutes(minute)+
                TimeSpan::fromSeconds(seconds)
              )
{
}

constexpr int DateTime::getYear() const
{
    return year;
}

constexpr int DateTime::getMonth() const
{
    return month;
}

constexpr int DateTime::getDay() const
{
    return day;
}

constexpr int DateTime::getHour() const
{
    return static_cast<int>(time.totalNanoseconds() / nanosecondsToHours);
}

constexpr int DateTime::getMinute() const
{
    return static_cast<int>((time.totalNanoseconds() % nanosecondsToHours) / nanosecondsToMinutes);
}

constexpr int DateTime::getSecond() const
{
    return static_cast<int>((time.totalNanoseconds() % nanosecondsToMinutes) / nanosecondsToSeconds);
}

constexpr int DateTime::getMillisecond() const
{
    return static_cast<int>((time.totalNanoseconds() % nanosecondsToSeconds) / nanosecondsToMilliseconds);
}

constexpr int DateTime::getMicrosecond() const
{
    return static_cast<int>((time.totalNanoseconds() % nanosecondsToMilliseconds) / nanosecondsToMicroseconds);
}

constexpr int DateTime::getNanosecond() const
{
    return static_cast<int>((time.totalNanoseconds() % nanosecondsToMicroseconds));
}

constexpr TimeSpan DateTime::getTimeComponent() const
{
    return time;
}

}} // Trayce::Time