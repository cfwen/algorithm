#pragma once

#include "data-structure.h"

namespace student_attendance_record
{

int check_record(int n)
{
    // consider P and L first
    // dp[i] is the number of all records of first i attendances
    // dl1[i] is the number of records end with one L
    // dl2[i] is the number of records end with LL
    vector<long long> dp(n + 1, 0);
    vector<long long> dl1(n + 1, 0);
    vector<long long> dl2(n + 1, 0);
    dp[0] = 1;
    dp[1] = 2;
    dl1[1] = 1;
    long long M = 1000000007;
    for (int i = 2; i <= n; ++i)
    {
        long long l1 = dl1[i - 1]; // records end with L
        long long l2 = dl2[i - 1]; // records end with LL
        long long np = dp[i - 1];
        long long nl = np - l2;     // records that can append L
        dp[i] = np;                 // append P
        dp[i] += (np + M - l2) % M; // append L
        dp[i] %= M;
        dl1[i] = (np + M - l1 + M - l2) % M;
        dl2[i] = dl1[i - 1]; // append L on records with ending L
        // cout << dp[i] << " " << dl1[i] << " " << dl2[i] << "\n";
    }
    // insert A at any position
    long long sum = dp[n];
    for (int i = 1; i <= n; i++)
    {
        sum += (dp[i - 1] * dp[n - i]) % M;
    }
    sum %= M;
    return sum;
}

TEST(student_attendance_record, simple_test)
{
    EXPECT_EQ(3536, check_record(10));
    EXPECT_EQ(320634376, check_record(50000));
}

} // namespace student_attendance_record
