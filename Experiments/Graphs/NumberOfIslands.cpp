#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
LeetCode 200: Number of Islands
Difficulty: Medium
Topic: Graphs - DFS / Grid Traversal

PROBLEM:
Given an m x n grid of '1's (land) and '0's (water),
return the number of islands.

An island is formed by connecting adjacent land cells
horizontally or vertically. You may assume all four
edges of the grid are surrounded by water.

EXAMPLE 1:
Input:
[
    ['1','1','0','0'],
    ['1','0','0','1'],
    ['0','0','1','1'],
    ['0','0','0','0']
]
Output: 2

EXAMPLE 2:
Input: [['1','1','1'],['0','1','0'],['1','1','1']]
Output: 1

EXAMPLE 3:
Input: [['0','0'],['0','0']]
Output: 0

CONSTRAINTS:
- 1 <= m, n <= 300
- grid[i][j] is either '0' or '1'
- Adjacent cells connect horizontally or vertically.
- Diagonal cells do not connect.

APPROACH TO EXPLORE:
Use DFS to explore all connected land cells.
Count each new, unexplored island once.

LeetCode signature:
int numIslands(vector<vector<char>>& grid)
*/

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int rows = grid.size();
        int cols = grid[0].size();
        int numberOfIslands = 0;

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == '1' && !visited[i][j])
                {
                    numberOfIslands++;
                    dfs(i, j, grid, visited);
                }
            }
        }
        return numberOfIslands;
    }

    void dfs(int row, int col, vector<vector<char>> &grid, vector<vector<bool>> &visited)
    {
        //out of bounds safety
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] == '0')
        {
            return;
        }

        if (visited[row][col]) // return if already visited the cell
            return;

        visited[row][col] = true; //else mark it true

        //classic up down left right DFS
        dfs(row + 1, col, grid, visited);
        dfs(row - 1, col, grid, visited);
        dfs(row, col + 1, grid, visited);
        dfs(row, col - 1, grid, visited);
    }
};

struct TestCase
{
    string name;
    vector<vector<char>> grid;
    int expected;
};

int main()
{
    vector<TestCase> tests = {
        {"Example 1",
         {{'1', '1', '0', '0'},
          {'1', '0', '0', '1'},
          {'0', '0', '1', '1'},
          {'0', '0', '0', '0'}},
         2},
        {"Example 2",
         {{'1', '1', '1'},
          {'0', '1', '0'},
          {'1', '1', '1'}},
         1},
        {"Example 3 - No land",
         {{'0', '0'}, {'0', '0'}},
         0},
        {"Single land cell",
         {{'1'}},
         1},
        {"Separate islands",
         {{'1', '0', '1'},
          {'0', '0', '0'},
          {'1', '0', '1'}},
         4}};

    Solution solution;
    int passed = 0;

    for (const auto &test : tests)
    {
        auto grid = test.grid; // Fresh copy for each test
        int actual = solution.numIslands(grid);

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
        int actual = solution.numIslands(grid);

        cout << (actual == test.expected ? "[PASS] " : "[FAIL] ")
             << test.name
             << " | Expected: " << test.expected
             << " | Actual: " << actual << '\n';
    }

    return passed == static_cast<int>(tests.size()) ? 0 : 1;
}
