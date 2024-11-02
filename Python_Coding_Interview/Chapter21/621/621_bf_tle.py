class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        counter = Counter(tasks)
        ret = 0
        # print(counter)
        cool = collections.defaultdict(int)
        task = []
        while counter:
            mck = counter.most_common(26)
            # print("mck : ",mck)

            for t in cool:
                cool[t] = max(0, cool[t] - 1)
            # print("cool : ", cool)

            next_t = '#'
            for i in range(len(mck)):
                if cool[mck[i][0]] <= 0:
                    next_t = mck[i][0]
                    cool[next_t] = n+1
                    counter[next_t] -= 1
                    if counter[next_t] <= 0:
                        del counter[next_t]
                    break
            # if next_t != '#': # handl next_t
            task.append(next_t)
            ret+=1
            # else : # idle
            # print(task)

        return ret