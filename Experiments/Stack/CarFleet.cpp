/*
============================================================
LeetCode 853 - Car Fleet
Topic: Stack / Sorting / Greedy
Difficulty: Medium
============================================================

PROBLEM STATEMENT:

There are n cars going to the same destination along a
one-lane road.

The destination is target miles away.

You are given two integer arrays:
- position[i]: The starting position of the ith car.
- speed[i]: The speed of the ith car in miles per hour.

A car cannot pass another car ahead of it, but it can catch
up to a car ahead and drive at the same speed as that car.

A car fleet is a non-empty set of cars driving at the same
position and same speed. A single car is also considered a
car fleet.

If a car catches up to a fleet exactly at the destination,
it is still considered part of that fleet.

Return the number of car fleets that will arrive at the
destination.

------------------------------------------------------------
EXAMPLE 1:

Input:
target = 12
position = [10, 8, 0, 5, 3]
speed = [2, 4, 1, 1, 3]

Output:
3

Explanation:

The cars starting at positions 10 and 8 become one fleet.
The cars starting at positions 5 and 3 become another fleet.
The car starting at position 0 forms its own fleet.

------------------------------------------------------------
EXAMPLE 2:

Input:
target = 10
position = [3]
speed = [3]

Output:
1

------------------------------------------------------------
EXAMPLE 3:

Input:
target = 100
position = [0, 2, 4]
speed = [4, 2, 1]

Output:
1

------------------------------------------------------------
CONSTRAINTS:

- n == position.length == speed.length
- 1 <= n <= 1000
- 0 < target <= 100000
- 0 <= position[i] < target
- All values in position are unique.
- 0 < speed[i] <= 100000
- All cars start at different positions.

------------------------------------------------------------
APPROACH NOTES:

Think about:
- Pairing each car's position and speed.
- Sorting cars by starting position in descending order.
- Calculating each car's arrival time.
- Using floating-point division.
- Comparing arrival times with the fleet ahead.
- A faster car behind joins the fleet ahead.
- A slower car behind forms a new fleet.

Potential complexity:
- Time: O(n log n), dominated by sorting.
- Auxiliary space: O(n).

============================================================
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;

class Solution
{
public:
    int carFleet(int target, vector<int> &position, vector<int> &speed)
    {
        vector<pair<int, int>> combined;
        int n = position.size();
        stack<double> monostack;

        for (int i = 0; i < n; i++)
        {
            combined.push_back({position[i], speed[i]});
        }

        sort(combined.begin(), combined.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             { return a.first > b.first; });

        for (int i = 0; i < n; i++)
        {
            double arrivalTime = (double)(target - combined[i].first) / combined[i].second;
            if (!monostack.empty() && arrivalTime <= monostack.top())
            {
            }
            else
            {
                monostack.push(arrivalTime);
            }
        }

        return monostack.size();
    }
};

// ============================================================
// TEST HARNESS
// ============================================================

struct TestCase
{
    string name;
    int target;
    vector<int> position;
    vector<int> speed;
    int expected;
};

int main()
{
    vector<TestCase> tests = {
        {"LeetCode Example 1",
         12,
         {10, 8, 0, 5, 3},
         {2, 4, 1, 1, 3},
         3},
        {"Single Car",
         10,
         {3},
         {3},
         1},
        {"All Cars Form One Fleet",
         100,
         {0, 2, 4},
         {4, 2, 1},
         1},
        {"Every Car Forms A Separate Fleet",
         10,
         {0, 4, 8},
         {1, 1, 1},
         3},
        {"Two Cars Same Arrival Time",
         10,
         {6, 8},
         {3, 2},
         2},
        {"Equal Arrival Times",
         12,
         {10, 8},
         {2, 4},
         1},
        {"Faster Car Joins Slower Fleet",
         12,
         {10, 8},
         {2, 8},
         1},
        {"Multiple Fleets",
         20,
         {0, 5, 10, 15},
         {2, 1, 2, 1},
         2},
        {"Cars With Fractional Arrival Times",
         10,
         {8, 6, 3},
         {3, 4, 2},
         3}};

    int passed = 0;
    int failed = 0;

    vector<int> actualResults;

    for (const auto &test : tests)
    {
        Solution solution;

        vector<int> positions = test.position;
        vector<int> speeds = test.speed;

        int actual = solution.carFleet(
            test.target,
            positions,
            speeds);

        actualResults.push_back(actual);

        if (actual == test.expected)
            passed++;
        else
            failed++;
    }

    cout << "========================================\n";
    cout << "CAR FLEET - TEST SUMMARY\n";
    cout << "========================================\n";
    cout << "Total Tests : " << tests.size() << "\n";
    cout << "Passed      : " << passed << "\n";
    cout << "Failed      : " << failed << "\n";
    cout << "========================================\n\n";

    for (size_t i = 0; i < tests.size(); i++)
    {
        bool success = actualResults[i] == tests[i].expected;

        cout << (success ? "[PASS] " : "[FAIL] ")
             << tests[i].name << "\n";

        if (!success)
        {
            cout << "  Target   : " << tests[i].target << "\n";

            cout << "  Positions: ";
            for (int value : tests[i].position)
                cout << value << " ";

            cout << "\n  Speeds   : ";
            for (int value : tests[i].speed)
                cout << value << " ";

            cout << "\n  Expected : " << tests[i].expected;
            cout << "\n  Actual   : " << actualResults[i] << "\n";
        }
    }

    cout << "\n========================================\n";

    return failed == 0 ? 0 : 1;
}
