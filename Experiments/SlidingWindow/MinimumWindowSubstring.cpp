#include <bits/stdc++.h>
using namespace std;

/*
============================================================
LeetCode #76 - Minimum Window Substring
Difficulty: Hard
Topic: Sliding Window + Hashing
============================================================

PROBLEM STATEMENT:
Given two strings s and t, return the minimum window substring
of s such that every character in t (including duplicates)
is included in the window.

If no such substring exists, return "".

EXAMPLE 1:
Input:  s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"

EXAMPLE 2:
Input:  s = "a", t = "a"
Output: "a"

EXAMPLE 3:
Input:  s = "a", t = "aa"
Output: ""

CONSTRAINTS:
- 1 <= s.length(), t.length() <= 100000
- s and t consist of uppercase and lowercase English letters.
- The answer is unique when it exists.

YOUR TASK:
Implement:
string minWindow(string s, string t);

HINTS:
- Count required character frequencies in t.
- Expand the window by moving right.
- Track how many required character occurrences are matched.
- Once valid, shrink from the left to find a smaller window.
- Save the smallest valid window.

TEST CASES:
1.  s="ADOBECODEBANC", t="ABC" -> "BANC"
2.  s="a", t="a"                 -> "a"
3.  s="a", t="aa"                -> ""
4.  s="AAABBC", t="AABC"         -> "ABBC"
5.  s="ABCXYZ", t="ABC"          -> "ABC"
6.  s="XYZABC", t="ABC"          -> "ABC"
7.  s="aAbBcC", t="ABC"          -> "ABC"
8.  s="abdabca", t="aabc"        -> "abca"
9.  s="bba", t="ab"              -> "ba"
10. s="cabwefgewcwaefgcf", t="cae" -> "cwae"

Target complexity:
Time: O(m + n)
Space: O(1) for a fixed character set.
============================================================
*/

class Solution
{
public:
   string minWindow(string s, string t)
   {
      // TODO: Implement your solution.

      //store sizes of strings.
      int n = s.size();
      int m = t.size();

      //used to store frequency of each character from string t
      unordered_map<char, int> freq;

      //left and right pointers.. left for window shrinking and right for expanding.
      int left = 0;
      int right = 0;

      //Count stores how many required occurrences have we matched so far.
      int count = 0;
      int smallestLen = INT_MAX;

      int ansStringStartPoint = 0;

      // Step 1: Count required characters in t.
      for (char c : t)
      {
         freq[c]++;
      }

      // Continue your implementation here.

      //right pointer should stay in the bounds.
      while (right < n)
      {
         //character exists in the frequency map
         if (freq.find(s[right]) != freq.end())
         {
            //if character freq is > 0 it means the characters havent yet been encountered.
            //so increase the count once.
            if (freq[s[right]] > 0)
            {
               count++;
            }

            //decrease freq for that character meaning we have found one of its occurrences in string s.
            freq[s[right]]--;
         }

         while (count == m) //when count == m it means we have found a valid window , it countains all the characters from string t.
         {
            //+1 is used when both pointers are included.. if right and left are on the same element it points to atleast 1.
            int windowLen = right - left + 1;

            if (windowLen < smallestLen)
            {
               smallestLen = windowLen; //update new smallest length.
               ansStringStartPoint = left; //only update when smaller window than before is found.
            }

            //when we find a vaid window we go on to search another valid window. by shrinking the size using left++
            if (freq.find(s[left]) != freq.end())
            {
               //freq == 0 means that character exists exactly required amount of times in the window.
               if (freq[s[left]] == 0)
               {
                  count--;//decrease the count since we are going to shrink the window.
               }

               freq[s[left]]++; // increasing the freq means the now the character is yet to be found freq amount of times.
            }

            left++; //shrinks the window.
         }

         right++; //expand the window regardless.
      }

      //if after doing allat it still stays INT_MAX return an {} string.
      if (smallestLen == INT_MAX)
      {
         return {};
      }

      //substring takes in the starting index which we stored as the starting of the smallest window.
      //smallest len is the length we want for the substring.
      return s.substr(ansStringStartPoint, smallestLen);
   }
};

void runTest(string s, string t, string expected, int testNumber)
{
   Solution solution;
   string actual = solution.minWindow(s, t);

   cout << "Test " << testNumber << ": "
        << (actual == expected ? "PASS" : "FAIL") << '\n';

   if (actual != expected)
   {
      cout << "Expected: \"" << expected << "\"\n";
      cout << "Actual:   \"" << actual << "\"\n";
   }
}

int main()
{
   runTest("ADOBECODEBANC", "ABC", "BANC", 1);
   runTest("a", "a", "a", 2);
   runTest("a", "aa", "", 3);
   runTest("AAABBC", "AABC", "AABBC", 4);
   runTest("ABCXYZ", "ABC", "ABC", 5);
   runTest("XYZABC", "ABC", "ABC", 6);
   runTest("aAbBcC", "ABC", "AbBcC", 7);
   runTest("abdabca", "aabc", "abca", 8);
   runTest("bba", "ab", "ba", 9);
   runTest("cabwefgewcwaefgcf", "cae", "cwae", 10);

   return 0;
}

