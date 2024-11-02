class Solution:
    def diffWaysToCompute(self, expression: str) -> List[int]:
        
        def compute(l, r, op):
            ret = []
            for num1 in l:
                for num2 in r:
                    ret.append(eval(str(num1) + op + str(num2)))
            return ret
        
        if expression.isdigit():
            return [int(expression)]

        ret = []
        for idx, value in enumerate(expression):
            if value in "-+*":
                l = self.diffWaysToCompute(expression[:idx])
                r = self.diffWaysToCompute(expression[idx+1:])
                ret.extend(compute(l, r, value))
        return ret