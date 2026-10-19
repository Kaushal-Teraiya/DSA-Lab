
#include <bits/stdc++.h>
#include <cassert>

using namespace std;

// ============================================================
// PROBLEM: KTH LARGEST ELEMENT IN AN ARRAY
// LeetCode #215
// ============================================================
//
// Given an integer array nums and an integer k, return the
// kth largest element in the array.
//
// Note: It is the kth largest element in sorted order,
// not the kth distinct element.
//
// EXAMPLE 1:
// Input: nums = [3,2,1,5,6,4], k = 2
// Output: 5
//
// EXAMPLE 2:
// Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
// Output: 4
//
// YOUR TASK:
// 1. Start with your own reasoning.
// 2. Try a brute-force approach before optimizing.
// 3. Implement and test locally.
// 4. Analyze time and space complexity.
//
// LeetCode:
// https://leetcode.com/problems/kth-largest-element-in-an-array/
// ============================================================

class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        // TODO: Implement your solution.
        priority_queue<int, vector<int>, greater<int>> minHeap;
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            minHeap.push(nums[i]);

            if (minHeap.size() > k)
            {
                minHeap.pop();
            }
        }

        return minHeap.top();
    }
};

int main()
{
    Solution solution;

    // Test 3: k = 1 (largest element)
    {
        vector<int> nums = {3, 2, 1, 5, 6, 4};
        assert(solution.findKthLargest(nums, 1) == 6);
        cout << "Test 3 passed!\n";
    }

    // Test 4: k = n (smallest element)
    {
        vector<int> nums = {3, 2, 1, 5, 6, 4};
        assert(solution.findKthLargest(nums, 6) == 1);
        cout << "Test 4 passed!\n";
    }

    // Test 5: All elements are equal
    {
        vector<int> nums = {7, 7, 7, 7};
        assert(solution.findKthLargest(nums, 2) == 7);
        cout << "Test 5 passed!\n";
    }

    // Test 6: Duplicate values count separately
    {
        vector<int> nums = {5, 5, 4, 4, 3, 3};
        assert(solution.findKthLargest(nums, 3) == 4);
        cout << "Test 6 passed!\n";
    }

    // Test 7: Negative numbers
    {
        vector<int> nums = {-5, -2, -8, -1, -3};
        assert(solution.findKthLargest(nums, 2) == -2);
        cout << "Test 7 passed!\n";
    }

    // Test 8: Mixed positive and negative numbers
    {
        vector<int> nums = {-10, 5, 0, -2, 8, 3};
        assert(solution.findKthLargest(nums, 4) == 0);
        cout << "Test 8 passed!\n";
    }

    // Test 9: Single element
    {
        vector<int> nums = {42};
        assert(solution.findKthLargest(nums, 1) == 42);
        cout << "Test 9 passed!\n";
    }

    // Test 10: k equals number of elements, with duplicates
    {
        vector<int> nums = {4, 1, 4, 2, 9};
        assert(solution.findKthLargest(nums, 5) == 1);
        cout << "Test 10 passed!\n";
    }

    // Test 11: Unsorted array
    {
        vector<int> nums = {100, -100, 50, 0, 25};
        assert(solution.findKthLargest(nums, 3) == 25);
        cout << "Test 11 passed!\n";
    }

    // Test 12: k = 2 with repeated largest values
    {
        vector<int> nums = {9, 9, 8, 7, 6};
        assert(solution.findKthLargest(nums, 2) == 9);
        cout << "Test 12 passed!\n";
    }
    return 0;
}
