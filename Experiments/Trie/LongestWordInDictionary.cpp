/*
LeetCode 720 - Longest Word in Dictionary
Difficulty: Medium
Topic: Trie
Pattern: Trie Traversal / Prefix Validation

PROBLEM
Given an array of strings words representing an English dictionary,
return the longest word that can be built one character at a time
by other words in the dictionary.

If there is more than one possible answer, return the
lexicographically smallest one. If no answer exists, return "".

EXAMPLE 1
Input: words = {"w", "wo", "wor", "worl", "world"}
Output: "world"

EXAMPLE 2
Input: words = {"a", "banana", "app", "appl", "ap",
                "apply", "apple"}
Output: "apple"

CONSTRAINTS
- 1 <= words.length <= 1000
- 1 <= words[i].length <= 30
- words[i] consists of lowercase English letters.
- All strings in words are distinct.

LEETCODE SIGNATURE
string longestWord(vector<string>& words)

IMPLEMENTATION PLAN
1. Build a Trie containing every dictionary word.
2. Mark isEnd only at the final node of each inserted word.
3. Sort words lexicographically.
4. Validate each candidate by checking isEnd at every prefix node.
5. Keep the longest valid word; preserve the first in a tie.
6. Return the answer.

TODO: Implement the algorithm yourself.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct TrieNode
{
    TrieNode *children[26];
    bool isEnd;

    TrieNode()
    {
        for (int i = 0; i < 26; ++i)
            children[i] = nullptr;

        isEnd = false;
    }
};

class Solution
{
public:
    TrieNode *root;

    Solution()
    {
        root = new TrieNode();
    }

    void insert(string word)
    {
        // TODO: Implement insertion.
        // Initial root empty
        TrieNode *current = root;

        for (char c : word)
        {
            int index = c - 'a';

            if (current->children[index] == nullptr)
            {
                TrieNode *newNode = new TrieNode();
                current->children[index] = newNode;
            }
            current = current->children[index];
        }

        current->isEnd = true;
    }

    string longestWord(vector<string> &words)
    {
        //  Sort words lexicographically.
        //  Insert every word into the Trie.
        //  Validate every candidate word.
        //  Track and return the longest valid word.

        int n = words.size();
        sort(words.begin(), words.end()); //lexicoghraphical sorting

        for (int i = 0; i < n; i++)
        {
            //Build the trie
            insert(words[i]); //insert funciton from //"Implement Trie file"
        }

        string longestWordFound = "";

        for (int i = 0; i < n; i++)
        {
            //reset to root for each word so the processing starts fresh
            //isValid tracks whether all the characters have been valid till now
            TrieNode *current = root;
            bool isValid = true;

            for (char c : words[i])
            {
                //calc the index
                //update current to its children
                int index = c - 'a';
                current = current->children[index];
                
                //if a letter never existed in the trie to begin with , 
                //then that word is invalid and can't build the longest string.
                if (!current->isEnd)
                {
                    isValid = false;
                    break;
                }
            }

            //if everything was valid and new words size is more than the longest seen so far
            if (isValid && words[i].size() > longestWordFound.size())
            {
                //update it
                longestWordFound = words[i];
            }
        }

        //answer is here after both the loops end running.
        return longestWordFound;
    }
};

struct TestCase
{
    string name;
    vector<string> words;
    string expected;
};

int main()
{
    vector<TestCase> tests = {
        {"Example 1",
         {"w", "wo", "wor", "worl", "world"},
         "world"},
        {"Example 2 - Lexicographical Tie",
         {"a", "banana", "app", "appl", "ap",
          "apply", "apple"},
         "apple"},
        {"Missing Intermediate Prefix",
         {"a", "ab", "abc", "abde"},
         "abc"},
        {"Only One Buildable Word",
         {"hello", "a", "banana"},
         "a"},
        {"Single Character",
         {"z"},
         "z"},
        {"Lexicographical Tie at Length One",
         {"b", "a"},
         "a"}};

    int passed = 0;
    int failed = 0;

    cout << "========== TEST SUMMARY ==========\n";

    for (const auto &test : tests)
    {
        Solution solution;
        vector<string> input = test.words;
        string actual = solution.longestWord(input);

        if (actual == test.expected)
        {
            ++passed;
            cout << "[PASS] " << test.name << '\n';
        }
        else
        {
            ++failed;
            cout << "[FAIL] " << test.name << '\n';
        }
    }

    cout << "\nPassed: " << passed << '/' << tests.size() << '\n';
    cout << "Failed: " << failed << '/' << tests.size() << '\n';

    if (failed > 0)
    {
        cout << "\n========== FAILURE DETAILS ==========\n";

        for (const auto &test : tests)
        {
            Solution solution;
            vector<string> input = test.words;
            string actual = solution.longestWord(input);

            if (actual != test.expected)
            {
                cout << "Test: " << test.name << '\n';
                cout << "Expected: \"" << test.expected << "\"\n";
                cout << "Actual:   \"" << actual << "\"\n\n";
            }
        }
    }

    return failed == 0 ? 0 : 1;
}
