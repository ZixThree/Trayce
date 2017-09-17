#ifndef TRAYCE_CORE_TIME_TIMESPAN_H_
#define TRAYCE_CORE_TIME_TIMESPAN_H_

namespace Trayce { namespace Time {

struct TimeSpan final {
    constexpr TimeSpan() = default;
    ~TimeSpan() = default;

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

    constexpr unsigned long long totalNanoseconds() const { return nanoSpan; }

protected:
    constexpr TimeSpan(unsigned long long nanoTimeSpan) : nanoSpan(nanoTimeSpan) { }

private:
    unsigned long long nanoSpan;
};

static_assert(std::is_pod<TimeSpan>::value, "TimeSpan should be a pod.");


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
