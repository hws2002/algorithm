class Solution:
    def reconstructQueue(self, people: List[List[int]]) -> List[List[int]]:
        heap = []
        for h,k in people:
            heapq.heappush(heap, (-h,k))
        
        ret = []
        while heap:
            h, k = heapq.heappop(heap)
            ret.insert(k,[-h,k])

        return ret