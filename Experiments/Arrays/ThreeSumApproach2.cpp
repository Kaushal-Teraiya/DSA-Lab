// LeetCode #15 - 3Sum
// Approach 2: Sorting + Two Pointers
// Time Complexity: O(n^2)
// Space Complexity: O(1) auxiliary space, excluding output

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {

        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {

            // we are fixing on 1 index and doing the same for all nums so we wanna prevent using the same number again.
            //  That's what this check is for.
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }

            // Initializing left and right pointers with i+1 because  i will be our fixed index for the time being of one loop iteration.
            int left = i + 1;
            int right = nums.size() - 1;

            //while they don't cross each other.
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right]; //pre calc the sum.

                if (sum == 0) // if it's zero then we've got what we were finding so push it in the answer vector.
                {
                    //We push triplets in the answer array it allows duplicate element in one triplet.
                    ans.push_back({nums[i], nums[left], nums[right]});
                    //move both pointers.
                    left++;
                    right--;

                    //after updating the pointer if you stumble upon the same element again as the previous one. move the respective pointers.
                    //This part specifically prevents duplicate triplets from forming again.
                    while (left < right && nums[left] == nums[left - 1])
                        left++;

                    while (left < right && nums[right] == nums[right + 1])
                        right--;
                }
                else if (sum < 0) //self explanatory.. if sum is less than 0 we increase left pointer to get greater values since the array is sorted.
                {
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }

        return ans;
    }
};

int main()
{
    Solution solution;

    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> result = solution.threeSum(nums);

    for (const auto &triplet : result)
    {
        cout << "[" << triplet[0] << ", "
             << triplet[1] << ", "
             << triplet[2] << "]\n";
    }

    return 0;
}
