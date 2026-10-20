#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// ============================================================
// PROBLEM: CLONE GRAPH - LeetCode #133
// ============================================================
//
// PST:
// Given a reference to a node in a connected, undirected graph,
// return a deep copy (clone) of the graph.
//
// Each node has an integer value and a list of neighbors.
// Every cloned node must be a NEW object, while preserving all
// connections and cycles.
//
// EXAMPLE:
// Input adjacency list: [[2,4],[1,3],[2,4],[1,3]]
// Output adjacency list: [[2,4],[1,3],[2,4],[1,3]]
//
// CONSTRAINTS:
// - 0 to 100 nodes
// - Node values are unique, from 1 to 100
// - No repeated edges or self-loops
// - The graph is connected when non-empty
//
// YOUR TASK:
// 1. Implement cloneGraph.
// 2. Preserve graph structure and cycles.
// 3. Ensure every original node gets exactly one clone.
// 4. Do not modify the original graph.
//
// LeetCode:
// https://leetcode.com/problems/clone-graph/
// ============================================================

class Node
{
public:
    int val;
    vector<Node *> neighbors;

    Node() : val(0) {}
    Node(int _val) : val(_val) {}
    Node(int _val, vector<Node *> _neighbors)
        : val(_val), neighbors(_neighbors) {}
};

class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        unordered_map<Node *, Node *> visited;
        queue<Node *> q;

        if (node == nullptr)
            return nullptr;

        Node *clone = new Node(node->val);
        visited[node] = clone;
        q.push(node);

        while (!q.empty())
        {
            /* code */
            Node *current = q.front();
            q.pop();

            for (Node *neighbor : current->neighbors)
            {
                if (visited.find(neighbor) == visited.end())
                {
                    Node *neighborClone = new Node(neighbor->val);
                    visited[neighbor] = neighborClone;
                    q.push(neighbor);
                }

                visited[current]->neighbors.push_back(visited[neighbor]);
            }
        }
        return clone;
    }
};

// Builds a graph from a 1-based adjacency list.
Node *buildGraph(const vector<vector<int>> &adj)
{
    if (adj.empty())
        return nullptr;

    vector<Node *> nodes(adj.size() + 1, nullptr);

    for (int i = 1; i <= (int)adj.size(); i++)
        nodes[i] = new Node(i);

    for (int i = 1; i <= (int)adj.size(); i++)
        for (int neighbor : adj[i - 1])
            nodes[i]->neighbors.push_back(nodes[neighbor]);

    return nodes[1];
}

// Serializes a graph into an adjacency list.
vector<vector<int>> serializeGraph(Node *start)
{
    if (!start)
        return {};

    unordered_set<Node *> visited;
    queue<Node *> q;
    vector<vector<int>> result;

    visited.insert(start);
    q.push(start);

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        if ((int)result.size() < current->val)
            result.resize(current->val);

        vector<int> neighbors;

        for (Node *neighbor : current->neighbors)
        {
            neighbors.push_back(neighbor->val);

            if (visited.insert(neighbor).second)
                q.push(neighbor);
        }

        result[current->val - 1] = neighbors;
    }

    return result;
}

// Verifies equivalent structure and distinct node objects.
bool isDeepClone(Node *original, Node *clone)
{
    if (!original || !clone)
        return original == clone;

    unordered_map<Node *, Node *> mapping;
    queue<pair<Node *, Node *>> q;

    mapping[original] = clone;
    q.push({original, clone});

    while (!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();

        if (a == b || a->val != b->val ||
            a->neighbors.size() != b->neighbors.size())
            return false;

        for (int i = 0; i < (int)a->neighbors.size(); i++)
        {
            Node *x = a->neighbors[i];
            Node *y = b->neighbors[i];

            if (x == y || x->val != y->val)
                return false;

            if (!mapping.count(x))
            {
                mapping[x] = y;
                q.push({x, y});
            }
            else if (mapping[x] != y)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    Solution solution;

    // TC1: Four-node cycle
    {
        vector<vector<int>> adj = {
            {2, 4}, {1, 3}, {2, 4}, {1, 3}};
        Node *original = buildGraph(adj);
        Node *clone = solution.cloneGraph(original);
        assert(clone && serializeGraph(clone) == adj);
        assert(isDeepClone(original, clone));
        cout << "TC1 passed: Four-node cycle\n";
    }

    // TC2: Single node
    {
        vector<vector<int>> adj = {{}};
        Node *original = buildGraph(adj);
        Node *clone = solution.cloneGraph(original);
        assert(clone && clone->val == 1);
        assert(clone->neighbors.empty());
        assert(isDeepClone(original, clone));
        cout << "TC2 passed: Single node\n";
    }

    // TC3: Two connected nodes
    {
        vector<vector<int>> adj = {{2}, {1}};
        Node *original = buildGraph(adj);
        Node *clone = solution.cloneGraph(original);
        assert(serializeGraph(clone) == adj);
        assert(isDeepClone(original, clone));
        cout << "TC3 passed: Two connected nodes\n";
    }

    // TC4: Triangle cycle
    {
        vector<vector<int>> adj = {{2, 3}, {1, 3}, {1, 2}};
        Node *original = buildGraph(adj);
        Node *clone = solution.cloneGraph(original);
        assert(serializeGraph(clone) == adj);
        assert(isDeepClone(original, clone));
        cout << "TC4 passed: Triangle cycle\n";
    }

    // TC5: Multiple paths and cycles
    {
        vector<vector<int>> adj = {
            {2, 3}, {1, 4}, {1, 4, 5}, {2, 3, 5}, {3, 4}};
        Node *original = buildGraph(adj);
        Node *clone = solution.cloneGraph(original);
        assert(serializeGraph(clone) == adj);
        assert(isDeepClone(original, clone));
        cout << "TC5 passed: Multiple paths and cycles\n";
    }

    // TC6: Empty graph
    {
        assert(solution.cloneGraph(nullptr) == nullptr);
        cout << "TC6 passed: Empty graph\n";
    }

    cout << "\nAll test cases passed!\n";
    return 0;
}
