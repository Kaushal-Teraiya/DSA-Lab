#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #242 — Valid Anagram
Difficulty: Easy
Topics: Hashing, Strings

PROBLEM STATEMENT:
Given two strings s and t, return true if t is an anagram of s,
and false otherwise.

An anagram is formed by rearranging all the letters of another
string, using every character the same number of times.

EXAMPLES:
s = "anagram", t = "nagaram" -> true
s = "rat", t = "car"         -> false

CONSTRAINTS:
- s and t contain lowercase English letters.
- 1 <= s.length, t.length <= 5 * 10^4

YOUR TASK:
Implement bool isAnagram(string s, string t).

TEST CASES:
1. "anagram", "nagaram" -> true
2. "rat", "car"         -> false
3. "a", "a"             -> true
4. "a", "b"             -> false
5. "listen", "silent"   -> true
6. "hello", "bello"     -> false
7. "aabb", "bbaa"       -> true
8. "aacc", "ccac"       -> false
9. "abc", "ab"          -> false
10. "", ""              -> true

TARGET:
- Time: O(n)
- Extra space: O(1) for a fixed 26-letter alphabet.
*/

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        // TODO: Implement your solution.
        vector<int> freq(26, 0);
        int n = s.size();
        int m = t.size();

        if (n != m)
        {
            return false;
        }

        for (int i = 0; i < n; i++)
        {
            freq[s[i] - 'a']++;
        }

        for (int i = 0; i < m; i++)
        {
            freq[t[i] - 'a']--;
        }

        for (int num : freq)
        {
            if (num != 0)
                return false;
        }

        return true;
    }
};

void runTest(string s, string t, bool expected, int testNumber)
{
    Solution solution;
    bool actual = solution.isAnagram(s, t);

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
    runTest("anagram", "nagaram", true, 1);
    runTest("rat", "car", false, 2);
    runTest("a", "a", true, 3);
    runTest("a", "b", false, 4);
    runTest("listen", "silent", true, 5);
    runTest("hello", "bello", false, 6);
    runTest("aabb", "bbaa", true, 7);
    runTest("aacc", "ccac", false, 8);
    runTest("abc", "ab", false, 9);
    runTest("", "", true, 10);

    return 0;
}
