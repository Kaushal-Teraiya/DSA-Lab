#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #189 — Rotate Array

PROBLEM STATEMENT:
Given an integer array nums, rotate the array to the right
by k steps, where k is non-negative.

EXAMPLE 1:
Input: nums = {1, 2, 3, 4, 5, 6, 7}, k = 3
Output: {5, 6, 7, 1, 2, 3, 4}

EXAMPLE 2:
Input: nums = {-1, -100, 3, 99}, k = 2
Output: {3, 99, -1, -100}

EXAMPLE 3:
Input: nums = {1, 2}, k = 3
Output: {2, 1}

CONSTRAINTS:
- 1 <= nums.length <= 10^5
- -2^31 <= nums[i] <= 2^31 - 1
- 0 <= k <= 10^5

IMPORTANT:
Rotate the array in-place. Do not return a new array.

YOUR TASK:
Implement void rotate(vector<int>& nums, int k).
*/

class Solution
{
public:
        void rotate(vector<int> &nums, int k)
        {
                // TODO: Implement your solution.
                int n = nums.size();
                k %= n;
                reverse(nums.begin(), nums.end());
                reverse(nums.begin() + k, nums.end());
                reverse(nums.begin(), nums.begin() + k);
        }
};

void runTest(vector<int> nums, int k,
             const vector<int> &expected, int testNumber)
{
        Solution solution;
        solution.rotate(nums, k);

        cout << "Test " << testNumber << ": "
             << (nums == expected ? "PASS" : "FAIL")
             << " | Expected: ";

        for (int x : expected)
                cout << x << ' ';

        cout << "| Got: ";
        for (int x : nums)
                cout << x << ' ';

        cout << '\n';
}

int main()
{
        runTest({1, 2, 3, 4, 5, 6, 7},
                3, {5, 6, 7, 1, 2, 3, 4}, 1);

        runTest({-1, -100, 3, 99},
                2, {3, 99, -1, -100}, 2);

        runTest({1, 2}, 3, {2, 1}, 3);

        runTest({1}, 0, {1}, 4);

        runTest({1, 2, 3, 4, 5}, 0,
                {1, 2, 3, 4, 5}, 5);

        runTest({1, 2, 3}, 3,
                {1, 2, 3}, 6);

        runTest({1, 2, 3, 4, 5, 6}, 2,
                {5, 6, 1, 2, 3, 4}, 7);

        runTest({1, 2, 3, 4, 5}, 7,
                {4, 5, 1, 2, 3}, 8);

        return 0;
}
