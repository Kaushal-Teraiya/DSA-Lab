#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #283 — Move Zeroes

PROBLEM STATEMENT:
Given an integer array nums, move all zeroes to the end of it
while maintaining the relative order of the non-zero elements.

You must do this in-place without making a copy of the array.

EXAMPLE 1:
Input: nums = {0, 1, 0, 3, 12}
Output: {1, 3, 12, 0, 0}

EXAMPLE 2:
Input: nums = {0}
Output: {0}

CONSTRAINTS:
- 1 <= nums.length <= 10^4
- -2^31 <= nums[i] <= 2^31 - 1
- nums[i] is either zero or non-zero.

YOUR TASK:
Implement void moveZeroes(vector<int>& nums).

TEST CASES:
1. {0, 1, 0, 3, 12}       -> {1, 3, 12, 0, 0}
2. {0}                    -> {0}
3. {1, 2, 3}              -> {1, 2, 3}
4. {0, 0, 0}              -> {0, 0, 0}
5. {1, 0, 2, 0, 3}        -> {1, 2, 3, 0, 0}
6. {0, 1, 2, 3}           -> {1, 2, 3, 0}
7. {1, 2, 0, 0}           -> {1, 2, 0, 0}
8. {-1, 0, 4, 0, -3}      -> {-1, 4, -3, 0, 0}
9. {0, 1, 0, 0, 2}         -> {1, 2, 0, 0, 0}
10. {4, 0, 5, 0, 0, 6}    -> {4, 5, 6, 0, 0, 0}

NOTE:
- Preserve the order of all non-zero elements.
- Modify the input vector directly.
- Try to achieve O(n) time and O(1) extra space.
*/

class Solution
{
public:
    void moveZeroes(vector<int> &nums)
    {
        // TODO: Implement your solution.
        int firstZero = -1;
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            if (nums[i] == 0 && firstZero == -1)
            {
                firstZero = i;
            }
            else if (nums[i] != 0 && firstZero != -1)
            {
                swap(nums[i], nums[firstZero]);
                firstZero++;
            }
        }
    }
};

void runTest(vector<int> nums, const vector<int> &expected, int testNumber)
{
    Solution solution;
    solution.moveZeroes(nums);

    cout << "Test " << testNumber << ": "
         << (nums == expected ? "PASS" : "FAIL") << '\n';

    if (nums != expected)
    {
        cout << "Expected: ";
        for (int x : expected)
            cout << x << ' ';
        cout << "\nActual:   ";
        for (int x : nums)
            cout << x << ' ';
        cout << '\n';
    }
}

int main()
{
    runTest({0, 1, 0, 3, 12}, {1, 3, 12, 0, 0}, 1);
    runTest({0}, {0}, 2);
    runTest({1, 2, 3}, {1, 2, 3}, 3);
    runTest({0, 0, 0}, {0, 0, 0}, 4);
    runTest({1, 0, 2, 0, 3}, {1, 2, 3, 0, 0}, 5);
    runTest({0, 1, 2, 3}, {1, 2, 3, 0}, 6);
    runTest({1, 2, 0, 0}, {1, 2, 0, 0}, 7);
    runTest({-1, 0, 4, 0, -3}, {-1, 4, -3, 0, 0}, 8);
    runTest({0, 1, 0, 0, 2}, {1, 2, 0, 0, 0}, 9);
    runTest({4, 0, 5, 0, 0, 6}, {4, 5, 6, 0, 0, 0}, 10);

    return 0;
}
