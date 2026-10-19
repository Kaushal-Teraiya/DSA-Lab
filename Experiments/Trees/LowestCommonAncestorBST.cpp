#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// ============================================================
// PROBLEM: LOWEST COMMON ANCESTOR OF A BINARY SEARCH TREE
// LeetCode #235
// ============================================================
//
// PST (Problem Statement):
//
// Given a binary search tree (BST) and two nodes p and q,
// find their lowest common ancestor (LCA).
//
// The lowest common ancestor is the lowest node in the tree
// that has both p and q as descendants. A node can be a
// descendant of itself.
//
// BST PROPERTY:
// - Values smaller than a node are in its left subtree.
// - Values larger than a node are in its right subtree.
//
// EXAMPLE 1:
//
//         6
//        / \
//       2   8
//      / \ / \
//     0  4 7  9
//       / \
//      3   5
//
// Input: p = 2, q = 8
// Output: 6
//
// EXAMPLE 2:
//
//         6
//        / \
//       2   8
//      / \ / \
//     0  4 7  9
//       / \
//      3   5
//
// Input: p = 2, q = 4
// Output: 2
//
// CONSTRAINTS:
// - Number of nodes: [2, 10^5]
// - -10^9 <= Node.val <= 10^9
// - All Node.val values are unique.
// - p and q are different and both exist in the BST.
//
// LeetCode:
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
//
// ============================================================
// YOUR TASK:
// 1. Implement lowestCommonAncestor().
// 2. Use the BST property.
// 3. Run all test cases.
// 4. Analyze time and auxiliary space complexity.
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
    TreeNode *lowestCommonAncestor(TreeNode *root,
                                   TreeNode *p,
                                   TreeNode *q)
    {
        // TODO: Implement your solution.

        if (root == nullptr)
            return nullptr;

        if (p->val == root->val || q->val == root->val)
        {
            return root;
        }

        if ((p->val < root->val && q->val > root->val) || (p->val > root->val && q->val < root->val))
        {
            return root;
        }

        if (p->val < root->val && q->val < root->val)
        {
            return lowestCommonAncestor(root->left, p, q);
        }

        if (p->val > root->val && q->val > root->val)
        {
            return lowestCommonAncestor(root->right, p, q);
        }

        return nullptr;
    }
};

// ============================================================
// TEST CASES (TC)
// ============================================================

int main()
{
    Solution solution;

    // Build the BST:
    //
    //         6
    //        / \
    //       2   8
    //      / \ / \
    //     0  4 7  9
    //       / \
    //      3   5

    TreeNode *root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    // TC1: p and q are on opposite sides of root
    assert(solution.lowestCommonAncestor(
                       root, root->left, root->right)
               ->val == 6);
    cout << "TC1 passed: LCA is root\n";

    // TC2: One node is an ancestor of the other
    assert(solution.lowestCommonAncestor(
                       root, root->left, root->left->right)
               ->val == 2);
    cout << "TC2 passed: One node is ancestor of the other\n";

    // TC3: Nodes share a deeper ancestor
    assert(solution.lowestCommonAncestor(
                       root, root->left->right->left,
                       root->left->right->right)
               ->val == 4);
    cout << "TC3 passed: LCA is node 4\n";

    // TC4: Nodes in the right subtree
    assert(solution.lowestCommonAncestor(
                       root, root->right->left, root->right->right)
               ->val == 8);
    cout << "TC4 passed: LCA is node 8\n";

    // TC5: One node is the root
    assert(solution.lowestCommonAncestor(
                       root, root, root->right->right)
               ->val == 6);
    cout << "TC5 passed: One node is the root\n";

    // TC6: Same node passed as both p and q
    assert(solution.lowestCommonAncestor(
                       root, root->left, root->left)
               ->val == 2);
    cout << "TC6 passed: Same node twice\n";

    cout << "\nAll test cases passed!\n";
    return 0;
}
