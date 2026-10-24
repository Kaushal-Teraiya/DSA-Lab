// ============================================================
// LeetCode #104 - Maximum Depth of Binary Tree
// Difficulty: Easy
// Topics: Tree, Depth-First Search, Breadth-First Search
// ============================================================
//
// PROBLEM STATEMENT:
// Given the root of a binary tree, return its maximum depth.
//
// The maximum depth is the number of nodes along the longest
// path from the root node down to the farthest leaf node.
//
// EXAMPLE 1:
// Input: root = [3,9,20,null,null,15,7]
// Output: 3
//
//        3
//       / \
//      9  20
//         / \
//        15  7
//
// EXAMPLE 2:
// Input: root = [1,null,2]
// Output: 2
//
// EXAMPLE 3:
// Input: root = []
// Output: 0
//
// CONSTRAINTS:
// - The number of nodes is in the range [0, 10^4].
// - -100 <= Node.val <= 100
//
// ============================================================
// APPROACH NOTES:
// TODO: Derive the recursive relationship yourself.
// Hint: What should the depth be for an empty tree?
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <algorithm>
using namespace std;

// LeetCode-provided structure
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r)
        : val(x), left(l), right(r) {}
};

class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        // TODO: Implement your solution.
        if (root == nullptr)
            return 0;

        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};

// ============================================================
// LOCAL TEST HELPERS
// These helpers are for local practice, not LeetCode submission.
// ============================================================

TreeNode *buildTree(const vector<optional<int>> &values)
{
    if (values.empty() || !values[0].has_value())
        return nullptr;

    TreeNode *root = new TreeNode(*values[0]);
    queue<TreeNode *> q;
    q.push(root);

    size_t i = 1;

    while (!q.empty() && i < values.size())
    {
        TreeNode *node = q.front();
        q.pop();

        if (i < values.size() && values[i].has_value())
        {
            node->left = new TreeNode(*values[i]);
            q.push(node->left);
        }
        ++i;

        if (i < values.size() && values[i].has_value())
        {
            node->right = new TreeNode(*values[i]);
            q.push(node->right);
        }
        ++i;
    }

    return root;
}

void deleteTree(TreeNode *root)
{
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void runTest(const char *name,
             const vector<optional<int>> &input,
             int expected)
{
    TreeNode *root = buildTree(input);
    Solution solution;
    int actual = solution.maxDepth(root);

    cout << name << ": "
         << (actual == expected ? "PASS" : "FAIL")
         << " | Expected: " << expected
         << " | Actual: " << actual << '\n';

    deleteTree(root);
}

int main()
{
    runTest("Test 1 - Balanced tree",
            {3, 9, 20, nullopt, nullopt, 15, 7}, 3);

    runTest("Test 2 - Single-sided tree",
            {1, nullopt, 2}, 2);

    runTest("Test 3 - Empty tree",
            {}, 0);

    runTest("Test 4 - Single node",
            {7}, 1);

    runTest("Test 5 - Left-skewed tree",
            {1, 2, nullopt, 3, nullopt, 4}, 4);

    runTest("Test 6 - Complete tree",
            {1, 2, 3, 4, 5, 6, 7}, 3);

    return 0;
}
