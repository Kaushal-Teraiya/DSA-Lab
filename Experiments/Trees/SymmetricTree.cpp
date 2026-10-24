// ============================================================
// LeetCode #101 - Symmetric Tree
// Difficulty: Easy
// Topics: Tree, Depth-First Search, Breadth-First Search
// ============================================================
//
// PROBLEM:
// Given the root of a binary tree, check whether it is a mirror
// of itself (i.e., symmetric around its center).
//
// EXAMPLE 1:
// Input:  root = [1,2,2,3,4,4,3]
// Output: true
//
//         1
//        / \
//       2   2
//      / \ / \
//     3  4 4  3
//
// EXAMPLE 2:
// Input: root = [1,2,2,null,3,null,3]
// Output: false
//
//         1
//        / \
//       2   2
//        \   \
//         3   3
//
// CONSTRAINTS:
// - The number of nodes is in the range [1, 1000].
// - -100 <= Node.val <= 100.
//
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution
{
public:
    bool isSymmetric(TreeNode *root)
    {
        // TODO:
        // 1. Handle an empty tree.
        // 2. Compare the root's left and right subtrees.
        if (root == nullptr)
            return true;

        return isMirror(root->left , root->right);
    }

    bool isMirror(TreeNode *left, TreeNode *right)
    {
        // TODO:
        // 1. If both nodes are null, they match.
        // 2. If exactly one node is null, they do not match.
        // 3. If values differ, they do not match.
        // 4. Compare outer children and inner children recursively.

        if (left == nullptr && right == nullptr)
            return true;
        if (left == nullptr || right == nullptr)
            return false;

        //left and right values must match.
        //Match the mirror's so left->left and right->right 
        //Match the mirrors so lrft->right and right->left
        //inner and outer children.

        return left->val == right->val && isMirror(left->left, right->right) && isMirror(left->right, right->left);
    }
};

// Builds a tree from level-order values.
// Use -999999 to represent nullptr.
TreeNode *buildTree(const vector<int> &values)
{
    if (values.empty() || values[0] == -999999)
        return nullptr;

    TreeNode *root = new TreeNode(values[0]);
    queue<TreeNode *> q;
    q.push(root);

    size_t i = 1;

    while (!q.empty() && i < values.size())
    {
        TreeNode *current = q.front();
        q.pop();

        if (i < values.size() && values[i] != -999999)
        {
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;

        if (i < values.size() && values[i] != -999999)
        {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }

    return root;
}

void deleteTree(TreeNode *root)
{
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void runTest(
    const string &name,
    const vector<int> &input,
    bool expected,
    Solution &solution)
{
    TreeNode *root = buildTree(input);
    bool actual = solution.isSymmetric(root);

    cout << name << ": "
         << (actual == expected ? "PASS" : "FAIL")
         << " | Expected: " << boolalpha << expected
         << " | Actual: " << actual << '\n';

    deleteTree(root);
}

int main()
{
    Solution solution;

    cout << "========== TEST RESULTS ==========\n";

    runTest(
        "Test 1 - Symmetric tree",
        {1, 2, 2, 3, 4, 4, 3},
        true,
        solution);

    runTest(
        "Test 2 - Asymmetric tree",
        {1, 2, 2, -999999, 3, -999999, 3},
        false,
        solution);

    runTest(
        "Test 3 - Single node",
        {1},
        true,
        solution);

    runTest(
        "Test 4 - Matching negative values",
        {-1, -2, -2, -3, -4, -4, -3},
        true,
        solution);

    runTest(
        "Test 5 - Different mirrored values",
        {1, 2, 2, 3, -999999, -999999, 4},
        false,
        solution);

    runTest(
        "Test 6 - One-sided child",
        {1, 2, 2, 3, -999999, 3},
        false,
        solution);

    cout << "==================================\n";
    cout << "Detailed audit: review any FAIL above.\n";

    return 0;
}
