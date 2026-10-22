#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #739 — Daily Temperatures
Difficulty: Medium
Topic: Stack, Monotonic Stack

PROBLEM:
Given an array of daily temperatures, return an array answer
where answer[i] is the number of days you must wait after day i
to get a warmer temperature.

If there is no future day with a warmer temperature, answer[i] = 0.

EXAMPLE:
Input:  temperatures = {73, 74, 75, 71, 69, 72, 76, 73}
Output:                {1, 1, 4, 2, 1, 1, 0, 0}

YOUR TASK:
Implement vector<int> dailyTemperatures(vector<int>& temperatures).

TEST CASES:
1. {73, 74, 75, 71, 69, 72, 76, 73} -> {1, 1, 4, 2, 1, 1, 0, 0}
2. {30, 40, 50, 60}                  -> {1, 1, 1, 0}
3. {60, 50, 40, 30}                  -> {0, 0, 0, 0}
4. {30}                              -> {0}
5. {30, 30, 30}                      -> {0, 0, 0}
6. {30, 31}                          -> {1, 0}
7. {50, 60, 40, 70}                  -> {1, 2, 1, 0}
8. {70, 71, 69, 72}                  -> {1, 2, 1, 0}
9. {80, 75, 76, 74, 79}              -> {0, 1, 2, 1, 0}
10. {40, 35, 32, 37, 36, 39, 41}     -> {6, 2, 1, 2, 1, 1, 0}

TARGET:
Time: O(n)
Extra space: O(n)
*/

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        // TODO: Solve it yourself.
        int n = temperatures.size();
        stack<int> days;
        vector<int> answers(n, 0);

        for (int i = 0; i < n; i++)
        {
            while (!days.empty() && temperatures[days.top()] < temperatures[i])
            {
                answers[days.top()] = i - days.top(); //this finds answers for multiple days at once if a greater temp is found
                days.pop();
            }

            days.push(i);
        }

        return answers;
    }
};

void runTest(vector<int> temperatures, vector<int> expected, int testNumber)
{
    Solution solution;
    vector<int> actual = solution.dailyTemperatures(temperatures);

    cout << "Test " << testNumber << ": "
         << (actual == expected ? "PASS" : "FAIL") << '\n';

    if (actual != expected)
    {
        cout << "Expected: { ";
        for (int x : expected)
            cout << x << " ";
        cout << "}\nActual:   { ";
        for (int x : actual)
            cout << x << " ";
        cout << "}\n";
    }
}

int main()
{
    runTest({73, 74, 75, 71, 69, 72, 76, 73},
            {1, 1, 4, 2, 1, 1, 0, 0}, 1);

    runTest({30, 40, 50, 60}, {1, 1, 1, 0}, 2);
    runTest({60, 50, 40, 30}, {0, 0, 0, 0}, 3);
    runTest({30}, {0}, 4);
    runTest({30, 30, 30}, {0, 0, 0}, 5);
    runTest({30, 31}, {1, 0}, 6);
    runTest({50, 60, 40, 70}, {1, 2, 1, 0}, 7);
    runTest({70, 71, 69, 72}, {1, 2, 1, 0}, 8);
    runTest({80, 75, 76, 74, 79}, {0, 1, 2, 1, 0}, 9);
    runTest({40, 35, 32, 37, 36, 39, 41},
            {6, 2, 1, 2, 1, 1, 0}, 10);

    return 0;
}
