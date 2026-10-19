// ============================================================
// PROBLEM: TOP K FREQUENT ELEMENTS
// LeetCode #347
// ============================================================
//
// Given an integer array nums and an integer k, return the k
// elements that appear most frequently.
//
// The answer may be returned in any order.
//
// EXAMPLE 1:
// Input: nums = [1,1,1,2,2,3], k = 2
// Output: [1,2]
//
// EXAMPLE 2:
// Input: nums = [1], k = 1
// Output: [1]
//
// EXAMPLE 3:
// Input: nums = [4,4,4,7,7,2], k = 2
// Output: [4,7]
//
// CONSTRAINTS:
// 1 <= nums.size() <= 10^5
// -10^4 <= nums[i] <= 10^4
// 1 <= k <= number of unique elements
// The answer is guaranteed to be unique.
//
// YOUR TASK:
// 1. Start with your own reasoning.
// 2. Experiment freely in this local file.
// 3. Try a brute-force approach before optimizing.
// 4. Analyze time and space complexity.
//
// FOLLOW-UP:
// Can you solve it in better than O(n log n) time?
//
// LeetCode:
// https://leetcode.com/problems/top-k-frequent-elements/
//
// ============================================================

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        // TODO: Implement your solution.
        // Start with your own reasoning!
        unordered_map<int, int> map;

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>>
            minHeap;

        int n = nums.size();
        vector<int> result;

        for (int num : nums)
        {
            map[num]++;
        }

        for (auto it : map)
        {
            /* code */
            minHeap.push({it.second , it.first});

            if (minHeap.size() > k)
            {
                minHeap.pop();
            }
        }

        while (!minHeap.empty())
        {
            /* code */
            pair<int, int> pair = minHeap.top();
            result.push_back(pair.second);
            minHeap.pop();
        }

        return result;
    }
};

bool matches(vector<int> actual, vector<int> expected)
{
    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    return actual == expected;
}

int main()
{
    Solution solution;

    // Test 1: Standard example
    {
        vector<int> nums = {1, 1, 1, 2, 2, 3};
        vector<int> actual = solution.topKFrequent(nums, 2);

        cout << "Returned: ";
        for (int x : actual)
        {
            cout << x << " ";
        }
        cout << endl;

        assert(matches(actual, {1, 2}));
        cout << "Test 1 passed!\n";
    }

    // Test 2: Single element
    {
        vector<int> nums = {1};
        assert(matches(solution.topKFrequent(nums, 1), {1}));
        cout << "Test 2 passed!\n";
    }

    // Test 3: Different frequencies
    {
        vector<int> nums = {4, 4, 4, 7, 7, 2};
        assert(matches(solution.topKFrequent(nums, 2), {4, 7}));
        cout << "Test 3 passed!\n";
    }

    // Test 4: Negative numbers
    {
        vector<int> nums = {-1, -1, -1, 2, 2, 3};
        assert(matches(solution.topKFrequent(nums, 2), {-1, 2}));
        cout << "Test 4 passed!\n";
    }

    // Test 5: All elements have equal frequency; k includes all
    {
        vector<int> nums = {5, 5, 8, 8, 9, 9};
        assert(matches(solution.topKFrequent(nums, 3), {5, 8, 9}));
        cout << "Test 5 passed!\n";
    }

    // Test 6: k equals the number of unique elements
    {
        vector<int> nums = {2, 2, 3, 3, 4};
        assert(matches(solution.topKFrequent(nums, 3), {2, 3, 4}));
        cout << "Test 6 passed!\n";
    }

    cout << "\nAll test cases passed!\n";
    return 0;
}
