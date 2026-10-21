#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #11 — Container With Most Water
Difficulty: Medium
Topic: Two Pointers

PROBLEM STATEMENT:
You are given an integer array height of length n.
There are n vertical lines where the endpoints of the
ith line are (i, 0) and (i, height[i]).

Choose two lines that, together with the x-axis, form a
container that holds the most water.

Return the maximum amount of water the container can store.

IMPORTANT:
- You cannot slant the container.
- You must choose two different lines.
- Try to solve it in O(n) time using O(1) extra space.

EXAMPLE 1:
Input: height = {1, 8, 6, 2, 5, 4, 8, 3, 7}
Output: 49

EXAMPLE 2:
Input: height = {1, 1}
Output: 1

EXAMPLE 3:
Input: height = {4, 3, 2, 1, 4}
Output: 16

YOUR TASK:
Implement:
int maxArea(vector<int>& height);

TEST CASES:
1. {1, 8, 6, 2, 5, 4, 8, 3, 7} -> 49
2. {1, 1}                         -> 1
3. {4, 3, 2, 1, 4}                -> 16
4. {1, 2, 1}                      -> 2
5. {1, 2, 4, 3}                   -> 4
6. {2, 3, 4, 5, 18, 17, 6}       -> 17
7. {5, 5, 5, 5}                   -> 15
8. {1, 3, 2, 5, 25, 24, 5}       -> 24
9. {3, 9, 3, 4, 7, 2, 12, 6}     -> 36
10. {2, 2, 2}                    -> 4

HINTS FOR YOUR OWN REASONING:
- Width = distance between the two chosen indices.
- Water height is limited by the shorter line.
- The area is width multiplied by the shorter height.
- Think about which pointer to move after calculating the area.
*/

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        // TODO: Implement your solution.
        int n = height.size();
        int maxArea = 0;
        int left = 0;
        int right = n - 1;

        while (left < right)
        {
            if (height[left] < height[right])
            {
                maxArea = max(maxArea, (right - left) * height[left]);
                left++;
            }
            else if (height[left] > height[right])
            {
                maxArea = max(maxArea, (right - left) * height[right]);
                right--;
            }
            else
            {
                maxArea = max(maxArea, (right - left) * height[right]);
                left++;
            }
        }

        return maxArea;
    }
};

void runTest(vector<int> height, int expected, int testNumber)
{
    Solution solution;
    int actual = solution.maxArea(height);

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Expected: " << expected << '\n';
        cout << "Actual:   " << actual << '\n';
    }
}

int main()
{
    runTest({1, 8, 6, 2, 5, 4, 8, 3, 7}, 49, 1);
    runTest({1, 1}, 1, 2);
    runTest({4, 3, 2, 1, 4}, 16, 3);
    runTest({1, 2, 1}, 2, 4);
    runTest({1, 2, 4, 3}, 4, 5);
    runTest({2, 3, 4, 5, 18, 17, 6}, 17, 6);
    runTest({5, 5, 5, 5}, 15, 7);
    runTest({1, 3, 2, 5, 25, 24, 5}, 24, 8);
   runTest({3, 9, 3, 4, 7, 2, 12, 6}, 45, 9);
    runTest({2, 2, 2}, 4, 10);

    return 0;
}
