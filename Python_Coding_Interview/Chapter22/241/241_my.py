class Solution:
    def diffWaysToCompute(self, expression: str) -> List[int]:
        
        # parse        
        def isoperand(s) -> bool:
            return ord('0') <= ord(s) and ord(s) <= ord('9')

        op = []
        i = 0
        while i < len(expression):
            operand : int = 0
            if isoperand(expression[i]):
                while i < len(expression) and isoperand(expression[i]):
                    operand *= 10
                    operand += int(expression[i])
                    i+=1
                op.append(operand)
            else :
                op.append(expression[i])
                i+=1
        # print(op)

        def split(exp : list) -> list:
            if len(exp) == 1:
                return [exp[0]]

            ret = []
            for j in range(len(exp)):
                if not isinstance(exp[j],int):
                    l = split(exp[:j])
                    r = split(exp[j+1:])
                    if exp[j] == '+':
                        for num1 in l : 
                            for num2 in r :
                                ret.append(num1 + num2)
                    elif exp[j] == '-':
                        for num1 in l : 
                            for num2 in r :
                                ret.append(num1 - num2)
                    else :
                        for num1 in l : 
                            for num2 in r :
                                ret.append(num1 * num2)
                        
            return ret
            
        return split(op)
