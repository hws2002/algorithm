class Solution:
    def reconstructQueue(self, people: List[List[int]]) -> List[List[int]]:
        ret = []
        people.sort(key = itemgetter(1,0))
        # print(people)
        ret.append(people[0])
        for j in range(1, len(people)):
            h, k = people[j]
            i = 0
            while i < len(ret) and ( k or ret[i][0] < h) :
                if ret[i][0] >= h:
                    k -= 1
                i += 1
            ret.insert(i,people[j])

        return ret