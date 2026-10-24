// ============================================================
// LeetCode #102 - Binary Tree Level Order Traversal
// Difficulty: Medium
// Topics: Tree, Breadth-First Search, Queue, Binary Tree
// ============================================================
//
// PROBLEM:
// Given the root of a binary tree, return the level order
// traversal of its nodes' values (from left to right, level
// by level).
//
// EXAMPLE 1:
// Input:  root = [3,9,20,null,null,15,7]
// Output: [[3],[9,20],[15,7]]
//
//             3
//            / \
//           9   20
//              /  \
//             15   7
//
// EXAMPLE 2:
// Input:  root = [1]
// Output: [[1]]
//
// EXAMPLE 3:
// Input:  root = []
// Output: []
//
// CONSTRAINTS:
// - The number of nodes is in the range [0, 2000].
// - -1000 <= Node.val <= 1000.
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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        // create answer and a queue
        vector<vector<int>> answer;
        queue<TreeNode *> q;

        // if root is null just return the empty answer array
        if (root == nullptr)
            return answer;

        q.push(root); // push the intial value in queue as root.

        while (!q.empty())
        {
            // since its BFS we need to keep track of the level size and the node values in that level.
            vector<int> level;
            int levelSize = q.size();

            // run loop for levelSize times.
            // gives us this structure [[],[],[]]
            for (int i = 0; i < levelSize; i++)
            {
                TreeNode *currentNode = q.front();
                q.pop();//get front element from queue

                level.push_back(currentNode->val);

                if (currentNode->left != nullptr)
                {
                    //push the left child of that node in the queue
                    q.push(currentNode->left); 
                }

                if (currentNode->right != nullptr)
                {
                    //push the right child
                    q.push(currentNode->right); 
                }
            }

            answer.push_back(level); //push level vector in the answer
        }

        return answer; //final ans
    }
};

// Builds a binary tree from level-order values.
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

void printLevels(const vector<vector<int>> &levels)
{
    cout << "[";

    for (size_t i = 0; i < levels.size(); i++)
    {
        if (i > 0)
            cout << ", ";

        cout << "[";

        for (size_t j = 0; j < levels[i].size(); j++)
        {
            if (j > 0)
                cout << ", ";

            cout << levels[i][j];
        }

        cout << "]";
    }

    cout << "]";
}

void runTest(
    const string &name,
    const vector<int> &input,
    const vector<vector<int>> &expected,
    Solution &solution)
{
    TreeNode *root = buildTree(input);
    vector<vector<int>> actual = solution.levelOrder(root);

    bool passed = (actual == expected);

    cout << name << ": "
         << (passed ? "PASS" : "FAIL")
         << " | Expected: ";

    printLevels(expected);

    cout << " | Actual: ";
    printLevels(actual);
    cout << '\n';

    deleteTree(root);
}

int main()
{
    Solution solution;

    cout << "========== TEST RESULTS ==========\n";

    runTest(
        "Test 1 - Multiple levels",
        {3, 9, 20, -999999, -999999, 15, 7},
        {{3}, {9, 20}, {15, 7}},
        solution);

    runTest(
        "Test 2 - Single node",
        {1},
        {{1}},
        solution);

    runTest(
        "Test 3 - Empty tree",
        {},
        {},
        solution);

    runTest(
        "Test 4 - Left-skewed tree",
        {1, 2, -999999, 3},
        {{1}, {2}, {3}},
        solution);

    runTest(
        "Test 5 - Negative values",
        {-1, -2, -3, -4, -5, -6, -7},
        {{-1}, {-2, -3}, {-4, -5, -6, -7}},
        solution);

    runTest(
        "Test 6 - Uneven tree",
        {1, 2, 3, -999999, 4, -999999, 5},
        {{1}, {2, 3}, {4, 5}},
        solution);

    cout << "==================================\n";
    cout << "Detailed audit: review any FAIL above.\n";

    return 0;
}
