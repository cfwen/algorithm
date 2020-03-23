#pragma once

#include "data-structure.h"

namespace split_array
{

int split_array(vector<int>& nums, int m)
{
    int n = nums.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INT_MAX));
    dp[0] = vector<long long>(m, 0);
    vector<long long> sum(n + 1, 0);
    for (int i = 0; i < n; ++i)
        sum[i + 1] = sum[i] + nums[i];
    // dp[i][j] means the minimum of largest sum of that array[0..i] with split j
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= min(i, m); ++j)
        {
            for (int k = j - 1; k <= i; ++k)
                dp[i][j] = min(dp[i][j], max(dp[k][j - 1], sum[i] - sum[k]));
        }
    }
    return dp[n][m];
}

TEST(split_array, simple_test)
{
    vector<int> arr{7, 2, 5, 10, 8};
    int m = 2;
    EXPECT_EQ(18, split_array(arr, m));

    vector<int> arr2{1, 2147483647};
    EXPECT_EQ(2147483647, split_array(arr2, m));
}

} // namespace split_array
