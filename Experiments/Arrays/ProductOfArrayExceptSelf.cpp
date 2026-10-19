// ============================================================
// PROBLEM: PRODUCT OF ARRAY EXCEPT SELF
// LeetCode #238
// ============================================================
//
// Given an integer array nums, return an array answer such that
// answer[i] is equal to the product of all elements of nums
// except nums[i].
//
// The product of any prefix or suffix of nums is guaranteed
// to fit in a 32-bit integer.
//
// You must solve this without using division.
// Aim for O(n) time complexity.
//
// EXAMPLE 1:
// Input:  nums = [1, 2, 3, 4]
// Output: [24, 12, 8, 6]
//
// EXAMPLE 2:
// Input:  nums = [-1, 1, 0, -3, 3]
// Output: [0, 0, 9, 0, 0]
//
// CONSTRAINTS:
// 2 <= nums.size() <= 10^5
// -30 <= nums[i] <= 30
// The product of any prefix or suffix fits in 32-bit integer.
// Answer[i] fits in a 32-bit integer.
//
// FOLLOW-UP:
// Can you solve it in O(n) time without using division
// and with O(1) extra space, excluding the output array?
//
// YOUR MISSION:
// 1. Work out the brute-force approach.
// 2. Try to optimize it.
// 3. Do not look up the solution immediately.
// 4. Experiment freely in this file.
//
// LeetCode:
// https://leetcode.com/problems/product-of-array-except-self/
//
// ============================================================

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        // TODO: Implement your solution.
        // Start with your own reasoning!

        int leftProduct = 1;
        int rightProduct = 1;
        int n = nums.size();
        vector<int> result(n, 1);

        for (int i = 0; i < n; i++)
        {
            result[i] = leftProduct;
            leftProduct *= nums[i];
        }

        for (int i = n - 1; i >= 0; i--)
        {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }

        return result;
    }
};

int main()
{
    Solution solution;

    // Test 1: Basic example
    {
        vector<int> nums = {1, 2, 3, 4};
        vector<int> expected = {24, 12, 8, 6};

        vector<int> result = solution.productExceptSelf(nums);

        assert(result == expected);
        cout << "Test 1 passed!\n";
    }

    // Test 2: Contains zero
    {
        vector<int> nums = {-1, 1, 0, -3, 3};
        vector<int> expected = {0, 0, 9, 0, 0};

        vector<int> result = solution.productExceptSelf(nums);

        assert(result == expected);
        cout << "Test 2 passed!\n";
    }

    // Test 3: Two elements
    {
        vector<int> nums = {2, 5};
        vector<int> expected = {5, 2};

        vector<int> result = solution.productExceptSelf(nums);

        assert(result == expected);
        cout << "Test 3 passed!\n";
    }

    // Test 4: Negative numbers
    {
        vector<int> nums = {-2, -3, 4};
        vector<int> expected = {-12, -8, 6};

        vector<int> result = solution.productExceptSelf(nums);

        assert(result == expected);
        cout << "Test 4 passed!\n";
    }

    // Test 5: Multiple zeros
    {
        vector<int> nums = {0, 2, 0, 4};
        vector<int> expected = {0, 0, 0, 0};

        vector<int> result = solution.productExceptSelf(nums);

        assert(result == expected);
        cout << "Test 5 passed!\n";
    }

    cout << "\nAll test cases passed!\n";
    return 0;
}
