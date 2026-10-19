
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// LeetCode #104 — Maximum Depth of Binary Tree
//
// Given the root of a binary tree, return its maximum depth.
//
// Maximum depth = number of nodes along the longest path
// from the root node down to the farthest leaf.
//
// Examples:
//     3           depth = 1
//
//     3           depth = 2
//    /
//   9
//
//       3         depth = 3
//      / \
//     9  20
//       /  \
//      15   7

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;

        return 1 + max(maxDepth(root->right), maxDepth(root->left));
    }
};

int main()
{
    Solution solution;

    // Test 4: Empty tree
    assert(solution.maxDepth(nullptr) == 0);
    cout << "Test 4 passed!\n";

    // Test 5: Root with only a left child
    {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);

        assert(solution.maxDepth(root) == 2);
        cout << "Test 5 passed!\n";
    }

    // Test 6: Root with only a right child
    {
        TreeNode *root = new TreeNode(1);
        root->right = new TreeNode(2);

        assert(solution.maxDepth(root) == 2);
        cout << "Test 6 passed!\n";
    }

    // Test 7: Left-skewed tree of depth 4
    {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->left->left = new TreeNode(3);
        root->left->left->left = new TreeNode(4);

        assert(solution.maxDepth(root) == 4);
        cout << "Test 7 passed!\n";
    }

    // Test 8: Right-skewed tree of depth 5
    {
        TreeNode *root = new TreeNode(1);
        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);
        root->right->right->right = new TreeNode(4);
        root->right->right->right->right = new TreeNode(5);

        assert(solution.maxDepth(root) == 5);
        cout << "Test 8 passed!\n";
    }

    // Test 9: Balanced tree of depth 3
    {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(5);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(7);

        assert(solution.maxDepth(root) == 3);
        cout << "Test 9 passed!\n";
    }

    // Test 10: Uneven tree — longest path is on the left
    {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);
        root->left->left->left = new TreeNode(5);

        assert(solution.maxDepth(root) == 4);
        cout << "Test 10 passed!\n";
    }

    // Test 11: Uneven tree — longest path is on the right
    {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->right->right = new TreeNode(4);
        root->right->right->right = new TreeNode(5);

        assert(solution.maxDepth(root) == 4);
        cout << "Test 11 passed!\n";
    }

    // Test 12: Root with two leaf children
    {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);

        assert(solution.maxDepth(root) == 2);
        cout << "Test 12 passed!\n";
    }

    // Test 13: Single-node tree with a negative value
    {
        TreeNode *root = new TreeNode(-10);

        assert(solution.maxDepth(root) == 1);
        cout << "Test 13 passed!\n";
    }

    return 0;
}
