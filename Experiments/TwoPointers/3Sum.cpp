#include <bits/stdc++.h>
using namespace std;

/*
LeetCode #15 — 3Sum
Difficulty: Medium
Topic: Arrays, Sorting, Two Pointers

PROBLEM:
Given an integer array nums, return all unique triplets
[nums[i], nums[j], nums[k]] such that:

- i, j, and k are distinct indices.
- nums[i] + nums[j] + nums[k] == 0.

The answer must not contain duplicate triplets.

EXAMPLES:
Input:  nums = {-1, 0, 1, 2, -1, -4}
Output: {{-1, -1, 2}, {-1, 0, 1}}

YOUR TASK:
Implement vector<vector<int>> threeSum(vector<int>& nums).

TEST CASES:
1. {-1, 0, 1, 2, -1, -4}
   -> {{-1, -1, 2}, {-1, 0, 1}}

2. {0, 1, 1}
   -> {}

3. {0, 0, 0}
   -> {{0, 0, 0}}

4. {-2, 0, 1, 1, 2}
   -> {{-2, 0, 2}, {-2, 1, 1}}

5. {-1, -1, -1, 2, 2}
   -> {{-1, -1, 2}}

6. {-4, -2, -2, -2, 0, 2, 2, 2, 4}
   -> {{-4, 0, 4}, {-4, 2, 2}, {-2, -2, 4}, {-2, 0, 2}}

7. {1, 2, -2, -1}
   -> {}

8. {-3, 0, 1, 2, -1, 1, -2}
   -> {{-3, 1, 2}, {-2, 0, 2}, {-2, 1, 1}, {-1, 0, 1}}

9. {-1, 0, 1, 0}
   -> {{-1, 0, 1}}

10. {-5, -3, -1, 0, 2, 4, 6}
    -> {{-5, -1, 6}, {-5,  -?}}

TARGET:
Time: O(n^2)
Extra space: O(1) auxiliary space, excluding output
*/

class Solution
{
public:
   vector<vector<int>> threeSum(vector<int> &nums)
   {
      // TODO: Solve it yourself.
      int n = nums.size();
      unordered_map<int, int> exists;
      vector<vector<int>> answer;

      for (int i = 0; i < n; i++)
      {
         exists[nums[i]] = i;
      }

      for (int i = 0; i < n; i++)
      {
         for (int j = i + 1; j < n; j++)
         {
            int k = -nums[i] - nums[j];

            if (exists.find(k) != exists.end() && exists[k] != i && exists[k] != j)
            {
               vector<int> triplet = {nums[i], nums[j], k};
               sort(triplet.begin(), triplet.end());
               
               bool foundDuplicate = false;

               for (int x = 0; x < answer.size(); x++)
               {
                  if (answer[x] == triplet)
                  {
                     foundDuplicate = true;
                     break;
                  }
               }

               if (!foundDuplicate)
               {
                  answer.push_back(triplet);
               }
            }
         }
      }
      return answer;
   }
};

void runTest(vector<int> nums, vector<vector<int>> expected, int testNumber)
{
   Solution solution;
   vector<vector<int>> actual = solution.threeSum(nums);

   auto normalize = [](vector<vector<int>> &triplets)
   {
      for (auto &triplet : triplets)
      {
         sort(triplet.begin(), triplet.end());
      }
      sort(triplets.begin(), triplets.end());
   };

   normalize(actual);
   normalize(expected);

   cout << "Test " << testNumber << ": "
        << (actual == expected ? "PASS" : "FAIL") << '\n';

   if (actual != expected)
   {
      cout << "Expected triplets: " << expected.size()
           << ", Actual triplets: " << actual.size() << '\n';
   }
}

int main()
{
   runTest({-1, 0, 1, 2, -1, -4},
           {{-1, -1, 2}, {-1, 0, 1}}, 1);
   runTest({0, 1, 1}, {}, 2);
   runTest({0, 0, 0}, {{0, 0, 0}}, 3);
   runTest({-2, 0, 1, 1, 2},
           {{-2, 0, 2}, {-2, 1, 1}}, 4);
   runTest({-1, -1, -1, 2, 2}, {{-1, -1, 2}}, 5);
   runTest({-4, -2, -2, -2, 0, 2, 2, 2, 4},
           {{-4, 0, 4}, {-4, 2, 2}, {-2, -2, 4}, {-2, 0, 2}}, 6);
   runTest({1, 2, -2, -1}, {}, 7);
   runTest({-3, 0, 1, 2, -1, 1, -2},
           {{-3, 1, 2}, {-2, 0, 2}, {-2, 1, 1}, {-1, 0, 1}}, 8);
   runTest({-1, 0, 1, 0}, {{-1, 0, 1}}, 9);
   runTest({-5, -3, -1, 0, 2, 4, 6},
           {{-5, -1, 6}, {-3, -1, 4}}, 10);

   return 0;
}
