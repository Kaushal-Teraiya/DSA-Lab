/*
    LeetCode 1971: Find if Path Exists in Graph
    Difficulty: Easy
    Topics: Graph, DFS, BFS

    PROBLEM STATEMENT
    -----------------
    There is a bi-directional graph with n vertices, where each vertex
    is labeled from 0 to n - 1.

    The edges are given as a 2D integer array edges, where
    edges[i] = [ui, vi] indicates that there is an edge between
    vertices ui and vi.

    Given source and destination, return true if there is a valid
    path from source to destination, or false otherwise.

    EXAMPLE 1
    ---------
    Input:
    n = 3
    edges = [[0,1],[1,2]]
    source = 0
    destination = 2

    Output: true

    Explanation: There is a path from 0 to 2: 0 -> 1 -> 2.

    EXAMPLE 2
    ---------
    Input:
    n = 6
    edges = [[0,1],[0,2],[3,5],[5,4],[4,3]]
    source = 0
    destination = 5

    Output: false

    Explanation: There is no path between 0 and 5.

    CONSTRAINTS
    -----------
    1 <= n <= 2 * 10^5
    0 <= edges.length <= 2 * 10^5
    edges[i].length == 2
    0 <= ui, vi <= n - 1
    ui != vi
    0 <= source, destination <= n - 1
    There are no duplicate edges.
    There are no self-edges.

    APPROACH NOTES
    --------------
    Think about:
    - How to represent the graph using an adjacency list.
    - How DFS or BFS explores connected vertices.
    - Why a visited array is necessary.
    - When the destination has been found.

    COMPLEXITY
    ----------
    Time: O(n + m), where m is the number of edges.
    Space: O(n + m).
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    bool validPath(int n, vector<vector<int>> &edges,
                   int source, int destination)
    {
        // make adjacency list with n nodes.
        vector<vector<int>> adj(n);
        vector<bool> visited(n, false);

        // iterate over edges.
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            // store both in adj list.
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        //call dfs func
        return dfs(n, adj, source, destination , visited);
    }

    bool dfs(int n, vector<vector<int>> &adj, int node, int destination, vector<bool> &visited)
    {
        //if we reached the destination return true
        if (node == destination)
        {
            return true;
        }

        //mark the node visited
        visited[node] = true;

        //explore its neighbors
        for (auto neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                if (dfs(n, adj, neighbor, destination, visited))
                {
                    return true;
                }
            }
        }

        return false;
    }
};

// ==================== TEST HARNESS ====================

struct TestCase
{
    int n;
    vector<vector<int>> edges;
    int source;
    int destination;
    bool expected;
    string name;
};

int main()
{
    vector<TestCase> tests = {
        {3, {{0, 1}, {1, 2}}, 0, 2, true, "Example 1: path exists"},

        {6, {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}}, 0, 5, false, "Example 2: disconnected components"},

        {1, {}, 0, 0, true, "Single node: source equals destination"},

        {4, {{0, 1}, {2, 3}}, 0, 1, true, "Direct path"},

        {4, {{0, 1}, {2, 3}}, 0, 3, false, "Disconnected components"},

        {5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}}, 0, 4, true, "Long chain"}};

    int passed = 0;
    int failed = 0;

    for (const auto &test : tests)
    {
        Solution solution;
        auto edges = test.edges;

        bool actual = solution.validPath(
            test.n, edges, test.source, test.destination);

        if (actual == test.expected)
        {
            ++passed;
            cout << "[PASS] " << test.name << '\n';
        }
        else
        {
            ++failed;
            cout << "[FAIL] " << test.name
                 << " | Expected: " << boolalpha << test.expected
                 << " | Got: " << actual << '\n';
        }
    }

    cout << "\n========== Test Summary ==========\n";
    cout << "Passed: " << passed << '\n';
    cout << "Failed: " << failed << '\n';
    cout << "Total:  " << tests.size() << '\n';

    return failed == 0 ? 0 : 1;
}
