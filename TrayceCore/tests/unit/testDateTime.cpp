#include "gtest/gtest.h"

#include "Trayce/Time/DateTime.h"
#include "Trayce/Time/TimeSpan.h"

using namespace Trayce::Time;

TEST(DateTime, isLeapYear)
{
	// divisible by 4, but not by 100 unless by 400.
	ASSERT_TRUE (DateTime::isLeapYear(4));
	ASSERT_FALSE(DateTime::isLeapYear(7));
	ASSERT_FALSE(DateTime::isLeapYear(100));
	ASSERT_FALSE(DateTime::isLeapYear(399));
	ASSERT_TRUE (DateTime::isLeapYear(400));
	ASSERT_FALSE(DateTime::isLeapYear(401));
	ASSERT_TRUE (DateTime::isLeapYear(404));
	ASSERT_TRUE (DateTime::isLeapYear(2000));
	ASSERT_FALSE(DateTime::isLeapYear(1900));
	ASSERT_TRUE (DateTime::isLeapYear(9200));
}

TEST(DateTime, constructDate)
{
    DateTime dt {2017, 06, 20};

    ASSERT_EQ(2017, dt.getYear());
    ASSERT_EQ(6, dt.getMonth());
    ASSERT_EQ(20, dt.getDay());
    ASSERT_EQ(0, dt.getHour());
    ASSERT_EQ(0, dt.getMinute());
    ASSERT_EQ(0, dt.getSecond());
    ASSERT_EQ(0, dt.getMillisecond());
    ASSERT_EQ(0, dt.getMicrosecond());
    ASSERT_EQ(0, dt.getNanosecond());

    TimeSpan ts = dt.getTimeComponent();
    ASSERT_EQ(0, ts.totalNanoseconds());
}

TEST(DateTime, constructDateWithTime)
{
    DateTime dt {1901, 06, 20, 11, 25, 45};

    ASSERT_EQ(1901, dt.getYear());
    ASSERT_EQ(06, dt.getMonth());
    ASSERT_EQ(20, dt.getDay());

    ASSERT_EQ(0, dt.getNanosecond());
    ASSERT_EQ(0, dt.getMicrosecond());
    ASSERT_EQ(0, dt.getMillisecond());
    ASSERT_EQ(45, dt.getSecond());
    ASSERT_EQ(25, dt.getMinute());
    ASSERT_EQ(11, dt.getHour());

    TimeSpan ts = dt.getTimeComponent();
    ASSERT_EQ(((11*60+25)*60+45)*1000ull*1000*1000, ts.totalNanoseconds());
}

TEST(DateTime, constructDateWithTimeSpan)
{
    DateTime dtNano {1901, 06, 20, TimeSpan::fromNanoseconds(123)};

    ASSERT_EQ(123, dtNano.getNanosecond());
    ASSERT_EQ(0, dtNano.getMicrosecond());
    ASSERT_EQ(0, dtNano.getMillisecond());
    ASSERT_EQ(0, dtNano.getSecond());
    ASSERT_EQ(0, dtNano.getMinute());
    ASSERT_EQ(0, dtNano.getHour());

    DateTime dtMicro {1901, 06, 20, TimeSpan::fromMicroseconds(123)};

    ASSERT_EQ(0, dtMicro.getNanosecond());
    ASSERT_EQ(123, dtMicro.getMicrosecond());
    ASSERT_EQ(0, dtMicro.getMillisecond());
    ASSERT_EQ(0, dtMicro.getSecond());
    ASSERT_EQ(0, dtMicro.getMinute());
    ASSERT_EQ(0, dtMicro.getHour());

    DateTime dtMillis {1901, 06, 20, TimeSpan::fromMilliseconds(123)};

    ASSERT_EQ(0, dtMillis.getNanosecond());
    ASSERT_EQ(0, dtMillis.getMicrosecond());
    ASSERT_EQ(123, dtMillis.getMillisecond());
    ASSERT_EQ(0, dtMillis.getSecond());
    ASSERT_EQ(0, dtMillis.getMinute());
    ASSERT_EQ(0, dtMillis.getHour());

    DateTime dtSeconds {1901, 06, 20, TimeSpan::fromSeconds(56)};

    ASSERT_EQ(0, dtSeconds.getNanosecond());
    ASSERT_EQ(0, dtSeconds.getMicrosecond());
    ASSERT_EQ(0, dtSeconds.getMillisecond());
    ASSERT_EQ(56, dtSeconds.getSecond());
    ASSERT_EQ(0, dtSeconds.getMinute());
    ASSERT_EQ(0, dtSeconds.getHour());

    DateTime dtMinutes {1901, 06, 20, TimeSpan::fromMinutes(46)};

    ASSERT_EQ(0, dtMinutes.getNanosecond());
    ASSERT_EQ(0, dtMinutes.getMicrosecond());
    ASSERT_EQ(0, dtMinutes.getMillisecond());
    ASSERT_EQ(0, dtMinutes.getSecond());
    ASSERT_EQ(46, dtMinutes.getMinute());
    ASSERT_EQ(0, dtMinutes.getHour());

    DateTime dtHours {1901, 06, 20, TimeSpan::fromHours(13)};

    ASSERT_EQ(0, dtHours.getNanosecond());
    ASSERT_EQ(0, dtHours.getMicrosecond());
    ASSERT_EQ(0, dtHours.getMillisecond());
    ASSERT_EQ(0, dtHours.getSecond());
    ASSERT_EQ(0, dtHours.getMinute());
    ASSERT_EQ(13, dtHours.getHour());
}

TEST(DateTime, DateToDays)
{
	int dayCount = 0;
	for (int year = 1; year < 10000; ++year)
	{
		const int monthList[] = {
			31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
		};
		const int leapMonthList[] = {
			31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
		};

		const bool isLeapYear = DateTime::isLeapYear(year);

		for (int month = 0; month < 12; ++month)
		{
			const int monthLength = (isLeapYear ? leapMonthList[month] : monthList[month]);

			for (int day = 0; day < monthLength; day++)
			{
				DateTime date(year, month + 1, day + 1);

				ASSERT_EQ(++dayCount, *reinterpret_cast<int*>(&date));
			}
		}
	}
}

TEST(DateTime, AdvanceDays)
{
    DateTime dt{1, 1, 1};

    ASSERT_EQ(1, dt.getYear());
    ASSERT_EQ(1, dt.getMonth());
    ASSERT_EQ(1, dt.getDay());

    for(int year = 1; year < 10000; ++year)
    {
        const int monthList[] = {
                31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        };
        const int leapMonthList[] = {
                31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        };

        // divisible by 4, but not by 100 unless by 400.
		const bool isLeapYear = DateTime::isLeapYear(year);

        for(int month = 0; month < 12; ++month)
        {
            const int monthLength = (isLeapYear ? leapMonthList[month] : monthList[month]);

            for(int day = 0; day < monthLength; day++)
            {
                ASSERT_EQ(year, dt.getYear()) << "(" << year << ", " << (month+1) << ", " << (day+1) << ") " << *reinterpret_cast<int*>(&dt);
				ASSERT_EQ(month + 1, dt.getMonth()) << "(" << year << ", " << (month+1) << ", " << (day+1) << ") " << *reinterpret_cast<int*>(&dt);
                ASSERT_EQ(day + 1, dt.getDay()) << "(" << year << ", " << (month+1) << ", " << (day+1) << ") " << *reinterpret_cast<int*>(&dt);

                dt = dt + TimeSpan::fromDays(1);
            }
        }
    }
}