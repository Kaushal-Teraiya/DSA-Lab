// ============================================================
// LeetCode #15 - 3Sum (Approach 2)
// Difficulty: Medium
// Topics: Arrays, Sorting, Two Pointers
// ============================================================
//
// PROBLEM:
// Given an integer array nums, return all unique triplets
// [nums[i], nums[j], nums[k]] such that:
//
// i != j, i != k, j != k
// nums[i] + nums[j] + nums[k] == 0
//
// The solution must not contain duplicate triplets.
//
// EXAMPLE 1:
// Input:  nums = {-1, 0, 1, 2, -1, -4}
// Output: {{-1, -1, 2}, {-1, 0, 1}}
//
// EXAMPLE 2:
// Input:  nums = {0, 1, 1}
// Output: {}
//
// EXAMPLE 3:
// Input:  nums = {0, 0, 0}
// Output: {{0, 0, 0}}
//
// CONSTRAINTS:
// 3 <= nums.size() <= 3000
// -10^5 <= nums[i] <= 10^5
//
// HINTS:
// 1. Consider sorting the array.
// 2. Fix one element and search for two others.
// 3. Avoid duplicate triplets.
//
// TARGET:
// Time: O(n^2)
// Space: Depends on your implementation.
//
// ============================================================

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        // Your implementation goes here.
        int n = nums.size();
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }

            int left = i + 1;
            int right = n - 1;

            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0)
                {
                    ans.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    right--;

                    while (left < right && nums[left] == nums[left - 1])
                    {
                        left++;
                    }

                    while (left < right && nums[right] == nums[right + 1])
                    {
                        right--;
                    }
                }
                else if (sum < 0)
                {
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }
        return ans;
    }
};

// -------------------- TEST HARNESS --------------------

void runTest(vector<int> nums,
             vector<vector<int>> expected,
             int testNumber)
{
    Solution solution;
    vector<vector<int>> actual = solution.threeSum(nums);

    // Sort results so ordering does not affect comparison.
    for (auto &triplet : actual)
    {
        sort(triplet.begin(), triplet.end());
    }

    for (auto &triplet : expected)
    {
        sort(triplet.begin(), triplet.end());
    }

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Expected: ";
        for (const auto &triplet : expected)
        {
            cout << "[";
            for (int x : triplet)
                cout << x << " ";
            cout << "] ";
        }

        cout << "\nActual: ";
        for (const auto &triplet : actual)
        {
            cout << "[";
            for (int x : triplet)
                cout << x << " ";
            cout << "] ";
        }
        cout << '\n';
    }
}

int main()
{
    runTest({-1, 0, 1, 2, -1, -4},
            {{-1, -1, 2}, {-1, 0, 1}}, 1);

    runTest({0, 1, 1}, {}, 2);

    runTest({0, 0, 0}, {{0, 0, 0}}, 3);

    runTest({-2, 0, 1, 1, 2},
            {{-2, 0, 2}, {-2, 1, 1}}, 4);

    runTest({-1, -1, -1, 2, 2},
            {{-1, -1, 2}}, 5);

    return 0;
}
