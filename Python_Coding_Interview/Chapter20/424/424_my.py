class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        d = collections.defaultdict(list)
        for i, v in enumerate(s):
            d[v].append(i)
        
        ret = -1
        for c in d:
            lst = d[c]
            b = k
            i = 0
            # print(c,lst)
            l = r = 0
            while r < len(s):
                # r+=1
                if s[r] == c:
                    r+=1
                else :
                    if b > 0:
                        b-=1
                        r+=1
                    else:
                        # print("l,r : ", l, r)
                        ret = max(ret, r-l)
                        while i < len(lst) and l == lst[i]:
                            l+=1
                            i+=1 
                        if s[l] != c:
                            l+=1
                            b+=1
            ret = max(ret, r - l)
        return ret