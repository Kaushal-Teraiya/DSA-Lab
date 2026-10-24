// ============================================================
// LeetCode #108 - Convert Sorted Array to Binary Search Tree
// Difficulty: Easy
// Topics: Array, Divide and Conquer, Tree, Binary Search Tree
// ============================================================
//
// PROBLEM:
// Given an integer array nums where the elements are sorted
// in ascending order, convert it to a height-balanced binary
// search tree.
//
// A height-balanced binary tree is a binary tree in which the
// depth of the two subtrees of every node never differs by more
// than one.
//
// EXAMPLE 1:
// Input:  nums = [-10, -3, 0, 5, 9]
// Output: [0, -10, 5, null, -3, null, 9]
//
// One possible tree:
//
//          0
//         / \
//      -10   5
//         \   \
//         -3   9
//
// EXAMPLE 2:
// Input:  nums = [1, 3]
// Output: [1, null, 3] OR [3, 1]
//
// CONSTRAINTS:
// - 1 <= nums.length <= 10^4
// - -10^4 <= nums[i] <= 10^4
// - nums is sorted in a strictly increasing order.
//
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
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
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        // TODO: Start the recursive construction using the
        // entire array range.
        int n = nums.size();
        return buildTree(nums, 0, n - 1);
    }

    // this function is reposible for building the tree piece by piece from the array.
    TreeNode *buildTree(vector<int> &nums, int left, int right)
    {
        // when leftPointer becomes greater than right return null pointer.
        if (left > right)
            return nullptr;

        // mid formula gets mid index of the array.
        int mid = left + (right - left) / 2;

        // create a new node. intially inset the mid as the root.
        TreeNode *newNode = new TreeNode(nums[mid]);

        // recursively call buildtree for left half of the array. mid - 1 means the array shrinks from the right which is what we want since we are building a Bst
        // same for right half but this time left shrinks.
        newNode->left = buildTree(nums, left, mid - 1);   // first it builds the left subtree of the main root node.. the below right node call is still only for the left subtres's right nodes
        newNode->right = buildTree(nums, mid + 1, right); // then the right subtree recursion beginss which first builds the left nodes then right nodes.

        return newNode;
    }
};

// Returns the tree's height in nodes.
int treeHeight(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

// Checks that the tree satisfies the BST ordering.
bool isBST(TreeNode *root, long long low, long long high)
{
    if (root == nullptr)
        return true;

    if (root->val <= low || root->val >= high)
        return false;

    return isBST(root->left, low, root->val) &&
           isBST(root->right, root->val, high);
}

// Checks the height-balance condition at every node.
bool isHeightBalanced(TreeNode *root)
{
    if (root == nullptr)
        return true;

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    if (abs(leftHeight - rightHeight) > 1)
        return false;

    return isHeightBalanced(root->left) &&
           isHeightBalanced(root->right);
}

// Collects inorder traversal to verify all values and their order.
void inorder(TreeNode *root, vector<int> &result)
{
    if (root == nullptr)
        return;

    inorder(root->left, result);
    result.push_back(root->val);
    inorder(root->right, result);
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
    vector<int> nums,
    Solution &solution)
{
    TreeNode *root = solution.sortedArrayToBST(nums);

    vector<int> actualInorder;
    inorder(root, actualInorder);

    bool inorderCorrect = (actualInorder == nums);
    bool bstCorrect = isBST(
        root,
        numeric_limits<long long>::lowest(),
        numeric_limits<long long>::max());
    bool balanced = isHeightBalanced(root);

    bool passed = root != nullptr &&
                  inorderCorrect &&
                  bstCorrect &&
                  balanced;

    cout << name << ": "
         << (passed ? "PASS" : "FAIL")
         << " | Inorder: " << (inorderCorrect ? "PASS" : "FAIL")
         << " | BST: " << (bstCorrect ? "PASS" : "FAIL")
         << " | Balanced: " << (balanced ? "PASS" : "FAIL")
         << '\n';

    deleteTree(root);
}

int main()
{
    Solution solution;

    cout << "========== TEST RESULTS ==========\n";

    runTest(
        "Test 1 - Odd-sized array",
        {-10, -3, 0, 5, 9},
        solution);

    runTest(
        "Test 2 - Two elements",
        {1, 3},
        solution);

    runTest(
        "Test 3 - Single element",
        {7},
        solution);

    runTest(
        "Test 4 - Even-sized array",
        {1, 2, 3, 4, 5, 6},
        solution);

    runTest(
        "Test 5 - Negative and positive values",
        {-8, -4, -1, 2, 6, 10, 15},
        solution);

    cout << "==================================\n";
    cout << "Detailed audit: review any FAIL above.\n";

    return 0;
}
