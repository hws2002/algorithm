class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        if not nums:
            return -10001

        if len(nums) == 1:
            return nums[0]
        mid = len(nums) // 2
        ret = max( self.maxSubArray(nums[:mid]), \
                    self.maxSubArray(nums[mid+1:]))

        midLsum = nums[mid]
        maxR = 0
        sumR = 0
        r = mid+1
        l = mid -1
        while r < len(nums):
            sumR += nums[r]
            maxR = max(maxR, sumR)
            r+=1
        midLsum += maxR
        sumR = 0
        maxR = 0
        while l >= 0:
            sumR += nums[l]
            maxR = max(maxR, sumR)
            l-=1
        midLsum += maxR
        return max(ret, midLsum)