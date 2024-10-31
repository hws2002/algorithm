class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        best_sum = -10004
        c_sum = 0
        for num in nums:
            c_sum = max(num, c_sum + num)
            best_sum = max(c_sum, best_sum)
        return best_sum