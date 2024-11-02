class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        max_pg = -1
        max_i = len(gas)
        post_g = 0
        for i in range(len(gas)-1, -1, -1):
            post_g += gas[i] - cost[i]
            if max_pg < post_g:
                max_pg = post_g
                max_i = i
        if post_g < 0 :
            return -1
        return max_i