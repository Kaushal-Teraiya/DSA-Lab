/*
    LeetCode 844 - Backspace String Compare
    Difficulty: Easy
    Topic: Stack / Two Pointers

    ------------------------------------------------------------
    PROBLEM STATEMENT
    ------------------------------------------------------------

    Given two strings s and t, return true if they are equal
    when both are typed into empty text editors.

    The character '#' represents a backspace.

    A backspace removes the previous character, if one exists.
    If there is no previous character, the backspace does nothing.

    Note that after backspacing an empty text, the text will
    remain empty.

    ------------------------------------------------------------
    EXAMPLES
    ------------------------------------------------------------

    Example 1:

    Input:
    s = "ab#c"
    t = "ad#c"

    Output:
    true

    Explanation:
    Both strings become "ac" after backspacing.


    Example 2:

    Input:
    s = "ab##"
    t = "c#d#"

    Output:
    true

    Explanation:
    Both strings become an empty string.


    Example 3:

    Input:
    s = "a#c"
    t = "b"

    Output:
    false

    Explanation:
    s becomes "c", while t becomes "b".


    Example 4:

    Input:
    s = "a##c"
    t = "#a#c"

    Output:
    true

    ------------------------------------------------------------
    CONSTRAINTS
    ------------------------------------------------------------

    1 <= s.length, t.length <= 200

    s and t only contain lowercase letters and '#' characters.

    ------------------------------------------------------------
    APPROACH NOTES
    ------------------------------------------------------------

    Possible data structure:
    - Stack

    Consider:
    - Processing both strings independently.
    - Handling backspace when the stack is empty.
    - Comparing the final contents of both stacks.
    - Comparing every character, not just the top element.
    - Avoiding calls to top() on an empty stack.

    ------------------------------------------------------------
    IMPLEMENTATION
    ------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution
{
public:
    bool backspaceCompare(string s, string t)
    {
        stack<char> stackS;
        stack<char> stackT;

        int n = s.size();
        int m = t.size();

        for (int i = 0; i < n; i++)
        {
            if (s[i] == '#')
            {
                if (!stackS.empty())
                {
                    stackS.pop();
                }
            }
            else
            {
                stackS.push(s[i]);
            }
        }

        for (int i = 0; i < m; i++)
        {
            if (t[i] == '#')
            {
                if (!stackT.empty())
                {
                    stackT.pop();
                }
            }
            else
            {
                stackT.push(t[i]);
            }
        }

        if (stackS.size() != stackT.size())
            return false;

        while (!stackS.empty() && !stackT.empty())
        {
            if (stackS.top() == stackT.top())
            {
                stackS.pop();
                stackT.pop();
            }
            else
            {
                return false;
            }
        }

        return stackS.empty() && stackT.empty();
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
            {"Example 1 - Basic backspace",
             "ab#c",
             "ad#c",
             true},
            {"Example 2 - Both become empty",
             "ab##",
             "c#d#",
             true},
            {"Example 3 - Different final strings",
             "a#c",
             "b",
             false},
            {"Example 4 - Leading backspaces",
             "a##c",
             "#a#c",
             true},
            {"No backspaces",
             "abc",
             "abc",
             true},
            {"Different strings without backspaces",
             "abc",
             "abd",
             false},
            {"Backspace at the beginning",
             "#abc",
             "abc",
             true},
            {"All characters removed",
             "abc###",
             "###",
             true},
            {"Multiple consecutive backspaces",
             "a###b",
             "b",
             true},
            {"Backspace changes final comparison",
             "xywrrmp",
             "xywrrmu#p",
             true}};

    Solution solution;
    vector<TestResult> results;

    int passed = 0;
    int failed = 0;

    for (const TestCase &test : testCases)
    {
        bool actual = solution.backspaceCompare(test.s, test.t);
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
    cout << "    BACKSPACE STRING COMPARE - SUMMARY\n";
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
