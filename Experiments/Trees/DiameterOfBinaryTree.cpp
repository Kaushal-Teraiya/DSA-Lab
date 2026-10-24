// ============================================================
// LeetCode #543 - Diameter of Binary Tree
// Difficulty: Easy
// Topics: Tree, DFS, Binary Tree
// ============================================================
//
// PROBLEM:
// Given the root of a binary tree, return the length of its
// diameter.
//
// The diameter is the length of the longest path between any
// two nodes. The path may or may not pass through the root.
// Path length is measured in EDGES.
//
// EXAMPLE 1:
// Input: root = [1,2,3,4,5]
// Output: 3
//
//        1
//       / \
//      2   3
//     / \
//    4   5
//
// EXAMPLE 2:
// Input: root = [1,2]
// Output: 1
//
// CONSTRAINTS:
// - The number of nodes is in the range [1, 10^4].
// - -100 <= Node.val <= 100
//
// APPROACH:
// TODO: Calculate subtree heights recursively.
// TODO: At each node, update diameter using leftHeight + rightHeight.
// TODO: Return 1 + max(leftHeight, rightHeight) from the helper.
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <algorithm>
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
    int diameter = 0;

    int height(TreeNode *root)
    {
        // Base case: nullptr has height 0.
        // Calculate left and right heights.
        // Update diameter.
        // Return the current node's height.

        if (root == nullptr)
            return 0;

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        diameter = max(diameter, leftHeight + rightHeight);

        return 1 + max(leftHeight, rightHeight);
    }

public:
    int diameterOfBinaryTree(TreeNode *root)
    {
        height(root);
        return diameter;
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
             int expected)
{
    TreeNode *root = buildTree(input);
    Solution solution;
    int actual = solution.diameterOfBinaryTree(root);

    cout << (actual == expected ? "PASS" : "FAIL")
         << " - " << name
         << " | Expected: " << expected
         << " | Actual: " << actual << '\n';

    deleteTree(root);
}

int main()
{
    cout << "========== TEST RESULTS ==========\n";

    runTest("Example 1", {1, 2, 3, 4, 5}, 3);
    runTest("Example 2", {1, 2}, 1);
    runTest("Single node", {1}, 0);
    runTest("Perfect binary tree", {1, 2, 3, 4, 5, 6, 7}, 4);
    runTest("Left-skewed tree", {1, 2, nullopt, 3, nullopt, 4}, 3);
    runTest("Deeper longest path", {1, 2, 3, 4, 5, nullopt, nullopt, 6, 7}, 4);

    cout << "==================================\n";
    cout << "DETAILED AUDIT — review any FAIL above.\n";

    return 0;
}
