#pragma once

#include "data-structure.h"

namespace min_cost_to_make_valid_path
{

struct cmp
{
    bool operator()(pair<int, int>& a, pair<int, int>& b) { return a.first > b.first; }
};
int dijkstra(vector<vector<pair<int, int>>>& graph)
{
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    dist[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    pq.push({0, 0});

    while (!pq.empty())
    {
        auto p = pq.top();
        int i = p.second;
        pq.pop();
        for (auto p : graph[i])
        {
            int j = p.first;
            int wj = p.second;
            int dj = dist[i] + wj;
            if (dj < dist[j])
            {
                dist[j] = dj;
                pq.push({dj, j});
            }
        }
    }
    return dist[n - 1];
}
int min_cost(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    if (m == 1 && n == 1)
        return 0;
    auto index = [=](int i, int j) { return i * n + j; };
    vector<vector<pair<int, int>>> graph(m * n);

    vector<vector<int>> dirs(4);
    dirs[0] = {0, 1};
    dirs[1] = {0, -1};
    dirs[2] = {1, 0};
    dirs[3] = {-1, 0};

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int cij = index(i, j);
            for (int s = 0; s < 4; ++s)
            {
                vector<int>& dir = dirs[s];
                if (i + dir[0] < 0 || i + dir[0] >= m)
                    continue;
                if (j + dir[1] < 0 || j + dir[1] >= n)
                    continue;
                int cij2 = index(i + dir[0], j + dir[1]);
                int d = grid[i][j] == s + 1 ? 0 : 1;
                graph[cij].push_back({cij2, d});
            }
        }
    }
    return dijkstra(graph);
}

TEST(min_cost_to_make_valid_path, simple_test)
{
    vector<vector<int>> grid1 = {{1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}};
    vector<vector<int>> grid2 = {{2, 2, 2}, {2, 2, 2}};

    EXPECT_EQ(3, min_cost(grid1));
    EXPECT_EQ(3, min_cost(grid2));
}

} // namespace min_cost_to_make_valid_path
