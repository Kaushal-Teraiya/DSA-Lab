// ============================================================
// LeetCode #144 - Binary Tree Preorder Traversal
// Difficulty: Easy
// Topics: Tree, Binary Tree, DFS, Recursion
// Pattern: Root -> Left -> Right
// ============================================================
//
// PROBLEM STATEMENT:
// Given the root of a binary tree, return the preorder traversal
// of its nodes' values.
//
// Preorder traversal visits:
// 1. The current node (Root)
// 2. The left subtree (Left)
// 3. The right subtree (Right)
//
// EXAMPLE 1:
// Input:  root = [1,null,2,3]
// Output: [1,2,3]
//
//       1
//        \
//         2
//        /
//       3
//
// EXAMPLE 2:
// Input:  root = [1,2,3,4,5]
// Output: [1,2,4,5,3]
//
//        1
//       / \
//      2   3
//     / \
//    4   5
//
// EXAMPLE 3:
// Input:  root = []
// Output: []
//
// CONSTRAINTS:
// - The number of nodes is in the range [0, 100].
// - -100 <= Node.val <= 100
//
// THINK BEFORE CODING:
// 1. What should happen when root == nullptr?
// 2. At what point should root->val be added to the answer?
// 3. How can recursive calls share the same answer vector?
// 4. Why must the left subtree be processed before the right?
//
// EXPECTED COMPLEXITY:
// Time:  O(n)
// Space: O(h) auxiliary recursion stack, plus O(n) output
// where n = number of nodes and h = tree height.
//
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <string>

using namespace std;

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
    vector<int> preorderTraversal(TreeNode *root)
    {
        // TODO:
        // Implement preorder traversal using recursion.
        // Consider using a helper function and vector<int>& ans.
        vector<int> ans;
        preorder(root, ans);
        return ans;
    }

    void preorder(TreeNode *root, vector<int> &ans)
    {
        if (root == nullptr)
            return;

        ans.push_back(root->val);
        preorder(root->left, ans);
        preorder(root->right, ans);
    }
};

// Build a binary tree from level-order input.
// nullopt represents a missing node.
TreeNode *buildTree(const vector<optional<int>> &values)
{
    if (values.empty() || !values[0].has_value())
    {
        return nullptr;
    }

    TreeNode *root = new TreeNode(*values[0]);
    queue<TreeNode *> nodes;
    nodes.push(root);

    size_t i = 1;

    while (!nodes.empty() && i < values.size())
    {
        TreeNode *current = nodes.front();
        nodes.pop();

        if (i < values.size() && values[i].has_value())
        {
            current->left = new TreeNode(*values[i]);
            nodes.push(current->left);
        }
        ++i;

        if (i < values.size() && values[i].has_value())
        {
            current->right = new TreeNode(*values[i]);
            nodes.push(current->right);
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
    const string &name,
    const vector<optional<int>> &input,
    const vector<int> &expected)
{
    TreeNode *root = buildTree(input);

    Solution solution;
    vector<int> actual = solution.preorderTraversal(root);

    cout << name << ": ";

    if (actual == expected)
    {
        cout << "PASS";
    }
    else
    {
        cout << "FAIL | Expected: [";
        for (size_t i = 0; i < expected.size(); ++i)
        {
            if (i)
                cout << ", ";
            cout << expected[i];
        }

        cout << "] | Actual: [";
        for (size_t i = 0; i < actual.size(); ++i)
        {
            if (i)
                cout << ", ";
            cout << actual[i];
        }
        cout << "]";
    }

    cout << '\n';
    deleteTree(root);
}

int main()
{
    cout << "LeetCode #144 - Binary Tree Preorder Traversal\n";
    cout << "==============================================\n";

    // Test 1: Example 1
    runTest(
        "Test 1 - Right subtree",
        {1, nullopt, 2, 3},
        {1, 2, 3});

    // Test 2: Example 2
    runTest(
        "Test 2 - Balanced tree",
        {1, 2, 3, 4, 5},
        {1, 2, 4, 5, 3});

    // Test 3: Empty tree
    runTest(
        "Test 3 - Empty tree",
        {},
        {});

    // Test 4: Single node
    runTest(
        "Test 4 - Single node",
        {7},
        {7});

    // Test 5: Left-skewed tree
    runTest(
        "Test 5 - Left-skewed tree",
        {1, 2, nullopt, 3},
        {1, 2, 3});

    // Test 6: Negative values
    runTest(
        "Test 6 - Negative values",
        {-1, -2, 3, nullopt, -4},
        {-1, -2, -4, 3});

    return 0;
}
