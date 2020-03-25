#pragma once

#include "data-structure.h"

namespace sliding_window_maximum
{

vector<int> max_sliding_window(vector<int>& nums, int k)
{
    if (k == 1)
        return nums;
    if (nums.size() == 1)
        return nums;
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i)
    {
        if (!dq.empty() && dq.front() == i - k)
            dq.pop_front();
        while (!dq.empty() && nums[i] > nums[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        // cout << dq.front() << " " << nums[i] << " " << dq.size() << "\n";
        if (i + 1 >= k)
        {
            res.push_back(nums[dq.front()]);
        }
    }

    return res;
}

TEST(sliding_window_maximum, simple_test)
{
    vector<int> arr{1, 3, -1, -3, -4, 3, 6, 7};
    vector<int> res{3, 3, -1, 3, 6, 7};
    EXPECT_EQ(res, max_sliding_window(arr, 3));
}

} // namespace sliding_window_maximum