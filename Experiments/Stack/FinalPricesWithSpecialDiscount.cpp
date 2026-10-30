#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <map>

using namespace std;

/*
==========================================================
LeetCode 1475 - Final Prices With a Special Discount
Topic: Stack
Pattern: Monotonic Stack
Difficulty: Easy
==========================================================

PROBLEM STATEMENT:

You are given an integer array prices where prices[i]
is the price of the ith item in a shop.

There is a special discount for items in the shop.

If you buy the ith item, you will receive a discount
equivalent to the price of the first item j that comes
after the ith item (j > i) and has a price less than
or equal to prices[i].

Otherwise, you will not receive any discount at all.

Return an integer array answer where answer[i] is the
final price you will pay for the ith item of the shop,
considering the special discount.

EXAMPLE 1:

Input:
prices = [8,4,6,2,3]

Output:
[4,2,4,2,3]

Explanation:

For item 0:
Price = 8, discount = 4, final price = 4.

For item 1:
Price = 4, discount = 2, final price = 2.

For item 2:
Price = 6, discount = 2, final price = 4.

For item 3:
Price = 2, no qualifying discount, final price = 2.

For item 4:
Price = 3, no qualifying discount, final price = 3.


EXAMPLE 2:

Input:
prices = [1,2,3,4,5]

Output:
[1,2,3,4,5]

Explanation:
No item has a qualifying item to its right.


EXAMPLE 3:

Input:
prices = [10,1,1,6]

Output:
[9,0,1,6]


CONSTRAINTS:

1 <= prices.length <= 500

1 <= prices[i] <= 1000


EXPECTED COMPLEXITY:

Time Complexity: O(n)
Space Complexity: O(n)

==========================================================
SOLUTION
==========================================================
*/

class Solution
{
public:
    vector<int> finalPrices(vector<int> &prices)
    {
        // in place version
        int n = prices.size();
        stack<int> monostack;

        for (int i = 0; i < n; i++)
        {
            // take snap shot of current item
            int preservedPrice = prices[i];

            while (!monostack.empty() && prices[monostack.top()] >= preservedPrice)
            {
                // stack.top gives the index of previous element in the prices
                // while prices[i] represents current price
                prices[monostack.top()] -= preservedPrice;
                monostack.pop();
            }

            // we push index because pushing only elements would not consider the same / duplicate elements case
            monostack.push(i);
        }

        return prices;
    }
};

/*
==========================================================
LOCAL TEST HARNESS
==========================================================
*/

struct TestCase
{
    string name;
    vector<int> prices;
    vector<int> expected;
};

void printVector(const vector<int> &values)
{
    cout << "[";

    for (size_t i = 0; i < values.size(); i++)
    {
        cout << values[i];

        if (i + 1 < values.size())
        {
            cout << ", ";
        }
    }

    cout << "]";
}

bool vectorsEqual(
    const vector<int> &actual,
    const vector<int> &expected)
{
    return actual == expected;
}

struct TestResult
{
    string name;
    vector<int> actual;
    vector<int> expected;
    bool passed;
};

int main()
{

    vector<TestCase> tests = {

        {"Example 1",
         {8, 4, 6, 2, 3},
         {4, 2, 4, 2, 3}},

        {"Example 2 - Increasing prices",
         {1, 2, 3, 4, 5},
         {1, 2, 3, 4, 5}},

        {"Example 3",
         {10, 1, 1, 6},
         {9, 0, 1, 6}},

        {"Decreasing prices",
         {5, 4, 3, 2, 1},
         {1, 1, 1, 1, 1}},

        {"Equal prices",
         {5, 5, 5, 5},
         {0, 0, 0, 5}},

        {"Single item",
         {7},
         {7}},

        {"Mixed prices",
         {7, 5, 6, 3, 4},
         {2, 2, 3, 3, 4}},

        {"Repeated prices with smaller element",
         {5, 5, 7, 2},
         {0, 3, 5, 2}}};

    Solution solution;

    int passed = 0;
    int failed = 0;

    vector<TestResult> results;

    for (const auto &test : tests)
    {

        vector<int> input = test.prices;

        vector<int> actual = solution.finalPrices(input);

        bool success = vectorsEqual(actual, test.expected);

        if (success)
        {
            passed++;
        }
        else
        {
            failed++;
        }

        results.push_back({test.name,
                           actual,
                           test.expected,
                           success});
    }

    // SUMMARY FIRST

    cout << "\n========================================\n";
    cout << "          DSA LAB TEST SUMMARY          \n";
    cout << "========================================\n";

    cout << "Total Tests : " << tests.size() << "\n";
    cout << "Passed      : " << passed << "\n";
    cout << "Failed      : " << failed << "\n";

    cout << "Status      : "
         << (failed == 0 ? "ALL PASSED" : "SOME FAILED")
         << "\n";

    cout << "========================================\n";

    // DETAILED RESULTS

    cout << "\nDETAILED TEST RESULTS\n\n";

    for (const auto &result : results)
    {

        cout << (result.passed ? "[PASS] " : "[FAIL] ")
             << result.name << "\n";

        cout << "Expected: ";
        printVector(result.expected);

        cout << "\nActual:   ";
        printVector(result.actual);

        cout << "\n\n";
    }

    return (failed == 0) ? 0 : 1;
}
