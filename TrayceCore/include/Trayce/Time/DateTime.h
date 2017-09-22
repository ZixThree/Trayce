#ifndef TRAYCE_CORE_TIME_DATETIME_H_
#define TRAYCE_CORE_TIME_DATETIME_H_

#include "Trayce/Time/TimeSpan.h"

namespace Trayce { namespace Time
{

struct DateTime final
{
    constexpr DateTime();

    DateTime(int year, int month, int day);
    DateTime(int year, int month, int day, const TimeSpan &time);
    DateTime(int year, int month, int day, int hour, int minute, int seconds);

    ~DateTime() = default;

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    int getMillisecond() const;
    int getMicrosecond() const;
    int getNanosecond() const;

    TimeSpan getTimeComponent() const;

    friend constexpr DateTime operator+(const DateTime &left, const TimeSpan &right);
    friend constexpr DateTime operator-(const DateTime &left, const TimeSpan &right);

    const DateTime getEpoch() { return DateTime(DaysAt1900, TimeSpan()); }

    static constexpr bool isLeapYear(int year);

private:
    constexpr DateTime(int days, const TimeSpan &time);

    static int GetMonthInYear(bool isLeapYear, int days);
    static int GetDaysInYearAtMonth(bool isLeapYear, int month);

    static constexpr const int DaysPer1Year = 365;
    static const int DaysPer4Years = DaysPer1Year * 4 + 1;
    static const int DaysPer100Years = DaysPer4Years * (100 / 4) - 1;
    static const int DaysPer400Years = DaysPer100Years * 4 + 1;

    static const int DaysAt1900 = 4 * DaysPer400Years + 3 * DaysPer100Years;

    int days;
    TimeSpan time;
};

constexpr DateTime::DateTime()
        : days(0), time()
{
}

constexpr DateTime::DateTime(int days, const TimeSpan &time)
        : days(days), time(time)
{
}

inline DateTime::DateTime(int year, int month, int day)
        : DateTime(year, month, day, TimeSpan())
{
}

inline DateTime::DateTime(int year, int month, int day, const TimeSpan& time)
    : days(
          (year-1)*365 + ((year-1)/4) - ((year-1)/100) + ((year-1)/400) +
          GetDaysInYearAtMonth(isLeapYear(year), month) +
          day
          )
    , time(time)
{

}

inline DateTime::DateTime(int year, int month, int day, int hour, int minute, int seconds)
        : DateTime(year, month, day,
                   TimeSpan::fromHours(hour) +
                   TimeSpan::fromMinutes(minute) +
                   TimeSpan::fromSeconds(seconds)
                  )
{
}

#define TRAYCE_DATETIME_DAYS_IN_MONTH(isLeapYear) \
static const int MonthDays[] = \
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 }; \
static const int LeapMonthDays[] = \
    { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }; \
auto& ReferenceMonthDays = isLeapYear ? LeapMonthDays : MonthDays

inline int DateTime::GetMonthInYear(bool isLeapYear, int days)
{
    TRAYCE_DATETIME_DAYS_IN_MONTH(isLeapYear);

    int monthIndex = 1;
    for(; monthIndex < 12; ++monthIndex)
    {
        if(days <= ReferenceMonthDays[monthIndex])
        {
            break;
        }
    }

    return monthIndex;
}

inline int DateTime::GetDaysInYearAtMonth(bool isLeapYear, int month)
{
    TRAYCE_DATETIME_DAYS_IN_MONTH(isLeapYear);

    return ReferenceMonthDays[month - 1];
}

inline int DateTime::getYear() const
{
	int years = 1;
	int current = days;
	while(current >= DaysPer400Years)
	{
		current -= DaysPer400Years;
		years += 400;
	}
	while(current >= DaysPer100Years)
	{
		current -= DaysPer100Years;
		years += 100;
	}
	while(current >= DaysPer4Years)
	{
		current -= DaysPer4Years;
		years += 4;
	}
	while(current >= DaysPer1Year)
	{
		current -= DaysPer1Year;
		years += 1;
	}
	if(current == 0)
	{
		years--;
	}

	return years;
}

inline int DateTime::getMonth() const
{
	const int currentYear = getYear();
	const int remainingDays = days - (currentYear - 1) * 365 - (currentYear - 1) / 4 + (currentYear - 1) / 100 - (currentYear - 1) / 400;
	const bool leapYear = isLeapYear(currentYear);
    return GetMonthInYear(leapYear, remainingDays);
}

inline int DateTime::getDay() const
{
	const int currentYear = getYear();
	const int remainingDays = days - (currentYear - 1) * 365 - (currentYear - 1) / 4 + (currentYear - 1) / 100 - (currentYear - 1) / 400;
	const bool leapYear = isLeapYear(currentYear);
	const int month = GetMonthInYear(leapYear, remainingDays);
    return remainingDays - GetDaysInYearAtMonth(leapYear, month);
}

inline int DateTime::getHour() const
{
    return time.getHoursComponent();
}

inline int DateTime::getMinute() const
{
    return time.getMinutesComponent();
}

inline int DateTime::getSecond() const
{
    return time.getSecondsComponent();
}

inline int DateTime::getMillisecond() const
{
    return time.getMillisecondsComponent();
}

inline int DateTime::getMicrosecond() const
{
    return time.getMicrosecondsComponent();
}

inline int DateTime::getNanosecond() const
{
    return time.getNanosecondsComponent();
}

inline TimeSpan DateTime::getTimeComponent() const
{
    return time;
}

constexpr bool DateTime::isLeapYear(int year)
{
    return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

constexpr DateTime operator+(const DateTime &left, const TimeSpan &right)
{
    return DateTime(left.days + right.getDaysComponent(), right - TimeSpan::fromDays(right.getDaysComponent()));
}

constexpr DateTime operator-(const DateTime &left, const TimeSpan &right)
{
    return DateTime(left.days - right.getDaysComponent(), right);
}


}} // Trayce::Time

#endif // TRAYCE_CORE_TIME_DATETIME_H_