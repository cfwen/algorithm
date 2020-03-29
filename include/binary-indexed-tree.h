#pragma once

#include "data-structure.h"

namespace binary_indexed_tree
{

void update_bit(vector<int>& bitree, int index, int val)
{
    index += 1;

    while (index < bitree.size())
    {
        bitree[index] += val;
        index += index & (-index);
    }
}

vector<int> construct_bit(const vector<int>& arr)
{
    vector<int> bitree(arr.size() + 1, 0);
    for (int i = 0; i < arr.size(); ++i)
    {
        update_bit(bitree, i, arr[i]);
    }
    return bitree;
}

int get_sum(const vector<int>& bitree, int index)
{
    int sum = 0;

    index += 1;

    while (index)
    {
        sum += bitree[index];
        index -= index & (-index);
    }
    return sum;
}

int get_range_sum(const vector<int>& bitree, int left, int right) 
{
    return get_sum(bitree, right) - get_sum(bitree, left - 1);
}

TEST(binary_indexed_tree, simple_test)
{
    vector<int> arr{2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> bitree = construct_bit(arr);

    EXPECT_EQ(12, get_sum(bitree, 5));

    arr[3] += 6;
    update_bit(bitree, 3, 6);

    EXPECT_EQ(18, get_sum(bitree, 5));
    EXPECT_EQ(30, get_range_sum(bitree, 2, 8));
}

} // namespace binary_indexed_tree
