// ============================================================
// PROBLEM: TWO SUM
// LeetCode #1
// ============================================================
//
// Given an integer array nums and an integer target, return
// the indices of two distinct elements whose values add up
// to target.
//
// You may assume exactly one valid answer exists.
// You cannot use the same element twice.
// Return the indices in any order.
//
// EXAMPLE 1:
// Input:  nums = [2, 7, 11, 15], target = 9
// Output: [0, 1]
// Explanation: nums[0] + nums[1] = 2 + 7 = 9.
//
// EXAMPLE 2:
// Input:  nums = [3, 2, 4], target = 6
// Output: [1, 2]
//
// EXAMPLE 3:
// Input:  nums = [3, 3], target = 6
// Output: [0, 1]
//
// CONSTRAINTS:
// 2 <= nums.size() <= 10^4
// -10^9 <= nums[i] <= 10^9
// -10^9 <= target <= 10^9
// Exactly one valid answer exists.
//
// YOUR TASK:
// 1. Start with a brute-force approach.
// 2. Experiment with different implementations.
// 3. Optimize your solution when you're ready.
// 4. Analyze time and space complexity.
//
// LeetCode: https://leetcode.com/problems/two-sum/
//
// ============================================================

#include <iostream>
#include <vector>
#include <cassert>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        // YOUR IMPLEMENTATION GOES HERE.
        // Experiment freely. No solution provided.
        unordered_map<int, int> map;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            /* code */
            int curr = target - nums[i];

            if (map.find(curr) != map.end())
            {
                return {map[curr], i};
            }

            map[nums[i]] = i;
        }

        return {};
    }
};

int main()
{
    Solution solution;

    // Test 1: Basic example
    {
        vector<int> nums = {2, 7, 11, 15};
        vector<int> result = solution.twoSum(nums, 9);
        assert(result == vector<int>({0, 1}));
        cout << "Test 1 passed!\n";
    }

    // Test 2: Pair in the middle
    {
        vector<int> nums = {3, 2, 4};
        vector<int> result = solution.twoSum(nums, 6);
        assert(result == vector<int>({1, 2}));
        cout << "Test 2 passed!\n";
    }

    // Test 3: Duplicate values
    {
        vector<int> nums = {3, 3};
        vector<int> result = solution.twoSum(nums, 6);
        assert(result == vector<int>({0, 1}));
        cout << "Test 3 passed!\n";
    }

    // Test 4: Negative numbers
    {
        vector<int> nums = {-3, 4, 3, 90};
        vector<int> result = solution.twoSum(nums, 0);
        assert(result == vector<int>({0, 2}));
        cout << "Test 4 passed!\n";
    }

    // Test 5: Negative target
    {
        vector<int> nums = {-5, -2, -8, 1};
        vector<int> result = solution.twoSum(nums, -10);
        assert(result == vector<int>({1, 2}));
        cout << "Test 5 passed!\n";
    }

    cout << "\nAll test cases passed!\n";
    return 0;
}
