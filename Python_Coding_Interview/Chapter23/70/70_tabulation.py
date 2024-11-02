class Solution:
    def climbStairs(self, n: int) -> int:
        if n <= 2:
            return n
        x, y = 1, 2
        n -= 2
        while n:
            x, y = y, x+y
            n-=1
        return y
