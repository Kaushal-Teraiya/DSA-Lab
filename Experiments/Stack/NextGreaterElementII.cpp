/*
============================================================
LeetCode 503 - Next Greater Element II
Topic: Stack / Monotonic Stack / Circular Array
Difficulty: Medium
============================================================

PROBLEM STATEMENT:

Given a circular integer array nums, return the next greater
number for every element in nums.

The next greater number of a number x is the first greater
number to its traversing-order next in the array, which means
you could search circularly to find its next greater number.

If it doesn't exist, return -1 for this number.

A circular array means the end of the array connects to the
beginning of the array.

------------------------------------------------------------
EXAMPLE 1:

Input:
nums = [1,2,1]

Output:
[2,-1,2]

Explanation:
The first 1's next greater number is 2.
The number 2 has no next greater number.
The second 1's next greater number is 2.

------------------------------------------------------------
EXAMPLE 2:

Input:
nums = [3,8,4,1,2]

Output:
[8,-1,8,2,3]

------------------------------------------------------------
EXAMPLE 3:

Input:
nums = [5,4,3,2,1]

Output:
[-1,5,5,5,5]

------------------------------------------------------------
CONSTRAINTS:

- 1 <= nums.length <= 10000
- -1000000000 <= nums[i] <= 1000000000

------------------------------------------------------------
APPROACH NOTES:

Think about:
- Monotonic decreasing stack
- Store indices instead of values
- Initialize the answer vector with -1
- Circular traversal using modulo (%)
- Two traversals of the array
- Resolve previous indices when a greater element appears
- Do not push indices again during the second traversal

Expected complexity:
- Time: O(n)
- Auxiliary space: O(n)

============================================================
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        int n = nums.size();
        stack<int> monostack;
        vector<int> ans(n, -1);

        for (int i = 0; i < 2 * n; i++)
        {
            int index = i % n;
            while (!monostack.empty() && nums[monostack.top()] < nums[index])
            {
                ans[monostack.top()] = nums[index];
                monostack.pop();
            }

            monostack.push(index);
        }

        return ans;
    }
};

// ============================================================
// TEST HARNESS
// ============================================================

struct TestCase
{
    string name;
    vector<int> nums;
    vector<int> expected;
};

int main()
{
    vector<TestCase> tests = {
        {"LeetCode Example 1",
         {1, 2, 1},
         {2, -1, 2}},
        {"LeetCode Example 2",
         {3, 8, 4, 1, 2},
         {8, -1, 8, 2, 3}},
        {"Strictly Increasing",
         {1, 2, 3, 4, 5},
         {2, 3, 4, 5, -1}},
        {"Strictly Decreasing",
         {5, 4, 3, 2, 1},
         {-1, 5, 5, 5, 5}},
        {"All Equal",
         {5, 5, 5, 5},
         {-1, -1, -1, -1}},
        {"Single Element",
         {7},
         {-1}},
        {"Two Elements Increasing",
         {1, 2},
         {2, -1}},
        {"Two Elements Decreasing",
         {2, 1},
         {-1, 2}},
        {"Negative Numbers",
         {-3, -2, -4, -5},
         {-2, -1, -3, -3}},
        {"Repeated Values",
         {2, 1, 2, 4, 3},
         {4, 2, 4, -1, 4}}};

    int passed = 0;
    int failed = 0;

    vector<vector<int>> actualResults;

    for (const auto &test : tests)
    {
        Solution solution;
        vector<int> input = test.nums;

        vector<int> actual = solution.nextGreaterElements(input);

        actualResults.push_back(actual);

        if (actual == test.expected)
            passed++;
        else
            failed++;
    }

    cout << "========================================\n";
    cout << "NEXT GREATER ELEMENT II - TEST SUMMARY\n";
    cout << "========================================\n";
    cout << "Total Tests : " << tests.size() << "\n";
    cout << "Passed      : " << passed << "\n";
    cout << "Failed      : " << failed << "\n";
    cout << "========================================\n\n";

    for (size_t i = 0; i < tests.size(); i++)
    {
        bool success = actualResults[i] == tests[i].expected;

        cout << (success ? "[PASS] " : "[FAIL] ")
             << tests[i].name << "\n";

        if (!success)
        {
            cout << "  Input    : ";
            for (int value : tests[i].nums)
                cout << value << " ";

            cout << "\n  Expected : ";
            for (int value : tests[i].expected)
                cout << value << " ";

            cout << "\n  Actual   : ";
            for (int value : actualResults[i])
                cout << value << " ";

            cout << "\n";
        }
    }

    cout << "\n========================================\n";

    return failed == 0 ? 0 : 1;
}
