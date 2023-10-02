# 2038. Remove Colored Pieces if Both Neighbors are the Same Color
[LeetCode - 2038. Remove Colored Pieces if Both Neighbors are the Same Color](https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/?envType=daily-question&envId=2023-10-01)
## Intuition

substring ‘AAA’혹은 ‘BBB’ 을 찾는 문제이다.

Alice의 턴에는 ‘AAA’ 를, Bob의 턴에는 ‘BBB’를 찾아야 하는데, brute force로 매턴마다 scan한다면, $O(n^2)$ 의 시간안에 해결할 수 있다.

하지만 굳이 매턴마다 scan해야 하는가? 다음과 같은 사실을 주목하자

> Alice 의 턴에 remove에 성공했다고 치자, 그럼 이것은 Bob의 removal 성공여부에 영향을 미치지않는다.
> 

즉, 우리는 한번만 scan하여 substring ‘AAA’ 와 ‘BBB’의 출현횟수를 기록한 다음, 더 큰쪽이 이긴다고 하면된다. (만약 같다면, Alice가 먼저 플레이하므로, Bob의 승리)

KMP, BM 알고리즘을 써야 하나 생각했지만, 그것까지 갈 필요도 없었다…

## Approach

“적절한” string method 로 해결했다.

```cpp
class Solution {
public:

    int countOverlappingPattern(
        const string& colors,
        const string& pattern
    ){
        int count = 0;
        for (size_t i = 0; i <= colors.size() - pattern.size(); i++) {
            if (colors.substr(i, pattern.size()) == pattern) {
                count++;
            }
        }
        return count;
    };

    bool winnerOfGame(string colors) {
        if(colors.size() <= 2) return false;
        string A_pattern = "AAA";
        string B_pattern = "BBB";
        int A_count = countOverlappingPattern(colors,A_pattern);
        int B_count = countOverlappingPattern(colors,B_pattern);
        return A_count > B_count ? true : false;
    };
};
```