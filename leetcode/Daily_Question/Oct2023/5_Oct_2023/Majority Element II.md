## Intuition

맨처음 든생각은 …  

> 정답의 길이는 2를 넘을수가없다.
> 

그래서 다음처럼 brute force 의사코드를 짜보았다.  

> `hash map` : element → number of appearance 
`threshold` : least number of appearance to be included in `res`
맨처음 threshold를 가장 먼저 구한다음, 주어진 배열을 순차적으로 iterrate하면서, 만약 출현 횟수가 threshold를 넘었고, 이미 `res` 안에 포함된적이 없다면, `res`에 포함시킨다. 동시에 `res`의 크기가 2를 넘어갔다면, 그 즉시 중단한다.
> 

물론 이방식은 굉장히 간단하지만, 그만큼 효율적이지 못하다.

우선 시간복잡도부터 매 iterration마다 해쉬맵에서 query（$O(n\log n)$의 시간복잡도)를 해야하므로, 절대 linear time 안에는 끝낼 수 없다.

그렇게 시간복잡도를 어떻게 개선시킬 수 있을까 라고 고민하던중, 다음과 같은 follow-up을 발견했다..

**Follow up:** Could you solve the problem in linear time and in `O(1)` space?

이 문제를 처음 봤을때, 우선 공간복잡도는 결코 $O(1)$안에 할 수는 없다고 생각했다. 그런데 시간복잡도와 공간복잡도 모두 linear time, $O(1)$안에 해결하는 방법이 있다고 하니, 더 깊게 생각해보게되었다.

그러다가 다음과 같은 사실을 발견했다.

> 
> 

## Approach

### brute force

```c++
class Solution {
public:

    bool Inres(const vector<int>& res, int valueToFind){
        for(int i = 0 ; i< res.size(); i++){
            printf("%dth element : %d \n", i+1, res[i]);
        }
        if (res.empty()) return false;
        return find(res.begin(), res.end(), valueToFind) != res.end() ? true : false ; 
    }
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;
        if(nums.size() == 1){
            res = nums;
            return res;
        }
        if(nums.size() == 2 ){
            if (nums[0] == nums[1]){
                res.push_back(nums[0]);
            } else {
                res.push_back(nums[0]);
                res.push_back(nums[1]);
            }
            return res;
        }
        unordered_map<int, int> element2count;
        int threshold = static_cast<int>(nums.size()) / 3;
        printf("threshold : %d \n", threshold);
        for(int i =0; i < nums.size(); i++){
            auto it = element2count.find(nums[i]);
            if( it != element2count.end()){
                // already in hashmap
                printf("(i=%d) num, count : %d, %d \n",i, nums[i], it->second);
                it->second += 1;
                if (it->second > threshold && (!Inres(res,it->first))) {
                    printf("(i=%d) pushing element %d to res \n",i,it->first);
                    res.push_back(it->first);
                    if (res.size() >= 2) break;
                }
            } else {
                printf("(i=%d) adding new element : %d \n", i,nums[i]);
                element2count[nums[i]] = 1;
            }
        }
        return res;
    }
};
```