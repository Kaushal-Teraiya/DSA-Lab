#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #33 — Search in Rotated Sorted Array
Difficulty: Medium
Topic: Binary Search

PROBLEM:
An integer array nums is sorted in ascending order with distinct values.
It is then rotated to the left by some number of positions.

Given nums and an integer target, return the index of target
if it exists in nums. Otherwise, return -1.

You must solve the problem in O(log n) time.

EXAMPLES:
1. nums = {4, 5, 6, 7, 0, 1, 2}, target = 0
   Output: 4

2. nums = {4, 5, 6, 7, 0, 1, 2}, target = 3
   Output: -1

3. nums = {1}, target = 0
   Output: -1

YOUR TASK:
Implement int search(vector<int>& nums, int target).

TEST CASES:
1. {4, 5, 6, 7, 0, 1, 2}, target = 0  -> 4
2. {4, 5, 6, 7, 0, 1, 2}, target = 3  -> -1
3. {1}, target = 0                     -> -1
4. {1}, target = 1                     -> 0
5. {3, 1}, target = 1                  -> 1
6. {5, 1, 3}, target = 5               -> 0
7. {6, 7, 1, 2, 3, 4, 5}, target = 2   -> 3
8. {7, 8, 1, 2, 3, 4, 5, 6}, target = 6 -> 7
9. {1, 2, 3, 4, 5}, target = 4         -> 3
10. {5, 6, 7, 1, 2, 3, 4}, target = 7  -> 2

TARGET:
Time: O(log n)
Extra space: O(1)
*/

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        // TODO: Solve it yourself.
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        int mid = left + (right - left) / 2;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target)
            {
                return mid;
            }

            if (nums[left] <= nums[mid])
            {
                if (target < nums[mid] && target >= nums[left])
                { // left as it is..
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
            else
            {
                if (target > nums[mid] && target <= nums[right])
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};

void runTest(vector<int> nums, int target, int expected, int testNumber)
{
    Solution solution;
    int actual = solution.search(nums, target);

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
    runTest({4, 5, 6, 7, 0, 1, 2}, 0, 4, 1);
    runTest({4, 5, 6, 7, 0, 1, 2}, 3, -1, 2);
    runTest({1}, 0, -1, 3);
    runTest({1}, 1, 0, 4);
    runTest({3, 1}, 1, 1, 5);
    runTest({5, 1, 3}, 5, 0, 6);
    runTest({6, 7, 1, 2, 3, 4, 5}, 2, 3, 7);
    runTest({7, 8, 1, 2, 3, 4, 5, 6}, 6, 7, 8);
    runTest({1, 2, 3, 4, 5}, 4, 3, 9);
    runTest({5, 6, 7, 1, 2, 3, 4}, 7, 2, 10);

    return 0;
}
