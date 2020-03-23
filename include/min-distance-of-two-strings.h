#pragma once

#include "data-structure.h"

namespace min_distance
{

int min_distance(string word1, string word2)
{
    int n1 = word1.size();
    int n2 = word2.size();
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, n1 + n2));
    for (int i2 = 0; i2 < n2; ++i2)
    {
        dp[n1][i2] = n2 - i2;
    }
    for (int i1 = 0; i1 < n1; ++i1)
    {
        dp[i1][n2] = n1 - i1;
    }
    dp[n1][n2] = 0;
    for (int k = n1 + n2 - 1; k >= 0; --k)
    {
        for (int i1 = min(n1 - 1, k), i2 = max(0, k - i1); i1 >= 0 && i2 < n2; --i1, ++i2)
        {
            if (word1[i1] == word2[i2])
            {
                dp[i1][i2] = dp[i1 + 1][i2 + 1];
            }
            else
            {
                dp[i1][i2] = 1 + min(dp[i1 + 1][i2], dp[i1][i2 + 1]);
            }
        }
    }
    // for(int i1 = 0; i1 <= n1; ++i1)
    // {
    //     for(int i2 = 0; i2 <= n2; ++i2)
    //     {
    //         cout << dp[i1][i2] << " ";
    //     }
    //     cout << "\n";
    // }
    return dp[0][0];
}

TEST(min_distance, simple_test)
{
    EXPECT_EQ(2, min_distance("sea", "eat"));
    string word1 = "dinitrophenylhydrazine";
    string word2 = "acetylphenylhydrazine";
    EXPECT_EQ(11, min_distance(word1, word2));
}

} // namespace min_distance
