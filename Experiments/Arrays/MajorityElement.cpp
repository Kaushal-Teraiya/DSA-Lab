// ============================================================
// LeetCode #169 - Majority Element
// Difficulty: Easy
// Topics: Arrays, Hashing, Divide and Conquer, Voting
// ============================================================
//
// PROBLEM:
// Given an integer array nums of size n, return the element
// that appears more than floor(n / 2) times.
//
// The majority element is guaranteed to exist.
//
// EXAMPLE 1:
// Input:  nums = {3, 2, 3}
// Output: 3
//
// EXAMPLE 2:
// Input:  nums = {2, 2, 1, 1, 1, 2, 2}
// Output: 2
//
// CONSTRAINTS:
// 1 <= nums.size() <= 50000
// -10^9 <= nums[i] <= 10^9
// A majority element always exists.
//
// HINTS:
// 1. Consider how you could count occurrences.
// 2. Can you solve it without storing every frequency?
// 3. Try to achieve O(n) time complexity.
//
// TARGET:
// Time: O(n)
// Space: Try to achieve O(1) extra space.
//
// ============================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        // Your implementation goes here.
        int count = 0;
        int candidate; //the majority element candidate.

        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            //Initially count is 0 so it automatically chooses first element.
            if (count == 0)
            {
                candidate = nums[i];
                count++; //increase count.
            }
            else if (nums[i] != candidate)
            {
                count--;
            }
            else if (nums[i] == candidate)
            {
                count++;
            }
        }

        return candidate;
    }
};

// -------------------- TEST HARNESS --------------------

void runTest(vector<int> nums, int expected, int testNumber)
{
    Solution solution;
    int actual = solution.majorityElement(nums);

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
    runTest({3, 2, 3}, 3, 1);
    runTest({2, 2, 1, 1, 1, 2, 2}, 2, 2);
    runTest({1}, 1, 3);
    runTest({5, 5, 5, 2, 2}, 5, 4);
    runTest({-1, -1, -1, 2, 3}, -1, 5);

    return 0;
}
