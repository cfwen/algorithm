#pragma once

#include "data-structure.h"

namespace stream_median
{

class StreamMedian
{
  public:
    void add_num(int n)
    {
        higher.push(n);
        lower.push(higher.top());
        higher.pop();
        if (lower.size() > higher.size())
        {
            higher.push(lower.top());
            lower.pop();
        }
    }

    double find_median()
    {
        if (higher.size() > lower.size())
            return higher.top();
        else
            return (higher.top() + lower.top()) / 2.0;
    }

    priority_queue<int, vector<int>, less<int>> lower;
    priority_queue<int, vector<int>, greater<int>> higher;
};

TEST(StreamMedian, simple_test)
{
    StreamMedian sm;
    sm.add_num(1);
    sm.add_num(2);
    EXPECT_EQ(1.5, sm.find_median());
    sm.add_num(5);
    EXPECT_EQ(2, sm.find_median());
    sm.add_num(3);
    EXPECT_EQ(2.5, sm.find_median());
    sm.add_num(8);
    EXPECT_EQ(3, sm.find_median());
}

} // namespace stream_median
