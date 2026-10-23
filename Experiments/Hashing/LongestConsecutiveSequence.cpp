// ============================================================
// LeetCode #128 - Longest Consecutive Sequence
// Difficulty: Medium
// Topics: Array, Hashing
// ============================================================
//
// PROBLEM:
// Given an unsorted array of integers nums, return the length
// of the longest consecutive elements sequence.
//
// The algorithm must run in O(n) time.
//
// EXAMPLE 1:
// Input:  nums = [100, 4, 200, 1, 3, 2]
// Output: 4
// Explanation: The longest consecutive sequence is [1, 2, 3, 4].
//
// EXAMPLE 2:
// Input:  nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
// Output: 9
//
// EXAMPLE 3:
// Input:  nums = [1, 0, 1, 2]
// Output: 3
//
// CONSTRAINTS:
// - 0 <= nums.length <= 10^5
// - -10^9 <= nums[i] <= 10^9
//
// HINTS (try without these first):
// Hint 1: The numbers are unsorted. Does their original order matter?
// Hint 2: What makes a sequence consecutive?
// Hint 3: The required time complexity is O(n).
//
// ============================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        // TODO: Derive and implement your approach.
        unordered_set<int> seen;
        int n = nums.size();

        int longestLen = 0;

        if (n <= 0)
        {
            return 0;
        }

        for (int num : nums)
        {
            seen.insert(num);
        }

        for (int num : seen)
        {
            if (seen.find(num - 1) == seen.end()) //start of the sequence
            {
                
                int currLen = 1;
                int currNum = num;

                while (seen.find(currNum + 1) != seen.end()) // checks continuation.
                {
                    currLen++; //length of the current sequence 
                    currNum++; //increase currNum by 1 and find in the set.
                }
                longestLen = max(longestLen, currLen); //keep track of the longest length.
            }
        }
        return longestLen;
    }
};

int main()
{
    Solution solution;

    vector<pair<vector<int>, int>> tests = {
        {{100, 4, 200, 1, 3, 2}, 4},
        {{0, 3, 7, 2, 5, 8, 4, 6, 0, 1}, 9},
        {{1, 0, 1, 2}, 3},
        {{}, 0},
        {{5}, 1},
        {{10, 11, 12, 20, 21}, 3},
        {{-2, -1, 0, 1}, 4}};

    for (int i = 0; i < (int)tests.size(); i++)
    {
        vector<int> nums = tests[i].first;
        int expected = tests[i].second;
        int actual = solution.longestConsecutive(nums);

        cout << "Test " << i + 1
             << " | Expected: " << expected
             << " | Actual: " << actual
             << " | " << (actual == expected ? "PASS" : "FAIL")
             << '\n';
    }

    return 0;
}
