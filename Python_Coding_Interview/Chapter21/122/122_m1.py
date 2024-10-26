class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        ret = 0
        for i in range(1, len(prices)):
            ret += max(0, prices[i] - prices[i-1])
        return ret