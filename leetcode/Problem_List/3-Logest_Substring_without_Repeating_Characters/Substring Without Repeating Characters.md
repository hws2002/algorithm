# 问题
[LeetCode - 3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/description/)

## Intuition

> 다음과같은 문자열을 고려해보자.
`…(1)…a…(2)…a…(3)…`  
이미 a 가 중복된상황에서, `...(1)...a` 부분의 자세한 정보는 전혀 쓸모없다. 그저 그 부분에서 가장 길었던 중복이없는 longest substring의 길이만 알고있으면되며, longest substring이 될 수 있는 후보군은 `...(2)...a...(3)...` 에서 찾으면 된다.
> 

위와같은 사실로 인해, 자동적으로 set과 queue를 활용한 moving window 방식이 생각났다.

> 현재 s[0,i) 까지 scan한 상태에서, moving window를 Q라고 하자. (queue)
만약 Q가 s[i]를 포함하고있다면, Q의 왼쪽에서부터 s[i]를 pop할 때까지 pop한다. 그리고 다음 문자로 넘어간다
만약 Q가 s[i]를 포함하고있지않다면, Q.push(s[i])한다. 그리고 Q.length()가 현재까지 기록 longest substring length 보다 길다면, 갱신한다.
위 과정에서 Q가 포함하고있는 문자들을 원소로 둔 집합 chatSet을 매순간 갱신시킨다.
> 

## Approach

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.empty()) return 0;
        queue<char> Q;
        set<char> charSet; // keeps record of existing char in P
        Q.push(s[0]);
        charSet.insert(s[0]);
        int longest = Q.size(); 
        for (int i = 1; i < s.size(); i++){
            // check if P includes s[i]
            if( charSet.find(s[i]) != charSet.end()){
                // s[i] exists in the set
                while(!Q.empty() && Q.front() != s[i]){
                    charSet.erase(Q.front());
                    Q.pop();
                }
                Q.pop();
                Q.push(s[i]);
            } else{
                // s[i] doesn't exist in the set
                charSet.insert(s[i]);
                Q.push(s[i]);
                longest = max(longest, static_cast<int>(Q.size()));
                // debug Q
                cout<<"DEBUGGING : CURRENT Q follows -> : "<<endl;
                std::queue<char> copyQ = Q;
                while(!copyQ.empty()) {
                    cout << copyQ.front() << endl;
                    copyQ.pop();
                }
                //debug
            }
        }
        return longest;
    }
};
```

그런데 생각해보니, 굳이 `queue` 가 필요없다는것을 깨달았다.

사실상 우리의 queue는 given string s에서 “**연속**”된 문자들을 저장하고있다.

이말인즉슨, 굳이 queue안에 저장할필요가없고, 그냥 `[시작인덱스, 끝인덱스]` 형식으로 저장해도 같은 정보를 담고있음을 알게되었다. (`charSet` 관련한 operation에서는 given string s 를 활용하면 된다)

그래서 다음처럼 코드를 다듬을 수 있게되었다.

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int maxLength = 0;
        unordered_set<char> charSet;
        int left = 0;
        
        for (int right = 0; right < n; right++) {
            if (charSet.count(s[right]) == 0) {
                charSet.insert(s[right]);
                maxLength = max(maxLength, right - left + 1);
            } else {
                while (charSet.count(s[right])) {
                    charSet.erase(s[left]);
                    left++;
                }
                charSet.insert(s[right]);
            }
        }
        
        return maxLength;
    }
};
```

## Complexity

이 알고리즘의 complexity는 그닥 좋다고 할 수 없다.

우선 s[i]의 모든 문자를 iterrate하며 매번 `charSet` 안에 존재하는지 ($O(m\log m)$, m은 `charSet`의 사이즈)확인해야하는데, m은 언제나 이 문제의 답보다는 작으므로, 총 시간복잡도는 $O(answer *n\log n)$ 이라고 할 수 있겠다.

하지만, 애초에 매순간마다 $O(m\log m)$의 시간비용이 드는 operation을 한다는것 자체가 마음에 안들었다. 그래서 hashmap 을 활용한 알고리즘을 생각해보게되었다.

(공간복잡도는 $O(answer)$ 이 되겠다.)

## References

- https://leetcode.com/problems/longest-substring-without-repeating-characters/