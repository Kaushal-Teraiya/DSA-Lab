#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
LeetCode 695: Max Area of Island
Difficulty: Medium
Topic: Graphs - DFS / Grid Traversal

PROBLEM:
You are given an m x n binary grid. An island is a group
of 1s connected horizontally or vertically.

Return the maximum area of an island.
The area is the number of land cells in that island.
If there are no islands, return 0.

EXAMPLE 1:
Input:
[
    [0,0,1,0],
    [1,1,1,0],
    [0,1,0,1],
    [0,0,1,1]
]
Output: 4

EXAMPLE 2:
Input: [[0,0,0],[0,0,0]]
Output: 0

EXAMPLE 3:
Input: [[1,1,0],[1,0,0],[0,0,1]]
Output: 3

CONSTRAINTS:
- 1 <= m, n <= 50
- grid[i][j] is either 0 or 1
- Islands connect horizontally or vertically.
- Diagonal cells do not connect.

APPROACH TO EXPLORE:
Use DFS to explore each island.
Count the number of land cells in each island.
Return the largest area found.

LeetCode signature:
int maxAreaOfIsland(vector<vector<int>>& grid)
*/

class Solution
{
public:
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int rows = grid.size();
        int cols = grid[0].size();
        int maxArea = 0;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == 1 && !visited[i][j])
                {
                    maxArea = max(maxArea, dfs(i, j, grid, visited));
                }
            }
        }
        return maxArea;
    }

private:
    int dfs(int row, int col,
            vector<vector<int>> &grid,
            vector<vector<bool>> &visited)
    {

        if (row < 0 || row >= grid.size() ||
            col < 0 || col >= grid[0].size())
        {
            return 0;
        }

        if (visited[row][col] || grid[row][col] == 0)
            return 0;

        visited[row][col] = true;
        return 1 + dfs(row + 1, col, grid, visited) + dfs(row - 1, col, grid, visited) + dfs(row, col + 1, grid, visited) + dfs(row, col - 1, grid, visited);
    }
};

struct TestCase
{
    string name;
    vector<vector<int>> grid;
    int expected;
};

int main()
{
    vector<TestCase> tests = {
        {"Example 1",
         {{0, 0, 1, 0},
          {1, 1, 1, 0},
          {0, 1, 0, 1},
          {0, 0, 1, 1}},
         5},
        {"No islands",
         {{0, 0, 0}, {0, 0, 0}},
         0},
        {"Example 3",
         {{1, 1, 0}, {1, 0, 0}, {0, 0, 1}},
         3},
        {"Entire grid is land",
         {{1, 1}, {1, 1}},
         4},
        {"Separate islands",
         {{1, 0, 1},
          {0, 0, 0},
          {1, 0, 1}},
         1}};

    Solution solution;
    int passed = 0;

    for (const auto &test : tests)
    {
        auto grid = test.grid;
        int actual = solution.maxAreaOfIsland(grid);

        if (actual == test.expected)
        {
            passed++;
        }
    }

    cout << "========== TEST SUMMARY ==========\n";
    cout << "Passed: " << passed << "/" << tests.size() << "\n";
    cout << "Failed: " << tests.size() - passed << "/" << tests.size() << "\n";

    cout << "\n========== TEST DETAILS ==========\n";
    for (const auto &test : tests)
    {
        auto grid = test.grid;
        int actual = solution.maxAreaOfIsland(grid);

        cout << (actual == test.expected ? "[PASS] " : "[FAIL] ")
             << test.name
             << " | Expected: " << test.expected
             << " | Actual: " << actual << '\n';
    }

    return passed == static_cast<int>(tests.size()) ? 0 : 1;
}
