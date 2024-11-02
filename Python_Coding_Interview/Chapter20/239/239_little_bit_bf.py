class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        num2c = [0] * 20001
        ret = []
        max_v = -10001
        for i in range(k):
            max_v = max(max_v, nums[i])
            num2c[nums[i] + 10000] += 1
        ret.append(max_v)
        for i in range(k, len(nums)):
            max_v = max(max_v, nums[i])
            num2c[nums[i] + 10000] += 1
            num2c[nums[i-k] + 10000] -= 1
            if nums[i-k] == max_v and num2c[max_v + 10000] == 0:
                max_v = max(nums[i-k+1:i+1])
            ret.append(max_v)
        return ret