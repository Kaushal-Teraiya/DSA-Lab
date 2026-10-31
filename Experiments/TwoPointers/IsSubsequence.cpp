/*
    LeetCode 392 - Is Subsequence
    Difficulty: Easy
    Topic: Two Pointers / String

    ------------------------------------------------------------
    PROBLEM STATEMENT
    ------------------------------------------------------------

    Given two strings s and t, return true if s is a subsequence
    of t, or false otherwise.

    A subsequence of a string is a new string generated from the
    original string with some characters (possibly none) deleted
    without changing the relative order of the remaining
    characters.

    For example, "ace" is a subsequence of "abcde", while
    "aec" is not.

    ------------------------------------------------------------
    EXAMPLES
    ------------------------------------------------------------

    Example 1:

    Input:
    s = "abc"
    t = "ahbgdc"

    Output:
    true

    Explanation:
    The characters a, b, and c appear in t in the same order.


    Example 2:

    Input:
    s = "axc"
    t = "ahbgdc"

    Output:
    false

    Explanation:
    The character x cannot be matched in the required order.


    Example 3:

    Input:
    s = ""
    t = "abc"

    Output:
    true

    Explanation:
    An empty string is a subsequence of every string.

    ------------------------------------------------------------
    CONSTRAINTS
    ------------------------------------------------------------

    0 <= s.length <= 100
    0 <= t.length <= 10^4

    s and t consist only of lowercase English letters.

    ------------------------------------------------------------
    APPROACH NOTES
    ------------------------------------------------------------

    Data structure:
    - Two Pointers

    Consider:
    - One pointer tracks progress through s.
    - Another pointer traverses t.
    - When characters match, advance both pointers.
    - When characters differ, advance only the pointer in t.
    - Determine whether every character of s was matched.

    ------------------------------------------------------------
    IMPLEMENTATION
    ------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        int i = 0;
        int j = 0;

        while (j < t.size() && i < s.size())
        {
            if (s[i] == t[j])
            {
                i++;
                j++;
            }
            else
            {
                j++;
            }
        }

        return i == s.size();
    }
};

// ------------------------------------------------------------
// TEST HARNESS
// ------------------------------------------------------------

struct TestCase
{
    string name;
    string s;
    string t;
    bool expected;
};

struct TestResult
{
    string name;
    bool expected;
    bool actual;
    bool passed;
};

int main()
{
    vector<TestCase> testCases =
        {
            {"Example 1 - Basic subsequence",
             "abc",
             "ahbgdc",
             true},
            {"Example 2 - Missing character",
             "axc",
             "ahbgdc",
             false},
            {"Empty subsequence",
             "",
             "abc",
             true},
            {"Identical strings",
             "abc",
             "abc",
             true},
            {"Single matching character",
             "a",
             "abc",
             true},
            {"Single missing character",
             "z",
             "abc",
             false},
            {"Repeated characters",
             "aaa",
             "aaab",
             true},
            {"Insufficient repeated characters",
             "aaaa",
             "aaa",
             false},
            {"Characters in wrong order",
             "abc",
             "cba",
             false},
            {"Characters separated by many characters",
             "ace",
             "abcde",
             true}};

    Solution solution;
    vector<TestResult> results;

    int passed = 0;
    int failed = 0;

    for (const TestCase &test : testCases)
    {
        bool actual = solution.isSubsequence(test.s, test.t);
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

    // Summary before detailed results.

    cout << "\n========================================\n";
    cout << "       IS SUBSEQUENCE - TEST SUMMARY\n";
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

        cout << "        Expected: "
             << (result.expected ? "true" : "false")
             << " | Actual: "
             << (result.actual ? "true" : "false")
             << '\n';
    }

    cout << "----------------------------------------\n";

    return failed == 0 ? 0 : 1;
}
