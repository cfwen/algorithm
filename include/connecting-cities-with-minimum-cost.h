#pragma once

#include "data-structure.h"

namespace connecting_cities_with_minimum_cost
{

// using Kruskal's algorithm to compute minimum spanning tree
// using union finding to connect edges
int find(vector<int>& parent, int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}
int minimum_cost(int N, vector<vector<int>>& connections)
{
    sort(connections.begin(), connections.end(), [](vector<int>& c1, vector<int>& c2) { return c1[2] < c2[2]; });
    vector<int> parent(N + 1);
    for (int i = 1; i <= N; ++i)
        parent[i] = i;

    int min_cost = 0;
    int num_edge = 0;
    for (auto& conn : connections)
    {
        int p0 = find(parent, conn[0]);
        int p1 = find(parent, conn[1]);
        if (p0 != p1)
        {
            num_edge += 1;
            min_cost += conn[2];
            parent[p0] = parent[p1];
        }
    }
    if (num_edge < N - 1)
        return -1;
    return min_cost;
}

TEST(connecting_cities_with_minimum_cost, simple_test)
{
    vector<vector<int>> grid1 = {{1, 2, 5}, {1, 3, 6}, {2, 3, 1}};
    vector<vector<int>> grid2 = {{1, 2, 3}, {3, 4, 4}};

    EXPECT_EQ(6, minimum_cost(3, grid1));
    EXPECT_EQ(-1, minimum_cost(4, grid2));
}

} // namespace connecting_cities_with_minimum_cost
