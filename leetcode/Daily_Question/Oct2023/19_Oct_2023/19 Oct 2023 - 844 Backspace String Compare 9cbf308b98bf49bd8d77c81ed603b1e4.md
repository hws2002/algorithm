# 19 Oct 2023 - 844. Backspace String Compare

[Backspace String Compare - LeetCode](https://leetcode.com/problems/backspace-string-compare/description/?envType=daily-question&envId=2023-10-19)

Given two strings `s` and `t`, return `true` *if they are equal when both are typed into empty text editors*. `'#'` means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

**Example 1:**

```
Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".

```

**Example 2:**

```
Input: s = "ab##", t = "c#d#"
Output: true
Explanation: Both s and t become "".

```

**Example 3:**

```
Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".

```

**Constraints:**

- `1 <= s.length, t.length <= 200`
- `s` and `t` only contain lowercase letters and `'#'` characters.

---

## Intuition & Approach

이전에 Stack 의 활용에 대해 배울때 中缀表达式(infix expression)에 대해 배웠었는데,

이때의 예제로서 풀었던 polynomial 연산을 하는 문제의 간단화된 버전이라고 생각하면 되었다.

stack을 각각 준비해서, `#`이 나올때마다 pop을 해주고, 마지막에 비교하면 되었다.

문제의 특성상, vector로 구현하여도 전혀 문제 없었다.(오히려 debugging에 있어서 더 효율적임)

```cpp
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<char> left;
        stack<char> right;
        int s_length = s.length();
        int t_length = t.length();
        if( s_length > t_length){
            for(int i=0; i<t_length; i++){
                if(s[i] == '#') {
                    if(!left.empty()) left.pop();
                } else{
                    left.push(s[i]);
                }
                if(t[i] == '#'){
                    if(!right.empty()) right.pop();
                } else {
                    right.push(t[i]);
                }
            }
            for(int i = t_length; i < s_length; i++){
                if(s[i] == '#') {
                    if(!left.empty()) left.pop();
                } else{
                    left.push(s[i]);
                }
            }
        } else{
            for(int i=0; i < s_length; i++){
                if(s[i] == '#') {
                    if(!left.empty()) left.pop();
                } else{
                    left.push(s[i]);
                }
                if(t[i] == '#'){
                    if(!right.empty()) right.pop();
                } else {
                    right.push(t[i]);
                }
            }
            for(int i = s_length; i < t_length; i++){
                if(t[i] == '#'){
                    if(!right.empty()) right.pop();
                } else {
                    right.push(t[i]);
                }
            }
        }
        int left_size = left.size();
        int right_size = right.size();
        
        if(left_size != right_size) return false;
        while(!left.empty() && !right.empty()){
            if(left.top() != right.top()) return false;
            left.pop(); right.pop();
        }
        return true;
    }
};
```

![result1 - accepted!](19%20Oct%202023%20-%20844%20Backspace%20String%20Compare%209cbf308b98bf49bd8d77c81ed603b1e4/Untitled.png)

result1 - accepted!

## **Follow up:** Can you solve it in `O(n)` time and `O(1)` space?

`O(1)` space 안에 해결하는 방법이 뭐가 있을까 고민하다가, 거꾸로 scan하는 방법이 떠올랐다.

이 방법의 insight는 다음과같다

> s와 t를 각각 “마지막#” 전후로 나누자. 즉, s = “[left1]#[right1]”, t =“[left2]#[right2]”라고 하면, `backspaceCompare == true` ⇒ `[righ1]==[right2]` 이다.
> 

즉, 우리는 [right1] == [right2] 를 판단한다음, 나머지 [left1]# 와 [left2]#를 비교하기 시작하면 된다.

그렇게 새로운 코드는

```cpp
class Solution {
public:
    char getLastChar(const string & s, int & i, int & jump){ 
        if(i<0) return '-';
        if(s[i] == '#') {
            jump++; i--;
        } else{
            if(jump >= 1){
                jump--;i--;
            } else {
                return s[i];
            }
        }
        return getLastChar(s,i,jump);
    }

    bool backspaceCompare(string s, string t) {
        char s_last;
        char t_last;
        int i = s.length()-1; int j = t.length()-1;
        while(i > -1 || j > -1){
            int s_jump = 0;
            int t_jump = 0;
            s_last = getLastChar(s,i,s_jump);
            t_last = getLastChar(t,j,t_jump);
            //printf("s_last : %c , t_last : %c \n",s_last,t_last);
            i--;j--;
            if(s_last != t_last) return false;
        }
        return true;
    }
};
```

![[https://leetcode.com/problems/backspace-string-compare/submissions/1078979326/?envType=daily-question&envId=2023-10-19](https://leetcode.com/problems/backspace-string-compare/submissions/1078979326/?envType=daily-question&envId=2023-10-19)](19%20Oct%202023%20-%20844%20Backspace%20String%20Compare%209cbf308b98bf49bd8d77c81ed603b1e4/Untitled%201.png)

[https://leetcode.com/problems/backspace-string-compare/submissions/1078979326/?envType=daily-question&envId=2023-10-19](https://leetcode.com/problems/backspace-string-compare/submissions/1078979326/?envType=daily-question&envId=2023-10-19)

비록 통계상으로는 비슷하지만, 이론상으로는 시간복잡도 $O(n)$,공간복잡도$O(1)$를 만족시켰다. 

아마 test case들의 n이 무지막지하게 크진 않아서, 통계상으로 비슷한 결과가 나오는것 같다.

## Reference

[2-4 中缀表达式](https://www.notion.so/2-4-e167f6d6674a4954aad5fca53a1ed85d?pvs=21)