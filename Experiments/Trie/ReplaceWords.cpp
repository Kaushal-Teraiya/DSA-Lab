#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
LeetCode 648: Replace Words
Topic: Trie
Difficulty: Medium
=========================================================

PROBLEM STATEMENT
-----------------
You are given a dictionary of roots and a sentence consisting
of words separated by spaces.

Replace each word in the sentence with the shortest root
from the dictionary that is a prefix of that word.

If no dictionary root is a prefix of a word, keep the
original word.

Return the sentence after replacing the words.

EXAMPLE 1
---------
Input:
dictionary = {"cat", "bat", "rat"}
sentence = "the cattle was rattled by the battery"

Output:
"the cat was rat by the bat"

Explanation:
"cattle"  -> "cat"
"rattled" -> "rat"
"battery" -> "bat"

EXAMPLE 2
---------
Input:
dictionary = {"a", "b", "c"}
sentence = "aadsfasf absbs bbab cadsfafs"

Output:
"a a b c"

CONSTRAINTS
-----------
1 <= dictionary.length <= 1000
1 <= dictionary[i].length <= 100
1 <= sentence.length <= 10^6
dictionary[i] and sentence consist of lowercase letters.
All words in dictionary are distinct.
Sentence words are separated by a single space.

APPROACH NOTES
--------------
- Build a Trie using the dictionary roots.
- Mark the end of each dictionary root using isEnd.
- Process each sentence word independently.
- Find the shortest matching root, if one exists.
- Preserve the original word when no root matches.

Do not modify the test harness to make incorrect solutions pass.
=========================================================
*/

struct TrieNode
{
    TrieNode *children[26];
    bool isEnd;

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
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

    string replaceWords(vector<string> &dictionary, string sentence)
    {
        // TODO 1: Insert every dictionary root into the Trie.
        // TODO 2: Mark the final node of each root with isEnd.
        // TODO 3: Split the sentence into individual words.
        // TODO 4: Find the shortest matching root for each word.
        // TODO 5: Build and return the resulting sentence.
        TrieNode *current = root;
        for (int i = 0; i < dictionary.size(); i++)
        {
            current = root;
            for (char c : dictionary[i])
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

        stringstream ss(sentence);
        string word;
        string result = "";

        while (ss >> word)
        {
            TrieNode *current = root;
            string prefix = "";
            bool found = false;

            for (char c : word)
            {
                int index = c - 'a';
                if (current->children[index] == nullptr)
                {
                    break;
                }

                current = current->children[index];
                prefix += c;

                if (current->isEnd)
                {
                    found = true;
                    break;
                }
            }

            if (!result.empty())
            {
                result += " ";
            }

            if (found)
            {
                result += prefix;
            }
            else
            {
                result += word;
            }
        }

        return result;
    }
};

// ========================================================
// TEST HARNESS
// ========================================================

void runTest(
    int testNumber,
    vector<string> dictionary,
    string sentence,
    const string &expected)
{
    Solution solution;
    string actual = solution.replaceWords(dictionary, sentence);

    bool passed = (actual == expected);

    cout << "Test " << testNumber << ": "
         << (passed ? "PASS" : "FAIL") << '\n';

    if (!passed)
    {
        cout << "  Expected: \"" << expected << "\"\n";
        cout << "  Actual:   \"" << actual << "\"\n";
    }
}

int main()
{
    cout << "========== REPLACE WORDS ==========\n\n";

    int passed = 0;
    int total = 3;

    // Test 1: Standard example
    {
        vector<string> dictionary = {"cat", "bat", "rat"};
        string sentence = "the cattle was rattled by the battery";
        string expected = "the cat was rat by the bat";

        Solution solution;
        string actual = solution.replaceWords(dictionary, sentence);

        bool ok = (actual == expected);
        cout << "Test 1: " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok)
        {
            cout << "  Expected: \"" << expected << "\"\n";
            cout << "  Actual:   \"" << actual << "\"\n";
        }
        passed += ok;
    }

    // Test 2: Single-character roots
    {
        vector<string> dictionary = {"a", "b", "c"};
        string sentence = "aadsfasf absbs bbab cadsfafs";
        string expected = "a a b c";

        Solution solution;
        string actual = solution.replaceWords(dictionary, sentence);

        bool ok = (actual == expected);
        cout << "Test 2: " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok)
        {
            cout << "  Expected: \"" << expected << "\"\n";
            cout << "  Actual:   \"" << actual << "\"\n";
        }
        passed += ok;
    }

    // Test 3: Shortest matching root wins
    {
        vector<string> dictionary = {"c", "ca", "cat"};
        string sentence = "cattle car dog";
        string expected = "c c dog";

        Solution solution;
        string actual = solution.replaceWords(dictionary, sentence);

        bool ok = (actual == expected);
        cout << "Test 3: " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok)
        {
            cout << "  Expected: \"" << expected << "\"\n";
            cout << "  Actual:   \"" << actual << "\"\n";
        }
        passed += ok;
    }

    cout << "\n========== SUMMARY ==========\n";
    cout << "Passed: " << passed << "/" << total << '\n';
    cout << "Failed: " << total - passed << "/" << total << '\n';

    return (passed == total) ? 0 : 1;
}
