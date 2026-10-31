/*
    LeetCode 682 - Baseball Game
    Difficulty: Easy
    Topic: Stack

    ------------------------------------------------------------
    PROBLEM STATEMENT
    ------------------------------------------------------------

    You are keeping score for a baseball game with unusual rules.
    At the beginning of the game, you have no records.

    You are given a list of strings operations, where operations[i]
    is the ith operation you must apply to the record.

    Each operation can be one of the following:

    1. An integer x:
       Record a new score of x.

    2. "+":
       Record a new score that is the sum of the previous two scores.

    3. "D":
       Record a new score that is double the previous score.

    4. "C":
       Invalidate the previous score, removing it from the record.

    Return the sum of all the scores in the record after applying
    all the operations.

    It is guaranteed that the operations are valid and that all
    intermediate results fit in a 32-bit integer.

    ------------------------------------------------------------
    EXAMPLES
    ------------------------------------------------------------

    Example 1:

    Input:
    operations = {"5", "2", "C", "D", "+"}

    Output:
    30

    Explanation:
    "5" - Add 5. Record is [5].
    "2" - Add 2. Record is [5, 2].
    "C" - Remove the previous score. Record is [5].
    "D" - Add double the previous score. Record is [5, 10].
    "+" - Add the sum of the previous two scores.
           Record is [5, 10, 15].

    Total = 5 + 10 + 15 = 30.


    Example 2:

    Input:
    operations = {"5", "-2", "4", "C", "D", "9", "+", "+"}

    Output:
    27

    Explanation:
    The final record is [5, -2, -4, 9, 5, 14].

    Total = 27.


    Example 3:

    Input:
    operations = {"1", "C"}

    Output:
    0

    Explanation:
    "1" - Add 1. Record is [1].
    "C" - Remove the previous score. Record is [].

    Total = 0.

    ------------------------------------------------------------
    CONSTRAINTS
    ------------------------------------------------------------

    1 <= operations.length <= 1000

    operations[i] is "C", "D", "+", or an integer in the range
    [-30000, 30000].

    For operation "C", there will always be a previous valid score.

    For operation "D", there will always be a previous valid score.

    For operation "+", there will always be two previous valid scores.

    All intermediate and final results fit in a 32-bit integer.

    ------------------------------------------------------------
    APPROACH NOTES
    ------------------------------------------------------------

    Data structure:
    - Stack

    Consider:
    - How to record a new score.
    - How to cancel the previous score.
    - How to access the previous score.
    - How to access the previous two scores.
    - How to calculate the final sum without destroying the
      original stack.

    ------------------------------------------------------------
    IMPLEMENTATION
    ------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <utility>

using namespace std;

class Solution
{
public:
    int calPoints(vector<string> &operations)
    {
        stack<int> scores;
        int n = operations.size();

        for (int i = 0; i < n; i++)
        {
            if (scores.size() >= 2 && operations[i] == "+")
            {
                pair<int, int> temp;
                temp.first = scores.top();
                scores.pop();
                temp.second = scores.top();
                scores.pop();

                int final = temp.first + temp.second;
                scores.push(temp.second);
                scores.push(temp.first);
                scores.push(final);
            }
            else if (scores.size() >= 1 && operations[i] == "D")
            {
                scores.push(2 * scores.top());
            }
            else if (scores.size() >= 1 && operations[i] == "C")
            {
                scores.pop();
            }
            else
            {
                scores.push(stoi(operations[i]));
            }
        }

        stack<int> temp = scores;
        int total = 0;

        while (!temp.empty())
        {
            total += temp.top();
            temp.pop();
        }

        return total;
    }
};

// ------------------------------------------------------------
// TEST HARNESS
// ------------------------------------------------------------

struct TestCase
{
    string name;
    vector<string> operations;
    int expected;
};

struct TestResult
{
    string name;
    int expected;
    int actual;
    bool passed;
};

int main()
{
    vector<TestCase> testCases =
        {
            {"Example 1 - Basic operations",
             {"5", "2", "C", "D", "+"},
             30},
            {"Example 2 - Mixed operations",
             {"5", "-2", "4", "C", "D", "9", "+", "+"},
             27},
            {"Example 3 - Cancel all scores",
             {"1", "C"},
             0},
            {"Single positive score",
             {"10"},
             10},
            {"Single negative score",
             {"-10"},
             -10},
            {"Only doubling",
             {"5", "D"},
             15},
            {"Only addition",
             {"1", "2", "+"},
             6},
            {"Multiple cancellations",
             {"5", "10", "15", "C", "C"},
             5},
            {"Negative scores with doubling",
             {"-3", "D"},
             -9},
            {"Combination of all operations",
             {"10", "20", "+", "D", "C", "5"},
             65}};

    Solution solution;
    vector<TestResult> results;

    int passed = 0;
    int failed = 0;

    for (const TestCase &test : testCases)
    {
        vector<string> operations = test.operations;

        int actual = solution.calPoints(operations);
        bool success = actual == test.expected;

        results.push_back({test.name,
                           test.expected,
                           actual,
                           success});

        if (success)
            passed++;
        else
            failed++;
    }

    // Summary is deliberately printed before detailed results.

    cout << "\n========================================\n";
    cout << "       BASEBALL GAME - TEST SUMMARY\n";
    cout << "========================================\n";

    cout << "Total Tests : " << testCases.size() << '\n';
    cout << "Passed      : " << passed << '\n';
    cout << "Failed      : " << failed << '\n';

    cout << "Status      : "
         << (failed == 0 ? "ALL TESTS PASSED" : "SOME TESTS FAILED")
         << '\n';

    cout << "========================================\n";

    // Detailed test results.

    cout << "\nDETAILED TEST RESULTS\n";
    cout << "----------------------------------------\n";

    for (const TestResult &result : results)
    {
        cout << (result.passed ? "[PASS] " : "[FAIL] ")
             << result.name << '\n';

        cout << "        Expected: " << result.expected
             << " | Actual: " << result.actual << '\n';
    }

    cout << "----------------------------------------\n";

    return failed == 0 ? 0 : 1;
}
