#ifndef TRAYCE_CORE_TIME_TIMEPOINT_H_
#define TRAYCE_CORE_TIME_TIMEPOINT_H_

#include "Trayce/Time/TimeSpan.h"

namespace Trayce { namespace Time {

struct TimePoint final {
    constexpr TimePoint() = default;
    ~TimePoint() = default;

    constexpr unsigned long long getNanosecondsFromEpoch() const;

    static constexpr TimePoint fromEpoch(const TimeSpan& timeSpan);

    friend constexpr TimePoint operator+(const TimePoint& left, const TimeSpan& right);
    friend constexpr TimePoint operator-(const TimePoint& left, const TimeSpan& right);
protected:
    constexpr TimePoint(unsigned long long nanoFromEpoch) : nanoFromEpoch(nanoFromEpoch) { }

private:
    unsigned long long nanoFromEpoch;
};

static_assert(std::is_pod<TimePoint>::value, "TimePoint should be a pod.");

constexpr unsigned long long TimePoint::getNanosecondsFromEpoch() const
{
    return nanoFromEpoch;
}

constexpr TimePoint TimePoint::fromEpoch(const TimeSpan& timeSpan) {
    return TimePoint(timeSpan.totalNanoseconds());
}

constexpr TimePoint operator+(const TimePoint& left, const TimeSpan& right) {
    return TimePoint{left.nanoFromEpoch + right.totalNanoseconds()};
}

constexpr TimePoint operator-(const TimePoint& left, const TimeSpan& right) {
    return TimePoint{left.nanoFromEpoch + right.totalNanoseconds()};
}

}} // Trayce::Time

#endif // TRAYCE_CORE_TIME_TIMEPOINT_H_
