#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main()
{
    cout << "DSA Sandbox ready!" << '\n';

    // Median of Two Sorted Arrays
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};

    // Your code goes here

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
        int mid = left + (right - left) / 2;
        int j = -mid + (n + m + 1) / 2;

        int left1 = (mid == 0) ? INT_MIN : nums1[mid - 1];
        int right1 = (mid == n) ? INT_MAX : nums1[mid];

        int left2 = (j == 0) ? INT_MIN : nums2[j - 1];
        int right2 = (j == m) ? INT_MAX : nums2[j];

        if (left1 <= right2 && left2 <= right1)
        {
            if ((n + m) % 2 == 1)
            {
                return max(left1, left2);
            }
            else
            {
                return (max(left1,left2) + min(right1, right2)) / 2.0;
            }
        }
        else if (left1 > right2)
        {
            right = mid - 1;
        }
        else if (left2 > right1)
        {
            left = mid + 1;
        }
    }

    return 0;
}
