#include <bits/stdc++.h>
using namespace std;

/*
============================================================
LeetCode 211: Design Add and Search Words Data Structure
Topic: Trie + DFS / Backtracking
Difficulty: Medium
============================================================

PROBLEM STATEMENT
-----------------
Design a data structure that supports adding words and
searching for words.

Implement the WordDictionary class:

    WordDictionary()
        Initializes the data structure.

    void addWord(string word)
        Adds word to the data structure.

    bool search(string word)
        Returns true if there is a previously added word
        matching the query. The character '.' can match
        any single lowercase English letter.

EXAMPLE
-------
Operations:
    addWord("bad")
    addWord("dad")
    addWord("mad")

Queries and results:
    search("pad")  -> false
    search("bad")  -> true
    search(".ad")  -> true
    search("b..")  -> true

CONSTRAINTS
-----------
1 <= word.length <= 25
Words added contain lowercase English letters.
Search queries contain lowercase letters or '.'.
At most 2 dots occur in a search query.
At most 10^4 calls are made to addWord and search.

APPROACH NOTES
--------------
- Store words in a Trie.
- Mark the final node of each word with isEnd.
- For a normal character, follow its matching child.
- For '.', explore every existing child using DFS.
- Return true if any branch matches the entire query.
- A matching path must end at a node marked isEnd.

============================================================
TODO CHECKLIST
============================================================
[ ] Implement addWord().
[ ] Implement the DFS helper.
[ ] Handle normal characters.
[ ] Handle the '.' wildcard with DFS.
[ ] Implement search() by starting DFS at the root.
[ ] Pass every test.
============================================================
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

class WordDictionary
{
private:
    TrieNode *root;

    // TODO: Implement recursive DFS.
    bool dfs(const string &word, TrieNode *currentNode, int charIndex)
    {
        // TODO 1: If charIndex == word.size(), return currentNode->isEnd.
        //
        // TODO 2: Read the current character.
        //
        // TODO 3: If the character is not '.':
        //         - Calculate its child index.
        //         - Return false if the child doesn't exist.
        //         - Otherwise recurse into that child at charIndex + 1.
        //
        // TODO 4: If the character is '.':
        //         - Loop through all 26 children.
        //         - Skip null children.
        //         - Recurse into each existing child at charIndex + 1.
        //         - Return true if any recursive call succeeds.
        //         - Return false if every branch fails.

        if (charIndex == word.size())
        {
            return currentNode->isEnd;
        }

        char c = word[charIndex];
        int index = c - 'a';

        if (c == '.')
        {
            for (int i = 0; i < 26; i++)
            {
                if (currentNode->children[i] == nullptr)
                {
                    continue;
                }

                if (dfs(word, currentNode->children[i], charIndex + 1))
                {
                    return true;
                }
            }

            return false;
        }

        if (currentNode->children[index] == nullptr)
        {
            return false;
        }
        else
        {
            return dfs(word, currentNode->children[index], charIndex + 1);
        }
    }

public:
    WordDictionary()
    {
        root = new TrieNode();
    }

    void addWord(string word)
    {
        // TODO 5: Start at the root.
        // TODO 6: Insert each character, creating missing nodes.
        // TODO 7: Mark the final node as a complete word.
        TrieNode *current = root;

        for (char c : word)
        {
            int index = c - 'a';

            if (current->children[index] == nullptr)
            {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->isEnd = true;
    }

    bool search(string word)
    {
        // TODO 8: Start DFS at root and character index 0.
        TrieNode *current = root;
        return dfs(word, current, 0);
    }
};

// ============================================================
// TEST HARNESS
// ============================================================

int main()
{
    cout << "===== DESIGN ADD AND SEARCH WORDS =====\n\n";

    WordDictionary dictionary;
    int passed = 0;
    int total = 0;

    auto test = [&](const string &query, bool expected)
    {
        total++;

        bool actual = dictionary.search(query);
        bool ok = (actual == expected);
        passed += ok;

        cout << "Test " << total << ": "
             << (ok ? "PASS" : "FAIL") << '\n';

        if (!ok)
        {
            cout << "  Query:    \"" << query << "\"\n";
            cout << "  Expected: " << boolalpha << expected << '\n';
            cout << "  Actual:   " << boolalpha << actual << '\n';
        }
    };

    // Standard example
    dictionary.addWord("bad");
    dictionary.addWord("dad");
    dictionary.addWord("mad");

    test("pad", false);
    test("bad", true);
    test(".ad", true);
    test("b..", true);
    test("..d", true);
    test("...", true);
    test("ba", false);
    test("b...", false);

    // Single-character word
    dictionary.addWord("a");
    test("a", true);
    test(".", true);
    test("ab", false);

    // Multiple words sharing prefixes
    dictionary.addWord("bat");
    dictionary.addWord("batch");

    test("bat", true);
    test("ba.", true);
    test("b.t", true);
    test("bat..", true);
    test("ba", false);

    cout << "\n========== SUMMARY ==========\n";
    cout << "Passed: " << passed << "/" << total << '\n';
    cout << "Failed: " << total - passed << "/" << total << '\n';

    return (passed == total) ? 0 : 1;
}
