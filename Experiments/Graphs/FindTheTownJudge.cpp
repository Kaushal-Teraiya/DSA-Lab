/*
========================================================
LeetCode #997 - Find the Town Judge
Difficulty: Easy
Topic: Graphs, In-Degree, Out-Degree
========================================================

PROBLEM STATEMENT
-----------------
In a town, there are n people labeled from 1 to n.
One of these people might be the town judge.

If the town judge exists, then:

1. The town judge trusts nobody.
2. Everybody (except the judge) trusts the judge.
3. There is exactly one person who satisfies both rules.

You are given an array trust where trust[i] = [a, b]
means that person a trusts person b.

Return the label of the town judge if the judge exists.
Otherwise, return -1.

EXAMPLE 1
---------
Input:
n = 2
trust = {{1, 2}}

Output: 2

Explanation:
Person 1 trusts person 2, and person 2 trusts nobody.

EXAMPLE 2
---------
Input:
n = 3
trust = {{1, 3}, {2, 3}}

Output: 3

Explanation:
Both persons 1 and 2 trust person 3.
Person 3 trusts nobody.

EXAMPLE 3
---------
Input:
n = 3
trust = {{1, 3}, {2, 3}, {3, 1}}

Output: -1

Explanation:
Person 3 trusts person 1, so person 3 cannot be the judge.
Person 1 also cannot be the judge because person 3 does
not trust person 1? Check the relationships carefully.

CONSTRAINTS
-----------
- 1 <= n <= 1000
- 0 <= trust.length <= 10^4
- trust[i].length == 2
- All pairs trust[i] are unique.
- a != b
- 1 <= a, b <= n

APPROACH HINT
-------------
Think about how many people trust a person and how many
people that person trusts.

- In-degree: number of people who trust this person.
- Out-degree: number of people this person trusts.

The judge must be trusted by n - 1 people and trust 0
people.

Your task: implement findJudge().

========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findJudge(int n, vector<vector<int>> &trust)
    {
        vector<int> inDegree(n + 1, 0);
        vector<int> outDegree(n + 1, 0);

        for (auto &relationship : trust)
        {
            int a = relationship[0];
            int b = relationship[1];

            //indegree how many prople trust them.
            //outdegree how many people they trust. 
            inDegree[b]++;
            outDegree[a]++;
        }

        for (int i = 1; i <= n; i++)
        {
            //consition for the town judge is the following
            // they should trust nobody but everybody should trust them
            if (inDegree[i] == n - 1 && outDegree[i] == 0)
            {
                return i;
            }
        }

        return -1;
    }
};

// -------------------- TEST HARNESS --------------------

struct TestCase
{
    string name;
    int n;
    vector<vector<int>> trust;
    int expected;
};

int main()
{
    vector<TestCase> tests = {
        {"Two people",
         2,
         {{1, 2}},
         2},
        {"Three people, judge is person 3",
         3,
         {{1, 3}, {2, 3}},
         3},
        {"No judge",
         3,
         {{1, 3}, {2, 3}, {3, 1}},
         -1},
        {"Everyone trusts someone",
         3,
         {{1, 2}, {2, 3}, {3, 1}},
         -1},
        {"Single person town",
         1,
         {},
         1},
        {"Judge is person 1",
         3,
         {{2, 1}, {3, 1}},
         1},
        {"Nobody trusts anyone in a multi-person town",
         3,
         {},
         -1}};

    Solution solution;
    int passed = 0;

    for (const auto &test : tests)
    {
        vector<vector<int>> input = test.trust;
        int actual = solution.findJudge(test.n, input);

        if (actual == test.expected)
        {
            passed++;
        }
    }

    cout << "========== TEST SUMMARY ==========\n";
    cout << "Passed: " << passed << "/" << tests.size() << "\n";
    cout << "Failed: " << tests.size() - passed << "/" << tests.size() << "\n";
    cout << "==================================\n\n";

    for (const auto &test : tests)
    {
        vector<vector<int>> input = test.trust;
        int actual = solution.findJudge(test.n, input);

        cout << test.name << "\n";
        cout << "Expected: " << test.expected
             << " | Actual: " << actual
             << " | " << (actual == test.expected ? "PASS" : "FAIL")
             << "\n\n";
    }

    return passed == static_cast<int>(tests.size()) ? 0 : 1;
}
