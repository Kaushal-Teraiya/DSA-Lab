/*
    LeetCode 1047 - Remove All Adjacent Duplicates in String
    Difficulty: Easy
    Topic: Stack / String

    ------------------------------------------------------------
    PROBLEM STATEMENT
    ------------------------------------------------------------

    You are given a string s consisting of lowercase English
    letters.

    A duplicate removal consists of choosing two adjacent and
    equal letters and removing them.

    You repeatedly make duplicate removals until you can no
    longer do so.

    Return the final string after all duplicate removals have
    been made.

    The answer is guaranteed to be unique.

    ------------------------------------------------------------
    EXAMPLES
    ------------------------------------------------------------

    Example 1:

    Input:
    s = "abbaca"

    Output:
    "ca"

    Explanation:
    "abbaca" -> "aaca" -> "ca"


    Example 2:

    Input:
    s = "azxxzy"

    Output:
    "ay"

    Explanation:
    "azxxzy" -> "azzy" -> "ay"

    ------------------------------------------------------------
    CONSTRAINTS
    ------------------------------------------------------------

    1 <= s.length <= 10^5

    s consists of lowercase English letters.

    ------------------------------------------------------------
    APPROACH NOTES
    ------------------------------------------------------------

    Data structure:
    - Stack

    Consider:
    - Processing characters from left to right.
    - Comparing the current character with the stack top.
    - Removing both characters when they are equal.
    - Keeping a character when no adjacent duplicate exists.
    - Constructing the final string in the correct order.

    ------------------------------------------------------------
    IMPLEMENTATION
    ------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

class Solution
{
public:
    string removeDuplicates(string s)
    {
        int n = s.size();
        stack<int> monostack;

        for (int i = 0; i < n; i++)
        {
            if (!monostack.empty() && monostack.top() == s[i])
            {
                monostack.pop();
            }
            else
            {
                monostack.push(s[i]);
            }
        }

        string ans = "";
        while (!monostack.empty())
        {
            ans += monostack.top();
            monostack.pop();
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

// ------------------------------------------------------------
// TEST HARNESS
// ------------------------------------------------------------

struct TestCase
{
    string name;
    string input;
    string expected;
};

struct TestResult
{
    string name;
    string expected;
    string actual;
    bool passed;
};

int main()
{
    vector<TestCase> testCases =
        {
            {"Example 1 - Basic adjacent duplicates",
             "abbaca",
             "ca"},
            {"Example 2 - Multiple duplicate pairs",
             "azxxzy",
             "ay"},
            {"No duplicates",
             "abcdef",
             "abcdef"},
            {"All characters identical",
             "aaaa",
             ""},
            {"Single character",
             "a",
             "a"},
            {"Two identical characters",
             "aa",
             ""},
            {"Two different characters",
             "ab",
             "ab"},
            {"Cascading duplicate removal",
             "acbbc",
             "a"},
            {"Duplicates at both ends",
             "aabccba",
             "a"},
            {"Long consecutive duplicate groups",
             "aabbccddeeff",
             ""}};

    Solution solution;
    vector<TestResult> results;

    int passed = 0;
    int failed = 0;

    for (const TestCase &test : testCases)
    {
        string actual = solution.removeDuplicates(test.input);
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
    cout << "  REMOVE ADJACENT DUPLICATES - SUMMARY\n";
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

        cout << "        Expected: \"" << result.expected
             << "\" | Actual: \"" << result.actual << "\"\n";
    }

    cout << "----------------------------------------\n";

    return failed == 0 ? 0 : 1;
}
