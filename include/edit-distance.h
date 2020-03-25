#pragma once

#include "data-structure.h"

namespace edit_distance
{

vector<vector<int>> mem;
int minDistance(string word1, string word2, int i1, int i2)
{
    if (i1 == word1.size())
        return word2.size() - i2;
    if (i2 == word2.size())
        return word1.size() - i1;
    if (mem[i1][i2] != -1)
        return mem[i1][i2];
    int res = INT_MAX;
    if (word1[i1] == word2[i2])
    {
        res = minDistance(word1, word2, i1 + 1, i2 + 1);
    }
    else
    {
        res = min(res, 1 + minDistance(word1, word2, i1 + 1, i2 + 1));
        res = min(res, 1 + minDistance(word1, word2, i1 + 1, i2));
        res = min(res, 1 + minDistance(word1, word2, i1, i2 + 1));
    }
    mem[i1][i2] = res;
    return res;
}

int min_distance(string word1, string word2)
{
    int n1 = word1.size();
    int n2 = word2.size();

    if (word1.empty())
        return word2.size();
    if (word2.empty())
        return word1.size();

    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, INT_MAX));

    for (int i = 0; i <= n1; ++i)
    {
        dp[i][n2] = n1 - i;
    }
    for (int i = 0; i <= n2; ++i)
    {
        dp[n1][i] = n2 - i;
    }
    for (int i1 = n1 - 1; i1 >= 0; --i1)
    {
        for (int i2 = n2 - 1; i2 >= 0; --i2)
        {
            if (word1[i1] == word2[i2])
                dp[i1][i2] = dp[i1 + 1][i2 + 1];
            else
            {
                dp[i1][i2] = min(dp[i1][i2], 1 + dp[i1 + 1][i2 + 1]);
                dp[i1][i2] = min(dp[i1][i2], 1 + dp[i1][i2 + 1]);
                dp[i1][i2] = min(dp[i1][i2], 1 + dp[i1 + 1][i2]);
            }
        }
    }
    return dp[0][0];
}

TEST(edit_distance, simple_test)
{
    EXPECT_EQ(3, min_distance("horse", "ros"));
    EXPECT_EQ(5, min_distance("intention", "execution"));
    EXPECT_EQ(6, min_distance("dinitrophenylhydrazine", "acetylphenylhydrazine"));
}

} // namespace edit_distance
