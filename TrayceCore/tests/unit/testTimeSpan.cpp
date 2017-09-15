#include "gtest/gtest.h"

#include "Trayce/Time.h"

using namespace Trayce::Time;

TEST(TimePoint, fromHours)
{
    TimeSpan ts1 = TimeSpan::fromHours(3ull);
    ASSERT_EQ(3ull*60*60*1000*1000*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromHours(3.5);
    ASSERT_EQ((3ull*60+30)*60*1000*1000*1000, ts2.totalNanoseconds());

}

TEST(TimePoint, fromMinutes)
{
    TimeSpan ts1 = TimeSpan::fromMinutes(3ull);
    ASSERT_EQ(3ull*60*1000*1000*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromMinutes(3.5);
    ASSERT_EQ((3ull*60+30)*1000*1000*1000, ts2.totalNanoseconds());
}

TEST(TimePoint, fromSeconds)
{
    TimeSpan ts1 = TimeSpan::fromSeconds(3ull);
    ASSERT_EQ(3ull*1000*1000*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromSeconds(3.5);
    ASSERT_EQ((3ull*1000+500)*1000*1000, ts2.totalNanoseconds());
}

TEST(TimePoint, fromMilliseconds)
{
    TimeSpan ts1 = TimeSpan::fromMilliseconds(3ull);
    ASSERT_EQ(3ull*1000*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromMilliseconds(3.5);
    ASSERT_EQ((3ull*1000+500)*1000, ts2.totalNanoseconds());
}

TEST(TimePoint, fromMicroseconds)
{
    TimeSpan ts1 = TimeSpan::fromMicroseconds(3ull);
    ASSERT_EQ(3ull*1000, ts1.totalNanoseconds());

    TimeSpan ts2 = TimeSpan::fromMicroseconds(3.5);
    ASSERT_EQ(3ull*1000 + 500, ts2.totalNanoseconds());
}

TEST(TimePoint, fromNanoseconds)
{
    TimeSpan ts1 = TimeSpan::fromNanoseconds(3ull);
    ASSERT_EQ(3ull, ts1.totalNanoseconds());
}