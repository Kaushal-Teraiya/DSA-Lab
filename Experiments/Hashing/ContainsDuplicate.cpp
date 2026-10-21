#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #217 — Contains Duplicate
Difficulty: Easy
Topics: Array, Hashing

PROBLEM STATEMENT:
Given an integer array nums, return true if any value appears
at least twice in the array. Return false if every element
is distinct.

EXAMPLE 1:
Input: nums = {1, 2, 3, 1}
Output: true

EXAMPLE 2:
Input: nums = {1, 2, 3, 4}
Output: false

EXAMPLE 3:
Input: nums = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2}
Output: true

YOUR TASK:
Implement bool containsDuplicate(vector<int>& nums).

TEST CASES:
1. {1, 2, 3, 1}                 -> true
2. {1, 2, 3, 4}                 -> false
3. {1, 1, 1, 1}                 -> true
4. {1}                          -> false
5. {-1, -2, -3, -1}             -> true
6. {0, 0}                       -> true
7. {1, 2, 3, 4, 5, 6}            -> false
8. {5, 4, 3, 2, 1, 5}            -> true
9. {-1000000, 1000000, 0}        -> false
10. {2, 3, 4, 5, 6, 2, 7}       -> true

Try to achieve:
- Time complexity: O(n)
- Extra space: O(n)

You can solve this using an unordered_set or unordered_map.
*/

class Solution
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        // TODO: Implement your solution.
        int n = nums.size();
        unordered_map<int, int> seen;

        for (int num : nums)
        {
            seen[num]++;
            if (seen[num] > 1)
                return true;
        }

        return false;
    }
};

void runTest(vector<int> nums, bool expected, int testNumber)
{
    Solution solution;
    bool actual = solution.containsDuplicate(nums);

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << boolalpha;
        cout << "Expected: " << expected << '\n';
        cout << "Actual:   " << actual << '\n';
    }
}

int main()
{
    runTest({1, 2, 3, 1}, true, 1);
    runTest({1, 2, 3, 4}, false, 2);
    runTest({1, 1, 1, 1}, true, 3);
    runTest({1}, false, 4);
    runTest({-1, -2, -3, -1}, true, 5);
    runTest({0, 0}, true, 6);
    runTest({1, 2, 3, 4, 5, 6}, false, 7);
    runTest({5, 4, 3, 2, 1, 5}, true, 8);
    runTest({-1000000, 1000000, 0}, false, 9);
    runTest({2, 3, 4, 5, 6, 2, 7}, true, 10);

    return 0;
}
