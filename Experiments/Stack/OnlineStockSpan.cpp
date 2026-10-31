/*
============================================================
LeetCode 901 - Online Stock Span
Topic: Stack / Monotonic Stack
Difficulty: Medium
============================================================

PROBLEM STATEMENT:

Design an algorithm that collects daily stock prices and
returns the span of that stock's price for the current day.

The span of a stock's price today is defined as the maximum
number of consecutive days (starting from today and going
backwards) for which the stock price was less than or equal
to today's price.

For example, if the prices of the stock in the last four days
are [7, 2, 1, 2] and today's price is 2, then today's span is 4.

Implement the StockSpanner class:

- StockSpanner() Initializes the object.
- int next(int price) Returns the span of the stock's price
  for the current day.

------------------------------------------------------------
EXAMPLE 1:

Input:
["StockSpanner", "next", "next", "next", "next",
 "next", "next", "next"]
[[], [100], [80], [60], [70], [60], [75], [85]]

Output:
[null, 1, 1, 1, 2, 1, 4, 6]

Explanation:

StockSpanner stockSpanner = new StockSpanner();
stockSpanner.next(100); // returns 1
stockSpanner.next(80);  // returns 1
stockSpanner.next(60);  // returns 1
stockSpanner.next(70);  // returns 2
stockSpanner.next(60);  // returns 1
stockSpanner.next(75);  // returns 4
stockSpanner.next(85);  // returns 6

------------------------------------------------------------
CONSTRAINTS:

- 1 <= price <= 100000
- At most 100000 calls will be made to next().
- All calls to next() are made with strictly increasing
  chronological order.

------------------------------------------------------------
APPROACH NOTES:

Think about:
- Monotonic stack
- Storing price and previously calculated span
- Accumulating spans when previous prices are <= current price
- Each price is pushed once and popped at most once

Expected complexity:
- O(1) amortized time per next() call
- O(n) auxiliary space in the worst case

============================================================
*/

#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <string>

using namespace std;

class StockSpanner
{
    stack<pair<int, int>> monostack;

public:
    StockSpanner()
    {
    }

    int next(int price)
    {
        int span = 1;

        while (!monostack.empty() && monostack.top().first <= price)
        {
            span += monostack.top().second;
            monostack.pop();
        }

        monostack.push({price, span});
        return span;
    }
};

// ============================================================
// TEST HARNESS
// ============================================================

struct TestCase
{
    string name;
    vector<int> prices;
    vector<int> expected;
};

int main()
{
    vector<TestCase> tests = {
        {"LeetCode Example 1",
         {100, 80, 60, 70, 60, 75, 85},
         {1, 1, 1, 2, 1, 4, 6}},
        {"Strictly Increasing Prices",
         {10, 20, 30, 40, 50},
         {1, 2, 3, 4, 5}},
        {"Strictly Decreasing Prices",
         {50, 40, 30, 20, 10},
         {1, 1, 1, 1, 1}},
        {"All Equal Prices",
         {5, 5, 5, 5},
         {1, 2, 3, 4}},
        {"Single Price",
         {7},
         {1}},
        {"Mixed Prices",
         {31, 41, 48, 59, 79},
         {1, 2, 3, 4, 5}},
        {"Repeated Peaks",
         {100, 80, 90, 70, 85, 95},
         {1, 1, 2, 1, 2, 5}},
        {"Alternating Prices",
         {10, 5, 10, 5, 10},
         {1, 1, 3, 1, 5}}};

    int passed = 0;
    int failed = 0;

    vector<vector<int>> actualResults;

    // Run every test using a fresh StockSpanner instance.
    for (const auto &test : tests)
    {
        StockSpanner spanner;
        vector<int> actual;

        for (int price : test.prices)
        {
            actual.push_back(spanner.next(price));
        }

        actualResults.push_back(actual);

        if (actual == test.expected)
            passed++;
        else
            failed++;
    }

    cout << "========================================\n";
    cout << "ONLINE STOCK SPAN - TEST SUMMARY\n";
    cout << "========================================\n";
    cout << "Total Tests : " << tests.size() << "\n";
    cout << "Passed      : " << passed << "\n";
    cout << "Failed      : " << failed << "\n";
    cout << "========================================\n\n";

    for (size_t i = 0; i < tests.size(); i++)
    {
        cout << (actualResults[i] == tests[i].expected
                     ? "[PASS] "
                     : "[FAIL] ")
             << tests[i].name << "\n";

        if (actualResults[i] != tests[i].expected)
        {
            cout << "  Prices  : ";
            for (int value : tests[i].prices)
                cout << value << " ";

            cout << "\n  Expected: ";
            for (int value : tests[i].expected)
                cout << value << " ";

            cout << "\n  Actual  : ";
            for (int value : actualResults[i])
                cout << value << " ";

            cout << "\n";
        }
    }

    cout << "\n========================================\n";

    return failed == 0 ? 0 : 1;
}
