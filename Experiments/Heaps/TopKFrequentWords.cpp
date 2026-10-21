#include <bits/stdc++.h>
using namespace std;

// LeetCode #692 — Top K Frequent Words
// Approach: Frequency Map + Min-Heap

class Solution
{
public:
    vector<string> topKFrequent(vector<string> &words, int k)
    {
        auto comparator = [](const pair<int, string> &a, const pair<int, string> &b)
        {
            if (a.first != b.first)
                return a.first > b.first;
            return a.second < b.second;
        };

        priority_queue<pair<int, string>, vector<pair<int, string>>, decltype(comparator)> minHeap(comparator);
        unordered_map<string, int> map;
        vector<string> result;

        for (string word : words)
        {
            map[word]++;
        }

        for (auto it : map)
        {
            minHeap.push({it.second, it.first});
            if (minHeap.size() > k)
            {
                minHeap.pop();
            }
        }

        while (!minHeap.empty())
        {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }

        reverse(result.begin(), result.end());
        return result;
    }
};

void runTest(vector<string> words, int k,
             const vector<string> &expected, int testNumber)
{
    Solution solution;
    vector<string> actual = solution.topKFrequent(words, k);

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Expected: ";
        for (const auto &word : expected)
            cout << word << ' ';
        cout << "\nActual:   ";
        for (const auto &word : actual)
            cout << word << ' ';
        cout << '\n';
    }
}

int main()
{
    runTest({"i", "love", "leetcode", "i", "love", "coding"},
            2, {"i", "love"}, 1);

    runTest({"the", "day", "is", "sunny", "the", "the",
             "the", "sunny", "is", "is"},
            4, {"the", "is", "sunny", "day"}, 2);

    runTest({"a", "b", "c"}, 2, {"a", "b"}, 3);

    runTest({"aaa", "aa", "a", "aaa", "aa", "aaa"},
            2, {"aaa", "aa"}, 4);

    runTest({"i", "love", "coding", "i", "love", "coding"},
            2, {"coding", "i"}, 5);

    return 0;
}
