/*
LeetCode #4: Median of Two Sorted Arrays

PROBLEM STATEMENT
-----------------
Given two sorted arrays nums1 and nums2 of sizes m and n,
return the median of the two sorted arrays.

The overall run time complexity should be O(log(m + n)).

DEFINITION
----------
- If the combined array has an odd number of elements,
  the median is the middle element.
- If it has an even number of elements,
  the median is the average of the two middle elements.

EXAMPLE 1
---------
Input:
nums1 = [1, 3]
nums2 = [2]

Output: 2.0

Explanation:
The combined sorted array is [1, 2, 3].
The median is 2.

EXAMPLE 2
---------
Input:
nums1 = [1, 2]
nums2 = [3, 4]

Output: 2.5

Explanation:
The combined sorted array is [1, 2, 3, 4].
The median is (2 + 3) / 2 = 2.5.

CONSTRAINTS
-----------
- nums1.size() == m
- nums2.size() == n
- 0 <= m <= 1000
- 0 <= n <= 1000
- 1 <= m + n <= 2000
- -10^6 <= nums1[i], nums2[i] <= 10^6
- nums1 and nums2 are sorted in non-decreasing order.

TARGET
------
Time: O(log(m + n))
Space: O(1) auxiliary space

*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1,
                                  vector<int> &nums2)
    {
        // TODO: Implement your solution
        if (nums1.size() > nums2.size())
        {
            swap(nums1, nums2);
        }

        int n = nums1.size();
        int m = nums2.size();
        int left = 0;
        int right = n;

        while (left <= right)
        {
            // mid is the mid of the nums1 paritition
            // j is the num of elements required to make the total element as x after combining left halves of both arrays.
            // Where x is the number of elements of both arrays combined /2 & if odd left half must have 1 extra element
            int mid = left + (right - left) / 2;
            int j = -mid + (n + m + 1) / 2;

            // if the partition is such that  there are no elements in the left half left then set it to INT_MIN to avoid out of bounds exception.
            // else use nums1[mid-1]; meaning the boundary element in the left half partition
            //       for e.g   [1 , 3 | 8]       -> nums1 array
            //                 [2 , 7 | 10 , 11] -> nums2 array
            //  Here 3 is boundary element just before mid so mid - 1 .

            // mid == n is the opposite case of mid == 0 we can just keep using mid
            int left1 = (mid == 0) ? INT_MIN : nums1[mid - 1];
            int right1 = (mid == n) ? INT_MAX : nums1[mid];

            int left2 = (j == 0) ? INT_MIN : nums2[j - 1];
            int right2 = (j == m) ? INT_MAX : nums2[j];

            // cross boundary checking to make sure a bigger num isnt present in the left half.
            //       for e.g   [1 , 3 | 8]       -> nums1 array
            //                 [2 , 7 | 10 , 11] -> nums2 array
            // Compare 3 with 10 and 7 with 8
            if (left1 <= right2 && left2 <= right1)
            {
                // if odd number of elements in the combined array then return maximum from the left halves of nums1 , nums2
                // else return average by choosing max element from left and min element from right half of nums1 , nums2
                if ((n + m) % 2 == 1)
                {
                    return max(left1, left2);
                }
                else
                {
                    return (max(left1, left2) + min(right1, right2)) / 2.0;
                }
            }
            else if (left1 > right2) // if cross boundary check fails for nums1 left  , nums2 right move the cut to left so mid - 1
            {
                right = mid - 1;
            }
            else if (left2 > right1) // else if cross boundary check fails for nums2 left , nums1 right move the cut to  right by mid + 1
            {
                left = mid + 1;
            }
        }

        return 0.0;
    }
};

int main()
{
    Solution solution;

    struct TestCase
    {
        vector<int> nums1;
        vector<int> nums2;
        double expected;
    };

    vector<TestCase> tests = {
        {{1, 3}, {2}, 2.0},
        {{1, 2}, {3, 4}, 2.5},
        {{}, {1}, 1.0},
        {{2}, {}, 2.0},
        {{0, 0}, {0, 0}, 0.0},
        {{1, 3}, {2, 7}, 2.5},
        {{1, 2, 3}, {4, 5, 6}, 3.5},
        {{-5, -3, -1}, {-4, -2, 0}, -2.5},
        {{1}, {2, 3, 4, 5, 6}, 3.5},
        {{1, 2, 3, 4, 5}, {6}, 3.5}};

    int passed = 0;

    for (int i = 0; i < tests.size(); i++)
    {
        double result = solution.findMedianSortedArrays(
            tests[i].nums1, tests[i].nums2);

        bool correct = abs(result - tests[i].expected) < 1e-9;

        cout << "Test " << i + 1 << ": "
             << (correct ? "PASS" : "FAIL")
             << " | Expected: " << tests[i].expected
             << " | Got: " << result << '\n';

        if (correct)
            passed++;
    }

    cout << "\nPassed: " << passed << "/" << tests.size() << '\n';

    return 0;
}
