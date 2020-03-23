#pragma once

#include "data-structure.h"

namespace min_score_triangulation
{

int min_score_triangulation(vector<int>& A)
{
    int n = A.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            for (int k = i + 1; k < j; ++k)
            {
                dp[i][j] = min(dp[i][j] == 0 ? INT_MAX : dp[i][j], dp[i][k] + A[i] * A[k] * A[j] + dp[k][j]);
            }
        }
    }
    return dp[0][n - 1];
}

TEST(min_score_triangulation, simple_test)
{
    vector<int> arr{1, 3, 1, 4, 1, 5};
    EXPECT_EQ(13, min_score_triangulation(arr));

    vector<int> arr2{17, 97, 74, 55, 68, 64, 46, 48, 9, 2, 70, 39, 52, 31, 86, 2, 31, 8, 28, 78};
    EXPECT_EQ(79338, min_score_triangulation(arr2));
}

} // namespace min_score_triangulation
