class Solution:

    def minWindow(self, s: str, t: str) -> str:
        req = Counter(t)
        l = r = 0
        current_map = collections.defaultdict(int)

        ret_s = ""
        ret_n = 100001
        c_required = sum(req.values())
            
        i = 0
        while c_required and i < len(s):
            r+=1
            if s[i] in req:
                if not current_map:
                    l = r = i
                    current_map[s[i]] = 1
                    c_required-=1
                else :
                    current_map[s[i]] += 1
                    if current_map[s[i]] <= req[s[i]]:
                        c_required-=1
                if c_required == 0:
                    ret_n = r - l + 1
                    ret_s = s[l:r+1]                    
            i+=1
        if ret_n == 100001 :
            return ret_s

        while l < len(s) and (current_map[s[l]] > req[s[l]] or s[l] not in req):
            if s[l] in req:
                current_map[s[l]] -= 1
            l+=1
        
        ret_n = r - l + 1
        ret_s = s[l:r+1]

        while i < len(s):
            r+=1
            if s[i] in req:
                current_map[s[i]] += 1
                if current_map[s[i]] > req[s[i]] and s[l] == s[i]:
                    current_map[s[l]] -= 1
                    l += 1
                    while l < len(s) and (s[l] not in req or current_map[s[l]] > req[s[l]]):
                        if s[l] in req:
                            current_map[s[l]] -= 1
                        l+=1
                    if r - l + 1 < ret_n:
                        ret_n = r-l+1
                        ret_s = s[l:r+1]
            i+=1
        return ret_s