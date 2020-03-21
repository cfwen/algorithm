#pragma once

#include "data-structure.h"

int binary_search(vector<int>& arr, int target)
{
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target)
            left = mid + 1;
        else if (arr[mid] > target)
            right = mid - 1;
        else
            return mid;
    }
    return -1;
}

TEST(binary_search_test, target_exist)
{
    vector<int> arr1{1, 2, 3, 5, 8, 9};
    EXPECT_EQ(0, binary_search(arr1, 1));
    EXPECT_EQ(5, binary_search(arr1, 9));
    EXPECT_EQ(3, binary_search(arr1, 5));
    EXPECT_EQ(-1, binary_search(arr1, 10));
}
