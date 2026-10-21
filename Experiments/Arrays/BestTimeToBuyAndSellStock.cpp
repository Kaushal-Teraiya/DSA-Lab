#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #121 - Best Time to Buy and Sell Stock

PROBLEM STATEMENT:
You are given an array prices where prices[i] is the price
of a stock on the ith day.

Choose one day to buy and a different future day to sell.
Return the maximum profit possible from this transaction.
If no profit is possible, return 0.

RULES:
- Buy before you sell.
- At most one transaction is allowed.
- You cannot sell before buying.

EXAMPLES:
1. prices = {7, 1, 5, 3, 6, 4}
   Output: 5

2. prices = {7, 6, 4, 3, 1}
   Output: 0

3. prices = {2, 4, 1}
   Output: 2

TEST CASES:
1. {7, 1, 5, 3, 6, 4} -> 5
2. {7, 6, 4, 3, 1}    -> 0
3. {2, 4, 1}          -> 2
4. {1, 2}             -> 1
5. {5}                -> 0
6. {3, 3, 3, 3}        -> 0
7. {2, 1, 4}          -> 3
8. {3, 2, 6, 5, 0, 3} -> 4
9. {1, 5, 2, 8}       -> 7
10. {8, 2, 4, 1, 7}   -> 6

YOUR TASK:
Implement maxProfit(vector<int>& prices).
Try to solve it yourself before looking at hints.
*/

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        // TODO: Implement your solution.
        int n = prices.size();
        int maxProfit = 0;
        int minPrice = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            maxProfit = max(maxProfit, prices[i] - minPrice);
            minPrice = min(minPrice, prices[i]);
        }

        return maxProfit;
    }
};

int main()
{
    Solution solution;

    vector<pair<vector<int>, int>> tests = {
        {{7, 1, 5, 3, 6, 4}, 5},
        {{7, 6, 4, 3, 1}, 0},
        {{2, 4, 1}, 2},
        {{1, 2}, 1},
        {{5}, 0},
        {{3, 3, 3, 3}, 0},
        {{2, 1, 4}, 3},
        {{3, 2, 6, 5, 0, 3}, 4},
        {{1, 5, 2, 8}, 7},
        {{8, 2, 4, 1, 7}, 6}};

    for (int i = 0; i < (int)tests.size(); i++)
    {
        int actual = solution.maxProfit(tests[i].first);

        cout << "Test " << i + 1 << ": "
             << (actual == tests[i].second ? "PASS" : "FAIL")
             << " | Expected: " << tests[i].second
             << " | Got: " << actual << '\n';
    }

    return 0;
}
