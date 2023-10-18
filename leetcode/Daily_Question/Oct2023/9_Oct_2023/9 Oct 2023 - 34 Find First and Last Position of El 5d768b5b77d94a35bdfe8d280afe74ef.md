# 9 Oct 2023 - 34. Find First and Last Position of Element in Sorted Array

[LeetCode - The World's Leading Online Programming Learning Platform](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/?envType=daily-question&envId=2023-10-08)

Given an array of integers `nums` sorted in non-decreasing order, find the starting and ending position of a given `target` value.

If `target` is not found in the array, return `[-1, -1]`.

You must write an algorithm with `O(log n)` runtime complexity.

**Example 1:**

```
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

```

**Example 2:**

```
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

```

**Example 3:**

```
Input: nums = [], target = 0
Output: [-1,-1]

```

**Constraints:**

- `0 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`
- `nums` is a non-decreasing array.
- `-10^9 <= target <= 10^9`

---

## Intuition & Approach

Binary Search의 일종이다. 이전에 binary search lab 을 했던 경험으로 쉽게 풀 수 있었다.

먼저 nums[i] == target인 아무i를 찾은후에, 왼쪽 오른쪽으로 각각 iterate하며 first, last position을 찾으면 되었다.

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size() == 0)return vector<int>{-1,-1};
        int lo = -1; int hi = nums.size();
        bool found = false;
        int mid;
        while(lo+1< hi){
            mid = (lo+hi)>>1;
            if(nums[mid] == target){
                found = true;
                break;
            }
            else if(nums[mid] < target)
                lo = mid;
            else 
                hi = mid;
        }
        if(!found) return vector<int>{-1,-1};
        int start = mid;
        int end = start;
        printf("start : %d \n", start);
        printf("end : %d \n", end);
        while(nums[end] == target){
            if(end < nums.size()-1 && nums[end+1] == target){
                end++;
            } else {
                break;
            }
        }
        while(nums[start] == target){
            if(start > 0 && nums[start-1] == target) {
                start--;
            } else {
                break;
            }
        }
        return vector<int>{start,end};
    }
};
```