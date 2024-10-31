class Solution:
    cache = [0] * 31
    def fib(self, n: int) -> int:
        if self.cache[n] : 
            return self.cache[n]
        if n <= 1 :
            return n
        self.cache[n] = self.fib(n-1) + self.fib(n-2)
        return self.cache[n]