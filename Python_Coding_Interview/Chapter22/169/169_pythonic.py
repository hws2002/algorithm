class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        counter = Counter(nums)
        # print(counter)
        # print(counter.most_common(max(1,len(nums)//2)))
        return counter.most_common(max(1,len(nums)//2))[0][0]
        