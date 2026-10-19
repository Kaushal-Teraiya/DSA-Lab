// ============================================================
// PROBLEM: GROUP ANAGRAMS
// LeetCode #49
// Difficulty: Medium
// ============================================================
//
// Given an array of strings strs, group the anagrams together.
// You may return the answer in any order.
//
// EXAMPLE 1:
// Input: strs = {"eat","tea","tan","ate","nat","bat"}
// Output: {{"bat"},{"nat","tan"},{"ate","eat","tea"}}
//
// EXAMPLE 2:
// Input: strs = {""}
// Output: {{""}}
//
// EXAMPLE 3:
// Input: strs = {"a"}
// Output: {{"a"}}
//
// CONSTRAINTS:
// 1 <= strs.length <= 10^4
// 0 <= strs[i].length <= 100
// strs[i] consists of lowercase English letters.
//
// YOUR TASK:
// 1. Start with your own reasoning.
// 2. Experiment freely in this local file.
// 3. Try a brute-force approach before optimizing.
// 4. Analyze time and space complexity.
//
// FOLLOW-UP:
// Can you group the anagrams in O(n * m log m) time,
// where n is the number of strings and m is the maximum
// string length?
//
// ============================================================

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        // TODO: Implement your solution.
        // Start with your own reasoning!
        unordered_map<string, vector<string>> groups;
        vector<vector<string>> finalResult;
        vector<string> copy = strs;
        int n = strs.size();

        for (int i = 0; i < n; i++)
        {
            sort(copy[i].begin(), copy[i].end());
            groups[copy[i]].push_back(strs[i]);
        }

        for (auto it : groups)
        {
            finalResult.push_back(it.second);
        }

        return finalResult;
    }
};

// Compare groups without depending on output order.
bool matches(vector<vector<string>> actual,
             vector<vector<string>> expected)
{
    for (auto &group : actual)
    {
        sort(group.begin(), group.end());
    }

    for (auto &group : expected)
    {
        sort(group.begin(), group.end());
    }

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());

    return actual == expected;
}

int main()
{
    Solution solution;

    // Test 1: Standard example
    {
        vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
        vector<vector<string>> expected = {
            {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}};

        assert(matches(solution.groupAnagrams(strs), expected));
        cout << "Test 1 passed!\n";
    }

    // Test 2: Empty string
    {
        vector<string> strs = {""};
        vector<vector<string>> expected = {{""}};

        assert(matches(solution.groupAnagrams(strs), expected));
        cout << "Test 2 passed!\n";
    }

    // Test 3: Single character
    {
        vector<string> strs = {"a"};
        vector<vector<string>> expected = {{"a"}};

        assert(matches(solution.groupAnagrams(strs), expected));
        cout << "Test 3 passed!\n";
    }

    // Test 4: No anagrams
    {
        vector<string> strs = {"abc", "def", "ghi"};
        vector<vector<string>> expected = {{"abc"}, {"def"}, {"ghi"}};

        assert(matches(solution.groupAnagrams(strs), expected));
        cout << "Test 4 passed!\n";
    }

    // Test 5: All strings are anagrams
    {
        vector<string> strs = {"listen", "silent", "enlist", "inlets"};
        vector<vector<string>> expected = {
            {"listen", "silent", "enlist", "inlets"}};

        assert(matches(solution.groupAnagrams(strs), expected));
        cout << "Test 5 passed!\n";
    }

    // Test 6: Duplicate strings
    {
        vector<string> strs = {"abc", "abc", "bca", "cab"};
        vector<vector<string>> expected = {{"abc", "abc", "bca", "cab"}};

        assert(matches(solution.groupAnagrams(strs), expected));
        cout << "Test 6 passed!\n";
    }

    // Test 7: Different lengths
    {
        vector<string> strs = {"a", "ab", "ba", "abc", "bca", "abcd"};
        vector<vector<string>> expected = {
            {"a"}, {"ab", "ba"}, {"abc", "bca"}, {"abcd"}};

        assert(matches(solution.groupAnagrams(strs), expected));
        cout << "Test 7 passed!\n";
    }

    // Test 8: Repeated characters
    {
        vector<string> strs = {"aab", "aba", "baa", "abb", "bab", "bba"};
        vector<vector<string>> expected = {
            {"aab", "aba", "baa"}, {"abb", "bab", "bba"}};

        assert(matches(solution.groupAnagrams(strs), expected));
        cout << "Test 8 passed!\n";
    }

    cout << "\nAll test cases passed!\n";
    return 0;
}
