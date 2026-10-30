#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

/*
==========================================================
LeetCode 496 - Next Greater Element I
Topic: Stack
Pattern: Monotonic Stack
Difficulty: Easy
==========================================================

PROBLEM STATEMENT:

The next greater element of some element x in an array
is the first greater element that is to the right of x
in the same array.

You are given two distinct 0-indexed integer arrays
nums1 and nums2, where nums1 is a subset of nums2.

For each element in nums1, find its next greater element
in nums2.

If no such element exists, return -1 for that number.

Return an array ans of length nums1.length such that:

ans[i] = next greater element of nums1[i] in nums2.


EXAMPLE 1:

Input:
nums1 = [4,1,2]
nums2 = [1,3,4,2]

Output:
[-1,3,-1]

Explanation:
4 -> -1
1 -> 3
2 -> -1


EXAMPLE 2:

Input:
nums1 = [2,4]
nums2 = [1,2,3,4]

Output:
[3,-1]

Explanation:
2 -> 3
4 -> -1


CONSTRAINTS:

1 <= nums1.length <= nums2.length <= 1000

0 <= nums1[i], nums2[i] <= 10000

All integers in nums1 and nums2 are unique.

All elements of nums1 are also present in nums2.


EXPECTED COMPLEXITY:

Time Complexity: O(n + m)
Space Complexity: O(m)

Where:
n = nums1.length
m = nums2.length


==========================================================
SOLUTION IMPLEMENTATION
==========================================================
*/

class Solution
{
public:
    vector<int> nextGreaterElement(
        vector<int> &nums1,
        vector<int> &nums2)
    {
        //map to store the nexxt greater element of all the nums in nums2
        //stack to keep track of all the nums that needs to be processed
        //ans vector for greater element of nums1 
        unordered_map<int, int> map;
        stack<int> monostack;
        vector<int> ans;
        int n = nums2.size();

        //loop through all in nums2
        for (int i = 0; i < n; i++)
        {
            //stack must not be empty and top should be less than curr num
            while (!monostack.empty() && monostack.top() < nums2[i])
            {
                //store the next greater element relation
                map[monostack.top()] = nums2[i];
                monostack.pop();
            }

            monostack.push(nums2[i]);
        }

        //assign -1 for the nums whose NGE is not found
        while (!monostack.empty())
        {
            map[monostack.top()] = -1;
            monostack.pop();
        }

        //build the ans array
        for (int num : nums1)
        {
            ans.push_back(map[num]);
        }

        return ans;
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
    vector<int> nums1;
    vector<int> nums2;
    vector<int> expected;
};

bool vectorsEqual(
    const vector<int> &actual,
    const vector<int> &expected)
{
    return actual == expected;
}

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

int main()
{

    vector<TestCase> tests = {

        {"Example 1",
         {4, 1, 2},
         {1, 3, 4, 2},
         {-1, 3, -1}},

        {"Example 2",
         {2, 4},
         {1, 2, 3, 4},
         {3, -1}},

        {"Increasing sequence",
         {1, 2, 3},
         {1, 2, 3, 4},
         {2, 3, 4}},

        {"Decreasing sequence",
         {4, 3, 2, 1},
         {4, 3, 2, 1},
         {-1, -1, -1, -1}},

        {"Mixed sequence",
         {5, 3, 2},
         {5, 3, 2, 7, 6},
         {7, 7, 7}},

        {"Single element",
         {5},
         {5},
         {-1}},

        {"Subset in different order",
         {3, 1, 4},
         {1, 2, 3, 4, 5},
         {4, 2, 5}}};

    Solution solution;

    int passed = 0;
    int failed = 0;

    struct TestResult
    {
        string name;
        vector<int> actual;
        vector<int> expected;
        bool success;
    };

    vector<TestResult> results;

    for (const auto &test : tests)
    {

        vector<int> nums1 = test.nums1;
        vector<int> nums2 = test.nums2;

        vector<int> actual =
            solution.nextGreaterElement(nums1, nums2);

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

    // DETAILED RESULTS SECOND

    cout << "\nDETAILED TEST RESULTS\n\n";

    for (const auto &result : results)
    {

        cout << (result.success ? "[PASS] " : "[FAIL] ")
             << result.name << "\n";

        cout << "Expected: ";
        printVector(result.expected);

        cout << "\nActual:   ";
        printVector(result.actual);

        cout << "\n\n";
    }

    return (failed == 0) ? 0 : 1;
}
