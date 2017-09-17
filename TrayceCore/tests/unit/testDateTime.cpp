#include "gtest/gtest.h"

#include "Trayce/Time/DateTime.h"
#include "Trayce/Time/TimeSpan.h"

using namespace Trayce::Time;

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