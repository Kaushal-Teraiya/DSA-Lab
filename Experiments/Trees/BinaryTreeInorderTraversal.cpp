// ============================================================
// LeetCode #94 - Binary Tree Inorder Traversal
// Difficulty: Easy
// Topics: Tree, Depth-First Search, Binary Tree
// ============================================================
//
// PROBLEM STATEMENT:
// Given the root of a binary tree, return the inorder traversal
// of its node values.
//
// EXAMPLE 1:
// Input: root = [1,null,2,3]
// Output: [1,3,2]
//
// EXAMPLE 2:
// Input: root = [1,2,3,4,5]
// Output: [4,2,5,1,3]
//
// EXAMPLE 3:
// Input: root = []
// Output: []
//
// CONSTRAINTS:
// - The number of nodes in the range [0, 100].
// - -100 <= Node.val <= 100
//
// ============================================================
// APPROACH:
// Inorder traversal follows:
// Left Subtree -> Root -> Right Subtree
//
// TODO: Implement the recursive solution yourself.
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <cassert>
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
    vector<int> inorderTraversal(TreeNode *root)
    {
        // TODO: Implement your solution here.
        // Return the node values in Left -> Root -> Right order.
        vector<int> ans;
        inorder(root, ans);
        return ans;
    }

    void inorder(TreeNode *root, vector<int> &ans)
    {
        if (root == nullptr)
            return;

        inorder(root->left, ans);
        ans.push_back(root->val);
        inorder(root->right, ans);
    }
};

// ============================================================
// LOCAL TEST HELPERS
// These are for your own practice; LeetCode provides its own
// TreeNode and test runner, so don't submit these helpers.
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

void runTest(
    const char *name,
    const vector<optional<int>> &input,
    const vector<int> &expected)
{
    TreeNode *root = buildTree(input);
    Solution solution;
    vector<int> actual = solution.inorderTraversal(root);

    cout << name << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Expected: ";
        for (int x : expected)
            cout << x << ' ';
        cout << "\nActual:   ";
        for (int x : actual)
            cout << x << ' ';
        cout << '\n';
    }

    deleteTree(root);
}

int main()
{
    runTest("Test 1 - Balanced tree",
            {1, 2, 3, 4, 5},
            {4, 2, 5, 1, 3});

    runTest("Test 2 - Right subtree",
            {1, nullopt, 2, 3},
            {1, 3, 2});

    runTest("Test 3 - Empty tree",
            {},
            {});

    runTest("Test 4 - Single node",
            {7},
            {7});

    runTest("Test 5 - Left-skewed tree",
            {3, 2, nullopt, 1},
            {1, 2, 3});

    runTest("Test 6 - Negative values",
            {0, -2, 5, -3, -1},
            {-3, -2, -1, 0, 5});

    return 0;
}
