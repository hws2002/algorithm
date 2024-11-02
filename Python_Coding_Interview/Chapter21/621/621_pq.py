class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        ret = 0
        counter = Counter(tasks)

        while True:
            t = 0
            for task, _ in counter.most_common(n+1):
                t+=1
                ret+=1
                counter.subtract(task)
                # 0 이하인 아이템을 목록에서 제거
                counter += Counter()
            
            if not counter:
                break
            ret += n+1-t
        return ret