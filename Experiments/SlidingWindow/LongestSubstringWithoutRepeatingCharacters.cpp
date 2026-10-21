#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #3 — Longest Substring Without Repeating Characters
Difficulty: Medium
Topic: Sliding Window, Hashing

PROBLEM:
Given a string s, find the length of the longest substring
without repeating characters.

A substring is a contiguous sequence of characters.

EXAMPLES:
Input: "abcabcbb"  -> Output: 3  ("abc")
Input: "bbbbb"     -> Output: 1  ("b")
Input: "pwwkew"    -> Output: 3  ("wke")

YOUR TASK:
Implement int lengthOfLongestSubstring(string s).

TEST CASES:
1. "abcabcbb"       -> 3
2. "bbbbb"          -> 1
3. "pwwkew"         -> 3
4. ""               -> 0
5. "a"              -> 1
6. "abcdef"         -> 6
7. "abba"           -> 2
8. "dvdf"            -> 3
9. "tmmzuxt"        -> 5
10. "anviaj"        -> 5

TARGET:
- Time: O(n)
- Extra space: O(min(n, alphabet size))
*/

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        // TODO: Implement your solution.
        unordered_map<char, int> freq;
        int n = s.size();
        int left = 0;
        int right = 0;
        int maxLength = 0;

        while (right < n)
        {
            freq[s[right]]++;

            if (freq[s[right]] < 2)
            {
                maxLength = max(maxLength, right - left + 1);
                right++;
            }
            else
            {
                while (freq[s[right]] != 1)
                {
                    freq[s[left]]--;
                    left++;
                }

                right++;
            }
        }

        return maxLength;
    }
};

void runTest(string s, int expected, int testNumber)
{
    Solution solution;
    int actual = solution.lengthOfLongestSubstring(s);

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Input:    \"" << s << "\"\n";
        cout << "Expected: " << expected << '\n';
        cout << "Actual:   " << actual << '\n';
    }
}

int main()
{
    runTest("abcabcbb", 3, 1);
    runTest("bbbbb", 1, 2);
    runTest("pwwkew", 3, 3);
    runTest("", 0, 4);
    runTest("a", 1, 5);
    runTest("abcdef", 6, 6);
    runTest("abba", 2, 7);
    runTest("dvdf", 3, 8);
    runTest("tmmzuxt", 5, 9);
    runTest("anviaj", 5, 10);

    return 0;
}
