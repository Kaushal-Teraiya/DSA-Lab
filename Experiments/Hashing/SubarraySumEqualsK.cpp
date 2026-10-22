#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #560 — Subarray Sum Equals K
Difficulty: Medium
Topic: Hashing, Prefix Sum

PROBLEM:
Given an array of integers nums and an integer k,
return the total number of subarrays whose sum equals k.

A subarray is a contiguous, non-empty sequence of elements.

EXAMPLES:
Input: nums = {1, 1, 1}, k = 2
Output: 2

Input: nums = {1, 2, 3}, k = 3
Output: 2

YOUR TASK:
Implement int subarraySum(vector<int>& nums, int k).

TEST CASES:
1. nums = {1, 1, 1}, k = 2        -> 2
2. nums = {1, 2, 3}, k = 3        -> 2
3. nums = {1}, k = 0              -> 0
4. nums = {1, -1, 0}, k = 0       -> 3
5. nums = {3, 4, 7, 2, -3, 1, 4, 2}, k = 7 -> 4
6. nums = {-1, -1, 1}, k = 0      -> 1
7. nums = {1, 2, 1, 2, 1}, k = 3  -> 4
8. nums = {0, 0, 0}, k = 0        -> 6
9. nums = {2, -2, 2, -2}, k = 0   -> 4
10. nums = {5}, k = 5             -> 1

TARGET:
- Time: O(n)
- Extra space: O(n)
*/

class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        // TODO: Implement your solution.
        int n = nums.size();
        unordered_map<int, int> map;
        int currPrefixSum = 0;
        int answer = 0;
        map[0] = 1;
        
        for (int i = 0; i < n; i++)
        {
            currPrefixSum += nums[i];
            answer += map[currPrefixSum - k];
            map[currPrefixSum]++;
        }

        return answer;
    }
};

void runTest(vector<int> nums, int k, int expected, int testNumber)
{
    Solution solution;
    int actual = solution.subarraySum(nums, k);

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Input:    nums = { ";
        for (int num : nums)
            cout << num << " ";
        cout << "}, k = " << k << '\n';
        cout << "Expected: " << expected << '\n';
        cout << "Actual:   " << actual << '\n';
    }
}

int main()
{
    runTest({1, 1, 1}, 2, 2, 1);
    runTest({1, 2, 3}, 3, 2, 2);
    runTest({1}, 0, 0, 3);
    runTest({1, -1, 0}, 0, 3, 4);
    runTest({3, 4, 7, 2, -3, 1, 4, 2}, 7, 4, 5);
    runTest({-1, -1, 1}, 0, 1, 6);
    runTest({1, 2, 1, 2, 1}, 3, 4, 7);
    runTest({0, 0, 0}, 0, 6, 8);
    runTest({2, -2, 2, -2}, 0, 4, 9);
    runTest({5}, 5, 1, 10);

    return 0;
}
