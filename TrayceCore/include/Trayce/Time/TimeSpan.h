#ifndef TRAYCE_CORE_TIME_TIMESPAN_H_
#define TRAYCE_CORE_TIME_TIMESPAN_H_

#include <type_traits>

namespace Trayce { namespace Time {

struct TimeSpan final {
    constexpr TimeSpan();
    ~TimeSpan() = default;
    template<typename T> constexpr static typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type fromDays(T days);
    constexpr static TimeSpan fromDays(double days);
    template<typename T> constexpr static typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type fromHours(T hours);
    constexpr static TimeSpan fromHours(double hours);
    template<typename T> constexpr static typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type fromMinutes(T minutes);
    constexpr static TimeSpan fromMinutes(double minutes);
    template<typename T> constexpr static typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type fromSeconds(T seconds);
    constexpr static TimeSpan fromSeconds(double seconds);
    template<typename T> constexpr static typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type fromMilliseconds(T milliseconds);
    constexpr static TimeSpan fromMilliseconds(double milliseconds);
    template<typename T> constexpr static typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type fromMicroseconds(T microseconds);
    constexpr static TimeSpan fromMicroseconds(double microseconds);
    template<typename T> constexpr static typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type fromNanoseconds(T nanoseconds);

    constexpr int getDaysComponent() const;
    constexpr int getHoursComponent() const;
    constexpr int getMinutesComponent() const;
    constexpr int getSecondsComponent() const;
    constexpr int getMillisecondsComponent() const;
    constexpr int getMicrosecondsComponent() const;
    constexpr int getNanosecondsComponent() const;

    constexpr unsigned long long totalNanoseconds() const { return nanoSpan; }

protected:
    constexpr TimeSpan(unsigned long long nanoTimeSpan) : nanoSpan(nanoTimeSpan) { }

private:
    static const unsigned long long nanosecondsToMicroseconds = 1000;
    static const unsigned long long nanosecondsToMilliseconds = nanosecondsToMicroseconds * 1000;
    static const unsigned long long nanosecondsToSeconds = nanosecondsToMilliseconds * 1000;
    static const unsigned long long nanosecondsToMinutes = nanosecondsToSeconds * 60;
    static const unsigned long long nanosecondsToHours = nanosecondsToMinutes * 60;
    static const unsigned long long nanosecondsToDays = nanosecondsToHours * 24;

    unsigned long long nanoSpan;
};

//static_assert(std::is_pod<TimeSpan>::value, "TimeSpan should be a pod.");

constexpr TimeSpan::TimeSpan()
    : nanoSpan(0)
{
}

template<typename T> constexpr typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type TimeSpan::fromDays(T days)
{
    return TimeSpan::fromHours(static_cast<unsigned long long>(days) * 24);
};

constexpr TimeSpan TimeSpan::fromDays(double days)
{
    return TimeSpan::fromHours(days*24.0);
}

template<typename T>
constexpr typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type TimeSpan::fromHours(T hours) {
    return TimeSpan::fromMinutes(static_cast<unsigned long long>(hours) * 60);
}

constexpr TimeSpan TimeSpan::fromHours(double hours) {
    return TimeSpan::fromMinutes(hours*60.0);
}

template<typename T>
constexpr typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type TimeSpan::fromMinutes(T minutes) {
    return TimeSpan::fromSeconds(static_cast<unsigned long long>(minutes) * 60);
}

constexpr TimeSpan TimeSpan::fromMinutes(double minutes) {
    return TimeSpan::fromSeconds(minutes*60.0);
}

template<typename T>
constexpr typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type TimeSpan::fromSeconds(T seconds) {
    return TimeSpan::fromMilliseconds(static_cast<unsigned long long>(seconds) * 1000);
}

constexpr TimeSpan TimeSpan::fromSeconds(double seconds) {
    return TimeSpan::fromMilliseconds(seconds * 1000.0);
}

template<typename T>
constexpr typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type TimeSpan::fromMilliseconds(T milliseconds) {
    return TimeSpan::fromMicroseconds(static_cast<unsigned long long>(milliseconds) * 1000);
}

constexpr TimeSpan TimeSpan::fromMilliseconds(double milliseconds) {
    return TimeSpan::fromMicroseconds(milliseconds * 1000.0);
}

template<typename T>
constexpr typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type TimeSpan::fromMicroseconds(T microseconds) {
    return TimeSpan::fromNanoseconds(1000ull * microseconds);
}

constexpr TimeSpan TimeSpan::fromMicroseconds(double microseconds) {
    return TimeSpan::fromNanoseconds(static_cast<unsigned long long>(microseconds*1000));
}

template<typename T>
constexpr typename std::enable_if<std::is_arithmetic<T>::value, TimeSpan>::type TimeSpan::fromNanoseconds(T nanoseconds) {
    return TimeSpan(nanoseconds);
}

constexpr int TimeSpan::getDaysComponent() const
{
    return static_cast<int>(nanoSpan / nanosecondsToDays);
}

constexpr int TimeSpan::getHoursComponent() const
{
    return static_cast<int>(nanoSpan % nanosecondsToDays / nanosecondsToHours);
}

constexpr int TimeSpan::getMinutesComponent() const
{
    return static_cast<int>(nanoSpan % nanosecondsToHours / nanosecondsToMinutes);
}

constexpr int TimeSpan::getSecondsComponent() const
{
    return static_cast<int>(nanoSpan % nanosecondsToMinutes / nanosecondsToSeconds);
}

constexpr int TimeSpan::getMillisecondsComponent() const
{
    return static_cast<int>(nanoSpan % nanosecondsToSeconds / nanosecondsToMilliseconds);
}

constexpr int TimeSpan::getMicrosecondsComponent() const
{
    return static_cast<int>(nanoSpan % nanosecondsToMilliseconds / nanosecondsToMicroseconds);
}

constexpr int TimeSpan::getNanosecondsComponent() const
{
    return static_cast<int>(nanoSpan % nanosecondsToMicroseconds);
}


constexpr TimeSpan operator+(const TimeSpan& left, const TimeSpan& right)
{
    return TimeSpan::fromNanoseconds(left.totalNanoseconds() + right.totalNanoseconds());
}

constexpr TimeSpan operator-(const TimeSpan& left, const TimeSpan& right)
{
    return TimeSpan::fromNanoseconds(left.totalNanoseconds() - right.totalNanoseconds());
}


}} // Trayce::Time

#endif // TRAYCE_CORE_TIME_TIMESPAN_H_
