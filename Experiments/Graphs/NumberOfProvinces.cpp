/*
========================================================
LeetCode #547 - Number of Provinces
Difficulty: Medium
Topic: Graphs, DFS / BFS
========================================================

PROBLEM STATEMENT
-----------------
There are n cities. Some of them are connected, while
some are not. If city A is connected directly to city B,
and city B is connected directly to city C, then A and C
belong to the same province.

A province is a group of directly or indirectly connected
cities, with no cities outside that group connected to it.

You are given an n x n matrix isConnected, where:
- isConnected[i][j] = 1 means cities i and j are connected.
- isConnected[i][j] = 0 means cities i and j are not
  directly connected.

Return the total number of provinces.

EXAMPLE 1
---------
Input:
{
    {1, 1, 0},
    {1, 1, 0},
    {0, 0, 1}
}

Output: 2

Explanation:
Cities 0 and 1 belong to one province.
City 2 forms another province.

EXAMPLE 2
---------
Input:
{
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
}

Output: 3

Explanation:
No two different cities are connected, so every city
forms its own province.

EXAMPLE 3
---------
Input:
{
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
}

Output: 1

Explanation:
Every city is connected to every other city.

CONSTRAINTS
-----------
- 1 <= n <= 200
- n == isConnected.size()
- n == isConnected[i].size()
- isConnected[i][j] is 0 or 1.
- isConnected[i][i] == 1.
- isConnected[i][j] == isConnected[j][i].

APPROACH HINT
-------------
Think of each city as a node in a graph.

1. Maintain a visited array.
2. Loop through every city.
3. When you find an unvisited city, you have found
   a new province.
4. Increment the province count and explore all cities
   reachable from it using DFS or BFS.
5. Continue until every city has been considered.

Your task: implement findCircleNum().

========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;

        for (int i = 0; i < n; i++)
        {
            // Initially visited bool vector is false so it will enter for city 0.
            if (!visited[i])
            {
                dfs(i, isConnected, visited, n);
                provinces++; // found one province
            }
        }
        return provinces;
    }

    void dfs(int city, vector<vector<int>> &isConnected, vector<bool> &visited, int n)
    {
        visited[city] = true; // 0 is marked true

        for (int i = 0; i < n; i++)
        // now it checks if 0 is connected to all nodes and if those nodes are not yet visited.
        // run dfs on those nodes as well and mark them true if not visited;
        {
            if (isConnected[city][i] && !visited[i])
            {
                dfs(i, isConnected, visited, n);
            }
        }
    }
};

// -------------------- TEST HARNESS --------------------

struct TestCase
{
    string name;
    vector<vector<int>> isConnected;
    int expected;
};

int main()
{
    vector<TestCase> tests = {
        {"Two provinces",
         {{1, 1, 0},
          {1, 1, 0},
          {0, 0, 1}},
         2},
        {"Every city is isolated",
         {{1, 0, 0},
          {0, 1, 0},
          {0, 0, 1}},
         3},
        {"All cities connected",
         {{1, 1, 1},
          {1, 1, 1},
          {1, 1, 1}},
         1},
        {"Single city",
         {{1}},
         1},
        {"Two separate groups",
         {{1, 1, 0, 0},
          {1, 1, 0, 0},
          {0, 0, 1, 1},
          {0, 0, 1, 1}},
         2}};

    Solution solution;
    int passed = 0;

    for (const auto &test : tests)
    {
        vector<vector<int>> input = test.isConnected;
        int actual = solution.findCircleNum(input);

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
        vector<vector<int>> input = test.isConnected;
        int actual = solution.findCircleNum(input);

        cout << test.name << "\n";
        cout << "Expected: " << test.expected
             << " | Actual: " << actual
             << " | " << (actual == test.expected ? "PASS" : "FAIL")
             << "\n\n";
    }

    return passed == static_cast<int>(tests.size()) ? 0 : 1;
}
