class Solution:
    def findContentChildren(self, g: List[int], s: List[int]) -> int:
        g.sort()
        s.sort()
        ret = 0
        for i in s:
            idx = bisect.bisect_right(g,i)
            if idx > ret:
                ret+=1
        return ret