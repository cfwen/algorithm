#pragma once

#include "data-structure.h"

using Graph = vector<vector<int>>;
using ipair = pair<int, int>;

class compare
{
  public:
    bool operator()(ipair& a, ipair& b) { return a.second > b.second; }
};

int dijkstra(Graph& graph, int source)
{
    priority_queue<ipair, vector<ipair>, compare> pq;
    for (int i = 0; i < graph.size(); ++i)
    {
        if (i != source)
        {
            graph[i][i] = INT_MAX;
            pq.push({i, INT_MAX});
        }
    }
    graph[source][source] = 0;
    pq.push({source, 0});
    while (!pq.empty())
    {
        int u = pq.top().first;
        pq.pop();
        for (int v = 0; v < graph.size(); ++v)
        {
            if (v == u || graph[u][v] == -1)
                continue;
            int dv = graph[u][u] + graph[u][v];
            if (dv < graph[v][v])
            {
                graph[v][v] = dv;
                pq.push({v, dv});
            }
        }
    }
    return 0;
}

TEST(dijkstra_test, simple_test)
{
    int n = 4;
    vector<vector<int>> paths = {{1, 0, 1}, {1, 2, 1}, {2, 3, 1}};
    Graph graph(n + 1, vector<int>(n + 1, -1));
    for (vector<int>& path : paths)
    {
        graph[path[0]][path[1]] = path[2];
    }
    int re = dijkstra(graph, 1);

    EXPECT_EQ(0, re);
    EXPECT_EQ(2, graph[3][3]);
}
