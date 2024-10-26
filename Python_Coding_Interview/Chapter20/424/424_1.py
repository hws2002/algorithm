class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        left = right = 0
        ret = -1
        counter = collections.Counter()
        for right in range(1, len(s)+1):
            counter[s[right-1]] += 1
            most_char_n = counter.most_common(1)[0][1]

            if right - left - most_char_n > k:
                counter[s[left]] -= 1
                left+=1
                ret = max(ret, right - left)
        ret = max(ret, right - left)
        return ret