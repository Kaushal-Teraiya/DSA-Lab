#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #53 — Maximum Subarray
Difficulty: Medium
Topic: Arrays, Kadane's Algorithm

PROBLEM:
Given an integer array nums, find the contiguous subarray
with the largest sum and return that sum.

EXAMPLE:
Input:  nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4}
Output: 6

Explanation:
The subarray {4, -1, 2, 1} has the largest sum: 6.

YOUR TASK:
Implement int maxSubArray(vector<int>& nums).

TEST CASES:
1. {-2, 1, -3, 4, -1, 2, 1, -5, 4} -> 6
2. {1}                                -> 1
3. {5, 4, -1, 7, 8}                  -> 23
4. {-1, -2, -3, -4}                  -> -1
5. {1, 2, 3, 4}                      -> 10
6. {-2, 1}                           -> 1
7. {0, 0, 0}                         -> 0
8. {-2, -1}                          -> -1
9. {4, -1, 2, 1}                     -> 6
10. {8, -10, 5, 6}                   -> 11

TARGET:
Time: O(n)
Extra space: O(1)
*/

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        // TODO: Solve it yourself.
        int n = nums.size();
        int currSum = nums[0];
        int maxSum = nums[0];

        for (int i = 1; i < n; i++)
        {
            currSum = max(currSum + nums[i], nums[i]);
            maxSum = max(currSum, maxSum);
        }
        return maxSum;
    }
};

void runTest(vector<int> nums, int expected, int testNumber)
{
    Solution solution;
    int actual = solution.maxSubArray(nums);

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Expected: " << expected
             << ", Actual: " << actual << '\n';
    }
}

int main()
{
    runTest({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6, 1);
    runTest({1}, 1, 2);
    runTest({5, 4, -1, 7, 8}, 23, 3);
    runTest({-1, -2, -3, -4}, -1, 4);
    runTest({1, 2, 3, 4}, 10, 5);
    runTest({-2, 1}, 1, 6);
    runTest({0, 0, 0}, 0, 7);
    runTest({-2, -1}, -1, 8);
    runTest({4, -1, 2, 1}, 6, 9);
    runTest({8, -10, 5, 6}, 11, 10);

    return 0;
}
