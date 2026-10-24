// ============================================================
// LeetCode #100 - Same Tree
// Difficulty: Easy
// Topics: Tree, Depth-First Search, Binary Tree
// ============================================================
//
// PROBLEM STATEMENT:
// Given the roots of two binary trees p and q, write a function
// to check if they are the same or not.
//
// Two binary trees are considered the same if they are
// structurally identical and the nodes have the same values.
//
// EXAMPLE 1:
// Input: p = [1,2,3], q = [1,2,3]
// Output: true
//
// EXAMPLE 2:
// Input: p = [1,2], q = [1,null,2]
// Output: false
//
// EXAMPLE 3:
// Input: p = [1,2,1], q = [1,1,2]
// Output: false
//
// CONSTRAINTS:
// - The number of nodes in both trees is in the range [0, 100].
// - -10^4 <= Node.val <= 10^4
//
// ============================================================
// APPROACH NOTES:
// TODO: Determine the base cases.
// TODO: Compare current node values.
// TODO: Recursively compare corresponding left and right subtrees.
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <optional>
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
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        // TODO: Implement your recursive solution.
        if (p == nullptr && q == nullptr)
        {
            return true;
        }

        if (p == nullptr || q == nullptr)
        {
            return false;
        }

        if (p->val != q->val)
        {
            return false;
        }

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
             const vector<optional<int>> &pValues,
             const vector<optional<int>> &qValues,
             bool expected)
{
    TreeNode *p = buildTree(pValues);
    TreeNode *q = buildTree(qValues);

    Solution solution;
    bool actual = solution.isSameTree(p, q);

    cout << name << ": "
         << (actual == expected ? "PASS" : "FAIL")
         << " | Expected: " << boolalpha << expected
         << " | Actual: " << actual << '\n';

    deleteTree(p);
    deleteTree(q);
}

int main()
{
    runTest("Test 1 - Identical trees",
            {1, 2, 3}, {1, 2, 3}, true);

    runTest("Test 2 - Different structure",
            {1, 2}, {1, nullopt, 2}, false);

    runTest("Test 3 - Different values",
            {1, 2, 1}, {1, 1, 2}, false);

    runTest("Test 4 - Both empty",
            {}, {}, true);

    runTest("Test 5 - One empty",
            {1}, {}, false);

    runTest("Test 6 - Different deeper structure",
            {1, 2, 3, 4}, {1, 2, 3, nullopt, 4}, false);

    runTest("Test 7 - Identical negative values",
            {-1, -2, 3}, {-1, -2, 3}, true);

    return 0;
}
