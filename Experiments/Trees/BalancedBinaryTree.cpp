// ============================================================
// LeetCode #110 - Balanced Binary Tree
// Difficulty: Easy
// Topics: Tree, DFS, Binary Tree
// ============================================================
//
// PROBLEM:
// Given the root of a binary tree, determine if it is height-balanced.
//
// A height-balanced tree is one where the left and right subtree
// heights of EVERY node differ by no more than 1.
//
// EXAMPLE 1:
// Input: root = [3,9,20,null,null,15,7]
// Output: true
//
//        3
//       / \
//      9   20
//         /  \
//        15   7
//
// EXAMPLE 2:
// Input: root = [1,2,2,3,3,null,null,4,4]
// Output: false
//
// EXAMPLE 3:
// Input: root = []
// Output: true
//
// CONSTRAINTS:
// - The number of nodes is in the range [0, 5000].
// - -10^4 <= Node.val <= 10^4
//
// APPROACH:
// TODO: Implement height() recursively.
// TODO: Check the height difference at every node.
// TODO: Ensure both subtrees are balanced.
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <algorithm>
#include <cstdlib>
using namespace std;

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
    int height(TreeNode *root)
    {
        // TODO: Return 0 for nullptr.
        // TODO: Return 1 + max(left height, right height).

        if (root == nullptr)
            return 0;

        return 1 + max(height(root->left), height(root->right));
    }

public:
    bool isBalanced(TreeNode *root)
    {
        // TODO: Handle nullptr.
        // TODO: Calculate left and right heights.
        // TODO: Check if their difference is at most 1.
        // TODO: Recursively check both subtrees.
        if (root == nullptr)
            return true;

        // height difference should be atmost 1
        // isBalanced(root->left) checks the same for all the subtress of the current node.
        // same with isBalanced(root->right);
        return abs(height(root->left) - height(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
};

// ============================================================
// LOCAL TEST HELPERS — not part of LeetCode submission
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
             bool expected)
{
    TreeNode *root = buildTree(input);
    Solution solution;
    bool actual = solution.isBalanced(root);

    cout << (actual == expected ? "PASS" : "FAIL")
         << " - " << name
         << " | Expected: " << boolalpha << expected
         << " | Actual: " << actual << '\n';

    deleteTree(root);
}

int main()
{
    cout << "========== TEST RESULTS ==========\n";

    runTest("Example 1 - Balanced tree",
            {3, 9, 20, nullopt, nullopt, 15, 7}, true);

    runTest("Example 2 - Unbalanced tree",
            {1, 2, 2, 3, 3, nullopt, nullopt, 4, 4}, false);

    runTest("Example 3 - Empty tree",
            {}, true);

    runTest("Single node",
            {1}, true);

    runTest("Two-node tree",
            {1, 2}, true);

    runTest("Unbalanced left-skewed tree",
            {1, 2, nullopt, 3, nullopt, 4}, false);

    runTest("Balanced complete tree",
            {1, 2, 3, 4, 5, 6, 7}, true);

    cout << "==================================\n";
    cout << "DETAILED AUDIT — review any FAIL above.\n";

    return 0;
}
