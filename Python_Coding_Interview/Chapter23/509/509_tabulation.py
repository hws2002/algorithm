class Solution:
    def fib(self, n: int) -> int:
        if n <= 1:
            return n
        f_ = 0
        f = 1
        n-=1
        while n:
            f_, f = f, f_ + f
            n-=1
        return f