#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// ============================================================
// PROBLEM: TRAPPING RAIN WATER
// LeetCode #42
// ============================================================
//
// PST:
// Given an integer array height where each element represents
// the height of a bar of width 1, return how much rainwater
// can be trapped between the bars after it rains.
//
// EXAMPLE 1:
// Input:  height = [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
//
// EXAMPLE 2:
// Input:  height = [4,2,0,3,2,5]
// Output: 9
//
// CONSTRAINTS:
// - 1 <= height.size() <= 2 * 10^4
// - 0 <= height[i] <= 10^5
//
// LeetCode:
// https://leetcode.com/problems/trapping-rain-water/
//
// YOUR TASK:
// 1. Start with your own reasoning.
// 2. Try to understand how water gets trapped.
// 3. Implement your solution.
// 4. Test and analyze time and space complexity.
// ============================================================

class Solution {
public:
    int trap(vector<int>& height) {
        // TODO: Implement your solution.
    }
};

int main() {
    Solution solution;

    // TC1: Standard example
    {
        vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
        assert(solution.trap(height) == 6);
        cout << "TC1 passed: Standard example\n";
    }

    // TC2: Example with a deep basin
    {
        vector<int> height = {4,2,0,3,2,5};
        assert(solution.trap(height) == 9);
        cout << "TC2 passed: Deep basin\n";
    }

    // TC3: No water can be trapped
    {
        vector<int> height = {1,2,3,4,5};
        assert(solution.trap(height) == 0);
        cout << "TC3 passed: Increasing heights\n";
    }

    // TC4: Decreasing heights
    {
        vector<int> height = {5,4,3,2,1};
        assert(solution.trap(height) == 0);
        cout << "TC4 passed: Decreasing heights\n";
    }

    // TC5: All bars have equal height
    {
        vector<int> height = {3,3,3,3};
        assert(solution.trap(height) == 0);
        cout << "TC5 passed: Equal heights\n";
    }

    // TC6: Two bars cannot trap water
    {
        vector<int> height = {3,0};
        assert(solution.trap(height) == 0);
        cout << "TC6 passed: Two bars\n";
    }

    // TC7: A single basin
    {
        vector<int> height = {3,0,2};
        assert(solution.trap(height) == 2);
        cout << "TC7 passed: Single basin\n";
    }

    // TC8: Multiple basins
    {
        vector<int> height = {3,0,1,3,0,5};
        assert(solution.trap(height) == 8);
        cout << "TC8 passed: Multiple basins\n";
    }

    // TC9: Empty space between tall boundaries
    {
        vector<int> height = {5,0,0,0,5};
        assert(solution.trap(height) == 15);
        cout << "TC9 passed: Tall boundaries\n";
    }

    // TC10: No water with one bar
    {
        vector<int> height = {7};
        assert(solution.trap(height) == 0);
        cout << "TC10 passed: Single bar\n";
    }

    cout << "\nAll test cases passed!\n";
    return 0;
}
