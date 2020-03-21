#pragma once

#include "data-structure.h"

namespace number_of_islands
{

using Grid = vector<vector<int>>;

void dfs(Grid& grid, int row, int col)
{
    if (!grid[row][col])
        return;
    grid[row][col] = 0;
    if (row >= 1)
        dfs(grid, row - 1, col);
    if (col >= 1)
        dfs(grid, row, col - 1);
    if (row < grid.size() - 1)
        dfs(grid, row + 1, col);
    if (col < grid[row].size() - 1)
        dfs(grid, row, col + 1);
}

int num_islands(Grid& grid)
{
    int res = 0;
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            if (grid[i][j])
            {
                dfs(grid, i, j);
                res += 1;
            }
        }
    }
    return res;
}

TEST(num_islands, simple_test)
{
    Grid grid1 = {{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 1}};
    Grid grid2 = {{1, 1, 1}, {0, 1, 0}, {1, 1, 1}};

    EXPECT_EQ(3, num_islands(grid1));
    EXPECT_EQ(1, num_islands(grid2));
}

} // namespace number_of_islands
