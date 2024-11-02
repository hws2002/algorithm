class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        num2c = [0] * 20001
        ret = []
        h = []
        max_v = -10001
        for i in range(k):
            max_v = max(max_v, nums[i])
            num2c[nums[i]+10000] += 1
            heapq.heappush(h, -nums[i])
        ret.append(max_v)
        for i in range(k, len(nums)):
            max_v = max(max_v, nums[i])
            num2c[nums[i] + 10000] += 1
            num2c[nums[i-k] + 10000] -= 1
            
            if nums[i-k] == max_v and num2c[max_v + 10000] == 0:
                # change max_v
                while h and num2c[heapq.nsmallest(1,h)[0]*-1 + 10000] == 0:
                    heapq.heappop(h)
                heapq.heappush(h, -nums[i])  
                max_v = heapq.nsmallest(1,h)[0] * -1
            else :
                heapq.heappush(h, -nums[i])                
            ret.append(max_v)
        return ret