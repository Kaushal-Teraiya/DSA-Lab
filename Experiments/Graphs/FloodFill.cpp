/*
========================================================
LeetCode #733 - Flood Fill
Difficulty: Easy
Topic: Graphs, DFS, BFS, 2D Grid
========================================================

PROBLEM STATEMENT
-----------------
You are given an image represented by an m x n integer
grid, where image[i][j] represents the pixel color.

You are also given three integers:
- sr: starting row
- sc: starting column
- color: the new color to apply

Perform a flood fill starting from image[sr][sc].

To perform a flood fill:
1. Start at the given pixel.
2. Change its color to the new color.
3. Change the color of all 4-directionally connected
   pixels that have the same original color.
4. Continue until no more qualifying neighboring pixels
   remain.

Return the modified image.

EXAMPLE 1
---------
Input:
image = {
    {1, 1, 1},
    {1, 1, 0},
    {1, 0, 1}
}
sr = 1, sc = 1, color = 2

Output:
{
    {2, 2, 2},
    {2, 2, 0},
    {2, 0, 1}
}

Explanation:
Starting at (1, 1), all connected pixels with original
color 1 are changed to color 2.
The bottom-right pixel remains 1 because it is not
4-directionally connected to the starting region.

EXAMPLE 2
---------
Input:
image = {
    {0, 0, 0},
    {0, 0, 0}
}
sr = 0, sc = 0, color = 0

Output:
{
    {0, 0, 0},
    {0, 0, 0}
}

Explanation:
The starting pixel already has the requested color,
so the image remains unchanged.

CONSTRAINTS
-----------
- m == image.length
- n == image[i].length
- 1 <= m, n <= 50
- 0 <= image[i][j], color < 2^16
- 0 <= sr < m
- 0 <= sc < n

IMPORTANT
---------
Only horizontal and vertical neighbors count.
Diagonal neighbors are NOT connected for flood fill.

APPROACH HINT
-------------
Think of each pixel as a node in a graph.

1. Remember the original color of the starting pixel.
2. Explore its 4 neighbors: up, down, left, right.
3. Only continue into a neighbor if:
   - It is inside the grid.
   - Its color matches the original color.
4. Change qualifying pixels to the new color.

Watch out for the case where the original color already
equals the new color. Avoid infinite recursion!

Your task: implement floodFill().

========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> floodFill(
        vector<vector<int>> &image,
        int sr,
        int sc,
        int color)
    {
        // we only care if the given start row and start column are different than the given color.
        if (image[sr][sc] == color)
            return image;

        int originalColor = image[sr][sc];

        dfs(image, sr, sc, originalColor, color);
        return image;
    }

    void dfs(vector<vector<int>> &image, int row, int col, int originalColor, int color)
    {
        //row and col should stay in bounds
        if (row < 0 || row >= image.size() || col < 0 || col >= image[0].size())
        {
            return;
        }

        //the pixel should be equal to original color to be processed
        if (image[row][col] != originalColor)
            return;

            //if it is then just change its color
        if (image[row][col] == originalColor)
        {
            image[row][col] = color;
        }

        //explore all directions left right up down and process those pixels
        dfs(image, row - 1, col, originalColor, color); // Up
        dfs(image, row + 1, col, originalColor, color); // Down
        dfs(image, row, col - 1, originalColor, color); // Left
        dfs(image, row, col + 1, originalColor, color); // Right
    }
};

// -------------------- TEST HARNESS --------------------

struct TestCase
{
    string name;
    vector<vector<int>> image;
    int sr;
    int sc;
    int color;
    vector<vector<int>> expected;
};

void printImage(const vector<vector<int>> &image)
{
    for (const auto &row : image)
    {
        cout << "[ ";
        for (int pixel : row)
        {
            cout << pixel << " ";
        }
        cout << "]\n";
    }
}

int main()
{
    vector<TestCase> tests = {
        {"Example 1",
         {{1, 1, 1},
          {1, 1, 0},
          {1, 0, 1}},
         1,
         1,
         2,
         {{2, 2, 2},
          {2, 2, 0},
          {2, 0, 1}}},
        {"Color already matches",
         {{0, 0, 0},
          {0, 0, 0}},
         0,
         0,
         0,
         {{0, 0, 0},
          {0, 0, 0}}},
        {"Single pixel",
         {{5}},
         0,
         0,
         9,
         {{9}}},
        {"Disconnected same-color region",
         {{1, 0, 0},
          {0, 0, 1},
          {0, 0, 1}},
         0,
         0,
         3,
         {{3, 0, 0},
          {0, 0, 1},
          {0, 0, 1}}},
        {"Fill entire image",
         {{4, 4},
          {4, 4}},
         0,
         0,
         7,
         {{7, 7},
          {7, 7}}}};

    Solution solution;
    int passed = 0;

    for (const auto &test : tests)
    {
        vector<vector<int>> input = test.image;
        auto actual = solution.floodFill(
            input, test.sr, test.sc, test.color);

        if (actual == test.expected)
        {
            passed++;
        }
    }

    cout << "========== TEST SUMMARY ==========\n";
    cout << "Passed: " << passed << "/" << tests.size() << "\n";
    cout << "Failed: " << tests.size() - passed << "/" << tests.size() << "\n";
    cout << "==================================\n\n";

    for (const auto &test : tests)
    {
        vector<vector<int>> input = test.image;
        auto actual = solution.floodFill(
            input, test.sr, test.sc, test.color);

        cout << test.name << ": "
             << (actual == test.expected ? "PASS" : "FAIL") << "\n";

        if (actual != test.expected)
        {
            cout << "Expected:\n";
            printImage(test.expected);
            cout << "Actual:\n";
            printImage(actual);
        }

        cout << "\n";
    }

    return passed == static_cast<int>(tests.size()) ? 0 : 1;
}
