class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        ret = max(nums)
        i = len(nums)-1
        partial_sum = 0
        while i >= 0:
            if partial_sum + nums[i] > 0:
                partial_sum += nums[i]
                ret = max(ret, partial_sum)
            else :
                partial_sum = 0
            i-=1
        return ret