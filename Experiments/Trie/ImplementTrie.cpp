// LeetCode 208 - Implement Trie (Prefix Tree)
// Difficulty: Medium
// Topic: Trie / Prefix Tree
//
// PROBLEM STATEMENT
// Implement a Trie data structure supporting:
// 1. Trie(): Initialize an empty Trie.
// 2. insert(word): Insert a string into the Trie.
// 3. search(word): Return true if the exact word was inserted.
// 4. startsWith(prefix): Return true if any inserted word
//    starts with the given prefix.
//
// EXAMPLE 1
// Operations:
// ["Trie", "insert", "search", "search", "startsWith",
//  "insert", "search"]
// Arguments:
// [[], ["apple"], ["apple"], ["app"], ["app"],
//  ["app"], ["app"]]
// Expected outputs:
// [null, null, true, false, true, null, true]
//
// EXAMPLE 2
// Insert "carpet":
// search("car")      -> false
// startsWith("car")  -> true
// search("carpet")   -> true
//
// CONSTRAINTS
// - 1 <= word.length, prefix.length <= 2000
// - word and prefix consist only of lowercase English letters.
// - At most 3 * 10^4 calls will be made across all methods.
//
// STANDARD LEETCODE INTERFACE
// class Trie {
// public:
//     Trie();
//     void insert(string word);
//     bool search(string word);
//     bool startsWith(string prefix);
// };
//
// IMPLEMENTATION POLICY
// The three requested methods are intentionally left for you.

#include <iostream>
#include <string>
#include <vector>
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

class Trie
{
private:
    TrieNode *root;

public:
    Trie()
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

    bool search(string word)
    {
        // TODO: Implement exact-word search.
        TrieNode *current = root;
        for (char c : word)
        {
            int index = c - 'a';

            if (current->children[index] == nullptr)
            {
                return false;
            }

            current = current->children[index];
        }

        return current->isEnd;
    }

    bool startsWith(string prefix)
    {
        // TODO: Implement prefix search.
        TrieNode *current = root;
        for (char c : prefix)
        {
            int index = c - 'a';

            if (current->children[index] == nullptr)
            {
                return false;
            }

            current = current->children[index];
        }

        return true;
    }
};

struct Operation
{
    string name;
    string argument;
    string expected;
};

struct TestCase
{
    string name;
    vector<Operation> operations;
};

struct TestResult
{
    string name;
    string expected;
    string actual;
    bool passed;
};

int main()
{
    vector<TestCase> tests = {
        {"LeetCode example",
         {{"insert", "apple", "null"},
          {"search", "apple", "true"},
          {"search", "app", "false"},
          {"startsWith", "app", "true"},
          {"insert", "app", "null"},
          {"search", "app", "true"}}},
        {"Shared prefixes",
         {{"insert", "cat", "null"},
          {"insert", "car", "null"},
          {"search", "cat", "true"},
          {"search", "car", "true"},
          {"search", "ca", "false"},
          {"startsWith", "ca", "true"}}},
        {"Prefix longer than stored word",
         {{"insert", "app", "null"},
          {"search", "apple", "false"},
          {"startsWith", "appl", "false"},
          {"startsWith", "app", "true"}}},
        {"Different branches",
         {{"insert", "dog", "null"},
          {"insert", "dot", "null"},
          {"search", "dog", "true"},
          {"search", "dot", "true"},
          {"search", "dig", "false"},
          {"startsWith", "do", "true"}}},
        {"Single character",
         {{"insert", "a", "null"},
          {"search", "a", "true"},
          {"search", "b", "false"},
          {"startsWith", "a", "true"}}},
        {"Longer word",
         {{"insert", "carpet", "null"},
          {"search", "car", "false"},
          {"startsWith", "car", "true"},
          {"search", "carpet", "true"},
          {"startsWith", "carpets", "false"}}}};

    vector<TestResult> results;

    // Each test case receives a fresh Trie instance.
    for (const TestCase &test : tests)
    {
        Trie trie;
        bool testPassed = true;

        for (const Operation &op : test.operations)
        {
            string actual;

            if (op.name == "insert")
            {
                trie.insert(op.argument);
                actual = "null";
            }
            else if (op.name == "search")
            {
                actual = trie.search(op.argument) ? "true" : "false";
            }
            else if (op.name == "startsWith")
            {
                actual = trie.startsWith(op.argument) ? "true" : "false";
            }
            else
            {
                actual = "INVALID_OPERATION";
            }

            bool passed = (actual == op.expected);
            testPassed = testPassed && passed;

            results.push_back({test.name + " | " + op.name +
                                   "(\"" + op.argument + "\")",
                               op.expected,
                               actual,
                               passed});
        }

        // Each operation has its own expected result.
        // Overall summary below counts operation-level checks.
        (void)testPassed;
    }

    int passed = 0;
    int failed = 0;

    for (const TestResult &result : results)
    {
        if (result.passed)
            ++passed;
        else
            ++failed;
    }

    cout << "========== TEST SUMMARY ==========\n";
    cout << "Passed: " << passed << "/" << results.size() << "\n";
    cout << "Failed: " << failed << "/" << results.size() << "\n";

    cout << "\n========== TEST DETAILS ==========\n";

    for (const TestResult &result : results)
    {
        cout << (result.passed ? "[PASS] " : "[FAIL] ")
             << result.name
             << " | Expected: " << result.expected
             << " | Actual: " << result.actual << '\n';
    }

    return failed == 0 ? 0 : 1;
}
