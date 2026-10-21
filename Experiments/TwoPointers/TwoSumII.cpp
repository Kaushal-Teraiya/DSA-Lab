#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #167 — Two Sum II: Input Array Is Sorted

PROBLEM:
Given a 1-indexed array of integers numbers that is sorted
in non-decreasing order, find two numbers that add up to target.

Return their indices as {index1, index2}, where:
- 1 <= index1 < index2 <= numbers.length
- Exactly one solution exists.
- You must use O(1) extra space.

EXAMPLES:
numbers = {2, 7, 11, 15}, target = 9
Output: {1, 2}

numbers = {2, 3, 4}, target = 6
Output: {1, 3}

numbers = {-1, 0}, target = -1
Output: {1, 2}

YOUR TASK:
Implement vector<int> twoSum(vector<int>& numbers, int target).

TEST CASES:
1. {2, 7, 11, 15}, target 9   -> {1, 2}
2. {2, 3, 4}, target 6        -> {1, 3}
3. {-1, 0}, target -1         -> {1, 2}
4. {1, 2, 3, 4, 5}, target 9  -> {4, 5}
5. {1, 3, 4, 5, 7, 11}, target 10 -> {3, 4}
6. {-5, -2, 0, 3, 9}, target 1 -> {2, 4}
7. {1, 2}, target 3           -> {1, 2}
8. {0, 0, 3, 4}, target 0     -> {1, 2}

Remember: returned indices are 1-based, not 0-based.
*/

class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        // TODO: Derive the two-pointer solution.
        int n = numbers.size();
        int leftPointer = 0;
        int rightPointer = n - 1;

        while (leftPointer < rightPointer)
        {
            int sum = numbers[leftPointer] + numbers[rightPointer];
            if (sum > target)
            {
                rightPointer--;
            }
            else if (sum < target)
            {
                leftPointer++;
            }
            else if (sum == target)
            {
                return {leftPointer + 1, rightPointer + 1};
            }
        }

        return {};
    }
};

void runTest(vector<int> numbers, int target,
             vector<int> expected, int testNumber)
{
    Solution solution;
    vector<int> actual = solution.twoSum(numbers, target);

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Expected: ";
        for (int x : expected)
            cout << x << ' ';
        cout << "\nActual:   ";
        for (int x : actual)
            cout << x << ' ';
        cout << '\n';
    }
}

int main()
{
    runTest({2, 7, 11, 15}, 9, {1, 2}, 1);
    runTest({2, 3, 4}, 6, {1, 3}, 2);
    runTest({-1, 0}, -1, {1, 2}, 3);
    runTest({1, 2, 3, 4, 5}, 9, {4, 5}, 4);
 runTest({1, 3, 4, 5, 7, 11}, 10, {2, 5}, 5);
    runTest({-5, -2, 0, 3, 9}, 1, {2, 4}, 6);
    runTest({1, 2}, 3, {1, 2}, 7);
    runTest({0, 0, 3, 4}, 0, {1, 2}, 8);

    return 0;
}
