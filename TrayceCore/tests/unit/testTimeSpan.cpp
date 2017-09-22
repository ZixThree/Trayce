#include "gtest/gtest.h"

#include "Trayce/Time/TimeSpan.h"

using namespace Trayce::Time;

TEST(TimeSpan, zero)
{
    TimeSpan ts1 = TimeSpan();
    ASSERT_EQ(0, ts1.totalNanoseconds());
}

TEST(TimeSpan, fromDays)
{
    TimeSpan ts1 = TimeSpan::fromDays(3ull);
    ASSERT_EQ(3ull*24*60*60*1000*1000*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromDays(3.5);
    ASSERT_EQ((3ull*24+12)*60*60*1000*1000*1000, ts2.totalNanoseconds());
}

TEST(TimeSpan, fromHours)
{
    TimeSpan ts1 = TimeSpan::fromHours(3ull);
    ASSERT_EQ(3ull*60*60*1000*1000*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromHours(3.5);
    ASSERT_EQ((3ull*60+30)*60*1000*1000*1000, ts2.totalNanoseconds());

}

TEST(TimeSpan, fromMinutes)
{
    TimeSpan ts1 = TimeSpan::fromMinutes(3ull);
    ASSERT_EQ(3ull*60*1000*1000*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromMinutes(3.5);
    ASSERT_EQ((3ull*60+30)*1000*1000*1000, ts2.totalNanoseconds());
}

TEST(TimeSpan, fromSeconds)
{
    TimeSpan ts1 = TimeSpan::fromSeconds(3ull);
    ASSERT_EQ(3ull*1000*1000*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromSeconds(3.5);
    ASSERT_EQ((3ull*1000+500)*1000*1000, ts2.totalNanoseconds());
}

TEST(TimeSpan, fromMilliseconds)
{
    TimeSpan ts1 = TimeSpan::fromMilliseconds(3ull);
    ASSERT_EQ(3ull*1000*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromMilliseconds(3.5);
    ASSERT_EQ((3ull*1000+500)*1000, ts2.totalNanoseconds());
}

TEST(TimeSpan, fromMicroseconds)
{
    TimeSpan ts1 = TimeSpan::fromMicroseconds(3ull);
    ASSERT_EQ(3ull*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromMicroseconds(3.5);
    ASSERT_EQ(3ull*1000 + 500, ts2.totalNanoseconds());
}

TEST(TimeSpan, fromNanoseconds)
{
    TimeSpan ts1 = TimeSpan::fromNanoseconds(3ull);
    ASSERT_EQ(3ull, ts1.totalNanoseconds());
}

TEST(TimeSpan, getComponents)
{
    const int days = 12;
    const int hours = 15;
    const int minutes = 34;
    const int seconds = 56;
    const int millis = 321;
    const int micros = 654;
    const int nanos = 987;
    TimeSpan ts1 = TimeSpan::fromNanoseconds(
            (((((days * 24ull + hours) * 60 + minutes) * 60 + seconds) * 1000 + millis) * 1000 + micros) * 1000 + nanos
                                            );

    ASSERT_EQ(days, ts1.getDaysComponent());
    ASSERT_EQ(hours, ts1.getHoursComponent());
    ASSERT_EQ(minutes, ts1.getMinutesComponent());
    ASSERT_EQ(seconds, ts1.getSecondsComponent());
    ASSERT_EQ(millis, ts1.getMillisecondsComponent());
    ASSERT_EQ(micros, ts1.getMicrosecondsComponent());
    ASSERT_EQ(nanos, ts1.getNanosecondsComponent());
}

TEST(TimeSpan, add_with_operator)
{
    TimeSpan ts1 = TimeSpan::fromNanoseconds(12345);
    TimeSpan ts2 = TimeSpan::fromNanoseconds(60000);
    ASSERT_EQ(72345, (ts1+ts2).totalNanoseconds());
}

TEST(TimeSpan, subtract_with_operator)
{
    TimeSpan ts2 = TimeSpan::fromNanoseconds(60000);
    TimeSpan ts1 = TimeSpan::fromNanoseconds(12345);
    ASSERT_EQ(47655, (ts2-ts1).totalNanoseconds());
}