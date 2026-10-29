/*
LeetCode 677 - Map Sum Pairs
Difficulty: Medium
Topic: Trie
Pattern: Trie + Prefix Sum + Hash Map

PROBLEM
Design a MapSum class that supports:
1. insert(key, val): Insert a key with an integer value.
   If the key already exists, replace its old value.
2. sum(prefix): Return the sum of values of all keys
   that start with the given prefix.

EXAMPLE
Operations:
insert("apple", 3)
sum("ap")       -> 3
insert("app", 2)
sum("ap")       -> 5
insert("apple", 4)
sum("ap")       -> 6

CONSTRAINTS
- 1 <= key.length, prefix.length <= 50
- key and prefix consist of lowercase English letters.
- 1 <= val <= 1000
- At most 50 calls in total to insert and sum.

LEETCODE SIGNATURE
class MapSum {
public:
    MapSum();
    void insert(string key, int val);
    int sum(string prefix);
};

IMPLEMENTATION PLAN
1. TrieNode stores children[26] and a prefix sum.
2. MapSum stores a Trie root and unordered_map<string, int>
   containing each key's latest value.
3. In insert(), calculate change = new value - old value.
4. Update the stored value in the hash map.
5. Traverse/create the Trie path and add change to each
   visited node's sum.
6. In sum(), traverse the prefix and return its node's sum.
   Return 0 if a required child does not exist.

TODO: Implement the logic yourself.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct TrieNode
{
    TrieNode *children[26];
    int sum;

    TrieNode() : sum(0)
    {
        for (int i = 0; i < 26; ++i)
        {
            children[i] = nullptr;
        }
    }
};

class MapSum
{
private:
    TrieNode *root;
    unordered_map<string, int> values;

public:
    MapSum()
    {
        root = new TrieNode();
    }

    void insert(string key, int val)
    {
        // TODO: Calculate the difference from the old value.
        // TODO: Update values[key].
        // TODO: Traverse/create the key's Trie path.
        // TODO: Apply the difference to each visited node's sum.
        TrieNode *current = root;
        int change = -values[key] + val;
        values[key] = val;

        for (char c : key)
        {
            int index = c - 'a';

            if (current->children[index] == nullptr)
            {
                TrieNode *newNode = new TrieNode();
                current->children[index] = newNode;
            }

            current = current->children[index];
            current->sum += change;
        }
    }

    int sum(string prefix)
    {
        // TODO: Traverse the Trie using the prefix.
        // TODO: Return 0 if a required child is missing.
        // TODO: Return the sum at the final prefix node.
        TrieNode *current = root;

        for (char c : prefix)
        {
            int index = c - 'a';

            if (current->children[index] == nullptr)
            {
                return 0;
            }

            current = current->children[index];
        }
        return current->sum;
    }
};

struct Operation
{
    string type;
    string key;
    int value;
    int expected;
};

int main()
{
    MapSum mapSum;
    int passed = 0;
    int failed = 0;

    auto check = [&](const string &name, int actual, int expected)
    {
        if (actual == expected)
        {
            ++passed;
            cout << "[PASS] " << name << '\n';
        }
        else
        {
            ++failed;
            cout << "[FAIL] " << name << '\n';
        }
    };

    // Official example
    mapSum.insert("apple", 3);
    check("sum(ap) after apple=3", mapSum.sum("ap"), 3);

    mapSum.insert("app", 2);
    check("sum(ap) after app=2", mapSum.sum("ap"), 5);

    // Updating an existing key must apply only the difference.
    mapSum.insert("apple", 4);
    check("sum(ap) after updating apple to 4", mapSum.sum("ap"), 6);

    // Exact prefix and longer prefix checks.
    check("sum(app)", mapSum.sum("app"), 6);
    check("sum(apple)", mapSum.sum("apple"), 4);

    // Missing prefix.
    check("sum(b) for missing prefix", mapSum.sum("b"), 0);

    // Different branch.
    mapSum.insert("bat", 7);
    check("sum(ba)", mapSum.sum("ba"), 7);
    check("sum(ap) remains unchanged", mapSum.sum("ap"), 6);

    cout << "\n========== TEST SUMMARY ==========\n";
    cout << "Passed: " << passed << "/8\n";
    cout << "Failed: " << failed << "/8\n";

    return failed == 0 ? 0 : 1;
}
