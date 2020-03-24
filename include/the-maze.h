#pragma once

#include "data-structure.h"
#include "dijkstra.h"

namespace maze
{

using dijkstra::dijkstra;

int shortest_distance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination)
{
    int n = maze.size();
    int m = maze[0].size();
    auto ci = [&](int r, int c) { return r * m + c; };
    auto cv = [&](vector<int>& s) { return s[0] * m + s[1]; };
    unordered_map<int, int> cell_index;
    vector<vector<pair<int, int>>> adj;
    stack<vector<int>> ss;
    unordered_map<int, int> visited;
    cell_index[cv(start)] = 0;
    adj.push_back(vector<pair<int, int>>{});
    ss.push(start);
    // build the graph by connecting two reachable cells
    while (!ss.empty())
    {
        vector<int> s = ss.top();
        int sk = cv(s);
        if (cell_index.find(sk) == cell_index.end())
        {
            cell_index[sk] = cell_index.size() - 1;
            adj.push_back(vector<pair<int, int>>{});
        }
        int si = cell_index[sk];
        visited[si] = 1;
        ss.pop();

        int row = s[0];
        int col = s[1];
        for (row = s[0] + 1; row < n; ++row)
        {
            if (maze[row][col])
                break;
        }
        row--;
        if (row > s[0] && maze[row][col] == 0)
        {
            int tk = ci(row, col);
            if (cell_index.find(tk) == cell_index.end())
            {
                cell_index[tk] = cell_index.size() - 1;
                adj.push_back(vector<pair<int, int>>{});
            }
            int ti = cell_index[tk];
            adj[si].emplace_back(ti, row - s[0]);
            if (!visited[ti])
                ss.push({row, col});
        }
        row = s[0];
        col = s[1];
        for (col = s[1] + 1; col < m; ++col)
        {
            if (maze[row][col])
                break;
        }
        col--;
        if (col > s[1] && maze[row][col] == 0)
        {
            int tk = ci(row, col);
            if (cell_index.find(tk) == cell_index.end())
            {
                cell_index[tk] = cell_index.size() - 1;
                adj.push_back(vector<pair<int, int>>{});
            }
            int ti = cell_index[tk];
            adj[si].emplace_back(ti, col - s[1]);
            if (!visited[ti])
                ss.push({row, col});
        }
        row = s[0];
        col = s[1];
        for (row = s[0] - 1; row >= 0; --row)
        {
            if (maze[row][col])
                break;
        }
        row += 1;
        if (row < s[0] && maze[row][col] == 0)
        {
            int tk = ci(row, col);
            if (cell_index.find(tk) == cell_index.end())
            {
                cell_index[tk] = cell_index.size() - 1;
                adj.push_back(vector<pair<int, int>>{});
            }
            int ti = cell_index[tk];
            adj[si].emplace_back(ti, s[0] - row);
            if (!visited[ti])
                ss.push({row, col});
        }
        row = s[0];
        col = s[1];
        for (col = s[1] - 1; col >= 0; --col)
        {
            if (maze[row][col])
                break;
        }
        col += 1;
        if (col < s[1] && maze[row][col] == 0)
        {
            int tk = ci(row, col);
            if (cell_index.find(tk) == cell_index.end())
            {
                cell_index[tk] = cell_index.size() - 1;
                adj.push_back(vector<pair<int, int>>{});
            }
            int ti = cell_index[tk];
            adj[si].emplace_back(ti, s[1] - col);
            if (!visited[ti])
                ss.push({row, col});
        }
    }
    int dk = cv(destination);
    if (cell_index.find(dk) == cell_index.end())
        return -1;
    int di = cell_index[dk];
    int nn = adj.size();
    vector<vector<int>> graph(nn, vector<int>(nn, -1));
    for (int i = 0; i < adj.size(); ++i)
    {
        for (int j = 0; j < adj[i].size(); ++j)
        {
            graph[i][adj[i][j].first] = adj[i][j].second;
        }
    }
    // for(int i = 0; i < graph.size(); ++i)
    // {
    //     for(int j = 0; j < graph[i].size(); ++j)
    //     {
    //         cout << graph[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    int dist = dijkstra(graph, 0);
    return graph[di][di];
}

TEST(maze, simple_test)
{
    vector<vector<int>> maze{{0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 1, 0}, {1, 1, 0, 1, 1}, {0, 0, 0, 0, 0}};
    vector<int> start{0, 4};
    vector<int> destination{4, 4};

    EXPECT_EQ(12, shortest_distance(maze, start, destination));
}

} // namespace maze
