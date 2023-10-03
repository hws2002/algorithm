# 1512. Number of Good Pairs
[LeetCode - 1512. Number of Good Pairs](https://leetcode.com/problems/number-of-good-pairs/description/?envType=daily-question&envId=2023-10-03)
## Intuition

### 1. ${n \choose 2}$

처음 생각난 것은, “**중복조합**”이다.

만약 n개의 같은 숫자가 존재한다면, 여기서 얻을 수있는 good pairs 는 ${n \choose 2}$이다.

constraints 에서 숫자의 범위가 [1,100] 이라고 했으니, 길이가 100인 배열에 각각의 숫자가 몇번씩 출현했는지 기록하고, 마지막에 iterrate 하면서 good pairs 의 출현 횟수를 기록하면 된다.

## 2. 숫자를 기록하는 동시에 good pairs 기록하기

그러면서 생각난것은, 굳이 모든 숫자들을 확인한 후에, 다시한번 iterrate 하며 good pairs를 찾아낼 필요가 없다는것이다.

숫자들을 확인하는 iterration에서, good pairs 또한 기록할 수 있다.
예를 들어, 지금까지 10이 3번 나왔다고 치자. 그렇다면 우리의 nums_count[10] = 3 일것이다. 여기서 그다음 숫자가 10이라면, good pairs는 +nums_count[10]을, nums_count[10] = 4 로 바꿔주면 된다.

첫번째 방식은 ${n \choose 2}$을 계산하는 과정에서 은근 시간소모가 클 수 있다. 그러므로 2번방식이 훨씬 효율적일 것이다.

## Approach

```cpp
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int nums_count[101] = {0};
        int res = 0; // number of good pairs
        for(int i=0 ;i < nums.size(); i++){
            res += nums_count[nums[i]];
            nums_count[nums[i]] += 1;
        }
        return res;
    }
};
```