#include "gtest/gtest.h"

#include "Trayce/Time/TimeSpan.h"

using namespace Trayce::Time;

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

TEST(TimeSpan, add_with_operator)
{
    TimeSpan ts1 = TimeSpan::fromNanoseconds(12345);
    TimeSpan ts2 = TimeSpan::fromNanoseconds(60000);
    ASSERT_EQ(72345, (ts1+ts2).totalNanoseconds());
}