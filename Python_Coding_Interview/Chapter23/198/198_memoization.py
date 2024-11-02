class Solution:
    def rob(self, nums: List[int]) -> int:
        dp = [-1] * 101
        def fdp(idx : int) -> int:
            if idx >= len(nums)-2:
                return max(nums[idx:])
            if dp[idx] > -1:
                return dp[idx]
            dp[idx] = max( nums[idx] + fdp(idx+2), \
                            fdp(idx+1))
            return dp[idx]
        return fdp(0)