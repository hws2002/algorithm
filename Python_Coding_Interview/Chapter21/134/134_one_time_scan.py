class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        if sum(gas) < sum(cost):
            return -1
        
        s, f = 0, 0
        for i in range(len(gas)):
            if f + gas[i] - cost[i] < 0:
                s = i+1
                f = 0
            else :
                f += gas[i] - cost[i]

        return s