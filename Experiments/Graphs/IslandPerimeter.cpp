#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
LeetCode 463: Island Perimeter
Difficulty: Easy
Topic: Graphs - Grid Traversal

PROBLEM:
You are given an m x n grid where 1 represents land
and 0 represents water. There is exactly one island.
Return its perimeter. Land connects horizontally
or vertically, not diagonally.

EXAMPLE:
Input:
{{0,1,0,0},
 {1,1,1,0},
 {0,1,0,0}}
Output: 12

CONSTRAINTS:
- 1 <= rows, cols <= 100
- grid[i][j] is 0 or 1
- Exactly one island exists.

LeetCode signature:
int islandPerimeter(vector<vector<int>>& grid)
*/

class Solution
{
public:
    int islandPerimeter(vector<vector<int>> &grid)
    {
        int rows = grid.size();
        int cols = grid[0].size();

        int perimeter = 0;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == 0) // dont count 0 perimeter stays the same
                    continue;

                    //for every 1 perimeter increases by 4
                perimeter += 4;

                //for every adjacent box with 1 , subtract 1 perimeter.
                if (i > 0 && grid[i - 1][j] == 1)
                {
                    perimeter--;
                }

                if (i < rows - 1 && grid[i + 1][j] == 1)
                {
                    perimeter--;
                }

                if (j > 0 && grid[i][j - 1] == 1)
                {
                    perimeter--;
                }

                if (j < cols - 1 && grid[i][j + 1] == 1)
                {
                    perimeter--;
                }
            }
        }

        return perimeter; //return ans
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
        {"Plus-shaped island",
         {{0, 1, 0, 0},
          {1, 1, 1, 0},
          {0, 1, 0, 0}},
         12},
        {"Single land cell", {{1}}, 4},
        {"Two adjacent cells", {{1, 1}}, 6},
        {"Single row of land", {{1, 1, 1, 1, 1}}, 12},
        {"All water", {{0, 0}, {0, 0}}, 0}};

    Solution solution;
    int passed = 0;

    for (const auto &test : tests)
    {
        auto grid = test.grid;
        if (solution.islandPerimeter(grid) == test.expected)
            passed++;
    }

    cout << "========== TEST SUMMARY ==========\n";
    cout << "Passed: " << passed << "/" << tests.size() << "\n";
    cout << "Failed: " << tests.size() - passed << "/" << tests.size() << "\n";

    cout << "\n========== TEST DETAILS ==========\n";
    for (const auto &test : tests)
    {
        auto grid = test.grid;
        int actual = solution.islandPerimeter(grid);
        cout << (actual == test.expected ? "[PASS] " : "[FAIL] ")
             << test.name << " | Expected: " << test.expected
             << " | Actual: " << actual << '\n';
    }

    return passed == static_cast<int>(tests.size()) ? 0 : 1;
}
