#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// ============================================================
// PROBLEM: INVERT BINARY TREE
// LeetCode #226
// ============================================================
//
// PST (Problem Statement):
//
// Given the root of a binary tree, invert the tree and return
// its root.
//
// Inverting a binary tree means swapping the left and right
// children of every node.
//
// EXAMPLE 1:
//
// Input:
//       4
//      / \
//     2   7
//    / \ / \
//   1  3 6  9
//
// Output:
//       4
//      / \
//     7   2
//    / \ / \
//   9  6 3  1
//
// EXAMPLE 2:
// Input:  [2,1,3]
// Output: [2,3,1]
//
// EXAMPLE 3:
// Input:  []
// Output: []
//
// CONSTRAINTS:
// - Number of nodes: [0, 100]
// -100 <= Node.val <= 100
//
// LeetCode:
// https://leetcode.com/problems/invert-binary-tree/
//
// ============================================================
// YOUR TASK:
// 1. Implement invertTree().
// 2. Run all test cases.
// 3. Analyze time and auxiliary space complexity.
// ============================================================

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
    TreeNode *invertTree(TreeNode *root)
    {
        // TODO: Implement your solution.
        if (root == nullptr)
            return nullptr;

        TreeNode *tempNode = root->right;
        root->right = root->left;
        root->left = tempNode;

        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};

// ============================================================
// TEST CASE HELPER: LEVEL-ORDER TRAVERSAL
// ============================================================

vector<int> levelOrder(TreeNode *root)
{
    vector<int> result;

    if (root == nullptr)
    {
        return result;
    }

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();

        result.push_back(node->val);

        if (node->left != nullptr)
            q.push(node->left);
        if (node->right != nullptr)
            q.push(node->right);
    }

    return result;
}

int main()
{
    Solution solution;

    // TC1: Empty tree
    assert(solution.invertTree(nullptr) == nullptr);
    cout << "TC1 passed: Empty tree\n";

    // TC2: Single node
    {
        TreeNode *root = new TreeNode(1);
        TreeNode *result = solution.invertTree(root);

        assert((levelOrder(result) == vector<int>{1}));
        cout << "TC2 passed: Single node\n";
    }

    // TC3: Root with two children
    // Original: [2,1,3]
    // Expected: [2,3,1]
    {
        TreeNode *root = new TreeNode(2);
        root->left = new TreeNode(1);
        root->right = new TreeNode(3);

        TreeNode *result = solution.invertTree(root);

        assert((levelOrder(result) == vector<int>{2, 3, 1}));
        cout << "TC3 passed: Two children\n";
    }

    // TC4: Complete binary tree
    // Original: [4,2,7,1,3,6,9]
    // Expected: [4,7,2,9,6,3,1]
    {
        TreeNode *root = new TreeNode(4);
        root->left = new TreeNode(2);
        root->right = new TreeNode(7);
        root->left->left = new TreeNode(1);
        root->left->right = new TreeNode(3);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(9);

        TreeNode *result = solution.invertTree(root);

        assert((levelOrder(result) ==
                vector<int>{4, 7, 2, 9, 6, 3, 1}));
        cout << "TC4 passed: Complete tree\n";
    }

    // TC5: Left-only chain
    {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->left->left = new TreeNode(3);

        TreeNode *result = solution.invertTree(root);

        assert(result->right != nullptr);
        assert(result->right->val == 2);
        assert(result->right->left == nullptr);
        assert(result->right->right != nullptr);
        assert(result->right->right->val == 3);

        cout << "TC5 passed: Left-only chain\n";
    }

    // TC6: Right-only chain
    {
        TreeNode *root = new TreeNode(1);
        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);

        TreeNode *result = solution.invertTree(root);

        assert(result->left != nullptr);
        assert(result->left->val == 2);
        assert(result->left->left != nullptr);
        assert(result->left->left->val == 3);
        assert(result->left->right == nullptr);

        cout << "TC6 passed: Right-only chain\n";
    }

    // TC7: Negative values
    {
        TreeNode *root = new TreeNode(-1);
        root->left = new TreeNode(-2);
        root->right = new TreeNode(-3);

        TreeNode *result = solution.invertTree(root);

        assert((levelOrder(result) == vector<int>{-1, -3, -2}));
        cout << "TC7 passed: Negative values\n";
    }

    // TC8: Uneven tree
    // Original:
    //     1
    //    / \
    //   2   3
    //  /
    // 4
    {
        TreeNode *root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);

        TreeNode *result = solution.invertTree(root);

        assert((levelOrder(result) == vector<int>{1, 3, 2, 4}));
        cout << "TC8 passed: Uneven tree\n";
    }

    cout << "\nAll test cases passed!\n";
    return 0;
}
