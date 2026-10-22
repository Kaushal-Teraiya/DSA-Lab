#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #162 � Find Peak Element
Difficulty: Medium
Topic: Binary Search

PROBLEM:
A peak element is an element that is strictly greater than
its neighbors.

Given a 0-indexed integer array nums, find a peak element
and return its index.

If the array contains multiple peaks, return the index of
any peak.

Assume nums[-1] = nums[n] = -infinity.

You must solve this in O(log n) time.

EXAMPLES:
1. nums = {1, 2, 3, 1}
   Output: 2

2. nums = {1, 2, 1, 3, 5, 6, 4}
   Output: 1 or 5

TEST CASES:
1. {1, 2, 3, 1}           -> 2
2. {1, 2, 1, 3, 5, 6, 4} -> 1 or 5
3. {1}                    -> 0
4. {1, 2}                 -> 1
5. {2, 1}                 -> 0
6. {1, 2, 3, 4, 5}        -> 4
7. {5, 4, 3, 2, 1}        -> 0
8. {1, 3, 2}              -> 1
9. {2, 1, 2, 1, 2}        -> 0, 2, or 4
10. {1, 3, 5, 4, 2}       -> 2

TARGET:
Time: O(log n)
Extra space: O(1)
*/

class Solution
{
public:
    int findPeakElement(vector<int> &nums)
    {
        // TODO: Solve it yourself.
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        int mid = left + (right - left) / 2;

        while (left < right)
        {
            mid = left + (right - left) / 2;

            if (nums[mid] < nums[mid + 1])
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return left;
    }
};

bool isPeak(const vector<int> &nums, int index)
{
    bool leftOK = (index == 0 || nums[index] > nums[index - 1]);
    bool rightOK = (index == (int)nums.size() - 1 ||
                    nums[index] > nums[index + 1]);
    return leftOK && rightOK;
}

void runTest(vector<int> nums, vector<int> validAnswers, int testNumber)
{
    Solution solution;
    int actual = solution.findPeakElement(nums);

    bool valid = actual >= 0 &&
                 actual < (int)nums.size() &&
                 isPeak(nums, actual);

    cout << "Test " << testNumber << ": "
         << (valid ? "PASS" : "FAIL") << '\n';

    if (!valid)
    {
        cout << "Returned index: " << actual << '\n';
    }
}

int main()
{
    runTest({1, 2, 3, 1}, {2}, 1);
    runTest({1, 2, 1, 3, 5, 6, 4}, {1, 5}, 2);
    runTest({1}, {0}, 3);
    runTest({1, 2}, {1}, 4);
    runTest({2, 1}, {0}, 5);
    runTest({1, 2, 3, 4, 5}, {4}, 6);
    runTest({5, 4, 3, 2, 1}, {0}, 7);
    runTest({1, 3, 2}, {1}, 8);
    runTest({2, 1, 2, 1, 2}, {0, 2, 4}, 9);
    runTest({1, 3, 5, 4, 2}, {2}, 10);
    return 0;
}
