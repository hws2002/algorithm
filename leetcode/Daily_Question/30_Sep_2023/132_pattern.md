# 456. 132 pattern
[LeetCode - 456. 132 pattern](https://leetcode.com/problems/merge-sorted-array/description/?envType=study-plan-v2&envId=top-interview-150)
## Intuition

맨처음에 딱 보고 든 생각은…

**栈混洗..!**

> A permutation is a **stack permutation** iff it does NOT involve the permutation 312.(or 132 depend on the direction)
> 

132 패턴을 찾으려면, 주어진 배열의 길이가 n일때, 수열 <n,n-1,…,1]이 주어진 배열로 stack permutation 이 가능한지 알아보면된다.

### 알고리즘
다음과 같은 알고리즘으로 $O(n)$시간 안에 해결할 수 있다.

![S 는 보조 스택이다.](https://prod-files-secure.s3.us-west-2.amazonaws.com/50241e0d-1b54-4b6f-b668-fab4b01de234/ccf3412b-e273-4147-b3d8-3af9fac3679d/Untitled.png)

`pseudo code` 는 다음과 같다 

```cpp
// B = nums (given array)
// n == B.length().
// A = <n,n-1,n-2,...,2,1]
// S is a supplementary stack
for i in range(B.size()): {
	check if S.top() == B[i]. 
			yes -> {
						B.push(S.pop())
						i++
			}
			no -> {
						S.push(A.pop()) till we meet B[i] or A is empty.
						check if S.top() == B[i] :{
								yes -> B.push(S.pop()) 
								no -> return true (break) //this situation includes when S is empty
								i++
						}
			}
}
return false;
```

- [3,1,4,2] 예시 (true 예시, 132 포함)
    
    Stack A : <4,3,2,1] 에서 Stack B : [3,1,4,2> 로 permute 하려면,
    1-1. [S.top](http://S.top) 이 empty 이므로 no
    1-2. S.push(A.pop()) till we meet 3 → S = <3,4], A = <2,1]
    1-3. check if S.top() == 3:
        yes → B.push(S.pop()). S = <4], B = [3>
        i++
    
    2-1. [S.top](http://S.top) 이 empty 이므로 no
    2-2. S.push(A.pop()) till we meet 1 → S = <1,2,4], A = <]
    2-3. check if S.top == 1:
        yes → B.push(S.pop()). S = <2,4], B = [3,1>
        i++
    
    3-1. [S.top](http://S.top) 이 2이므로 no (≠4)
    3-2. A가 empty 이므로 do nothing
    3-3. check if S.top() == 4:
        no → return true.
    

## Approach

하지만 우린 위와같은 알고리즘을 바로 활용할 수 없는데,
주어진 배열이 1…n을 마구잡이로 섞은 배열이 아닌, `임의의 배열`이기 때문이다.(이때까지만 해도심지어 중복되는 원소들이 있다는 걸 몰랐다…) 예를 들어,

```bash
[-1,3,2,0] // Expected: true, gives true, but not in a reasonable way
[100,200,300,400] // Expected: false, but gives true 
```

이러한 경우가 있다.
이러한 상황에서는 우리가 가정한 `A`로 문제를 해결할 수 없음이 자명하다. (1…n을 마구잡이로 섞은 배열이 아닌 배열에게는 언제나 true 를 리턴한다.)

그렇다면 어떻게 해야할까?

이 문제를 해결할 수 있는 가장 쉬운 방법은, 주어진 array `B`를 array [1,2,3…,n> 로 맵핑하는 것이다. 다시말해, B의 각 원소를 크기순대로 나열했을때의 index를 부여해주면 된다.

기존 배열 : [-1,3,2,0]
mapping 후 : [1,4,3,2]

그후에는 B[i] 가 아닌 mapped[i] 를 비교 대상으로 삼으면 된다.

자 그럼, 맵핑은 어떻게 할까?  
가장먼저 생각난 방법은 Tree의 traverse이다. 

1. 주어진 배열 `B`를 가지고 leftNode Children들은 언제나 자신보다 작고, rightNode Children들은 언제나 자신보다 큰 Tree를 만든다.
2. pre-order traverse를 통해 각각의 값들의 index를 구한다.(조회하는 순서가 그 원소의 index가 된다)

헌데, 1번에서 Tree를 만드는 과정에서, 가장 단순한 방식으로 Tree를 구성하면, 너무 비효율적이니까, self-balanced BST를 만드는게…

라는 생각을 하던도중,그냥 이 방법으로 할수 있다는걸 알았다.

```cpp
// prepare a mapped 
      vector< pair<int,int> > pairs;

      for( int i=0; i< nums.size(); i++){
        pairs.push_back({nums[i],i});
      }
      
      stable_sort(pairs.begin(), pairs.end());

      //
      vector<int> order(nums.size());
      for(int i=0; i< pairs.size(); i++){
        order[pairs[i].second] = i+1;
      }
```

그래서 정말 기쁘게 다음처럼 코드를 적었는데…,

```cpp
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
      int n = nums.size();
      stack<int> S; // supplementary stack
      stack<int> A; 
      // stack B = nums

      // prepare a mapped 
      vector< pair<int,int> > pairs;

      for( int i=0; i< nums.size(); i++){
        pairs.push_back({nums[i],i});
      }
      
      stable_sort(pairs.begin(), pairs.end());

      //
      vector<int> order(nums.size());
      for(int i=0; i< pairs.size(); i++){
        order[pairs[i].second] = i+1;
      }

      // push elements from 1 to n onto the stack
      for (int i = 1 ; i<=n ; i++){
        A.push(i);
      }

      for(int i=0; i< order.size();){
        if (!S.empty() && S.top() == order[i]){ //yes
          S.pop();
          i++;
        } else { //no
          while(!A.empty() && A.top()!= order[i]){
            int element = A.top();
            A.pop();
            S.push(element);
          }
          if(!A.empty()){ // demonstrates that A.top() == nums[i]
            A.pop();
            S.push(order[i]);
          }

          // check if S.top() == x[i]
          if(S.top() == order[i]){ //yes
            S.pop();
          } else{ //no
            return true; // end. there is 132 patter (can't permute)
          }
          i++;
        }
      }
      return false; // there is no 132 pattern (can permute)
    };
};
```

duplicated elements 가 존재했다… (~~왜 처음부터 말안하는데~~)

이러면 애초에 걍 이 방법은 쓸수가 없다.. 다른 approach를 구해야한다.

결국 이미 존재하는 solution을 참고했다..

[갓닛코드](https://www.youtube.com/watch?v=q5ANAl8Z458)

이 방법의 intuition 은 Monotonic stack 과 minLeft 이다. 
그중 monotonic stack은 descending order을 가진 monotonic stack으로서, `nums[i]`, `nums[k]`, `nums[j]` 에 있어서 이미 `nums[j]` 의 역할은 할 수 없는, `nums[k]` 의 후보군을 저장하는 stack이며, minLeft[i] 는 0부터 i까지의 원소중 가장 작은 값을 나타내는 배열로서, `nums[i]`의 후보군을 저장한다.(편의상 밑에서부터는 132 패턴에서 ‘3의 역할’을 ,혹은 ‘2의 역할’ 이란 표현을 쓰겠다)

자세한 원리는 다음과 같다. 

`nums` 를 scan 하며 원소를 순차적으로 decreasing monotonic stack `mono_s`에 push 하는데,만약 현재 mono_s.top() 보다 push할 원소의 값이 더 크거나 같은 값이라면, `mono_s`의 top이 지금 push하려는 값보다 더 커질때까지 pop한다. 
그리고 나서, 현재위치에서의 `minLeft`와(`minLeft[i-1]`) push하려 했던 값을 비교하여, 만약 `minLeft`가 더 작다면 132 패턴이 존재한다는 뜻이므로 `return true`, 그렇지 않다면, push하고 `minLeft[i]` 또한 update한다. 그후 다음 원소로 넘어간다.

이 알고리즘의 정확성은 다음과 같은 사실을 기반으로 증명할 수 있다.

> `5,10,15,(...)` 이 15 를 3으로하는 132 패턴을 가지고있다면, `5,15,(...)` 또한 15를 3으로 하는 132 패턴을 가지고 있다.(10이 사라져도, 5가 1의 역할을 할 수 있기때문)
> 

이 사실은 monotonic stack을 유지할때, “push할 원소의 값이 더 크거나 같은 값일때, mono_s의 top이 지금 push하려는 값보다 더 커질때까지 pop”이라는 행위의 근거가 된다.
push할 원소의 값이 더 크다면, 현재 비교하고 있는 mono stack안의 원소와 push할 원소의 minLeft는 같으므로, 현재 push할 원소보다 작은 수들은 num[k]의 후보군에서 제외하여도 된다.

하지만 만약 push하려는 값이 더작다면, 이 값이 132 패턴에서 2의 역할을 담당하게되고,(`nums[j]`) 금방 비교한 mono_s 안의 값이 3의 역할을 담당하게 되므로, 그저 이 3과 2를 132 패턴으로 완성시켜줄 1이 존재여부만 판단하면된다. 그 과정에서 `minLeft`가 쓰이는것.

이로서 상기 알고리즘의 정확성은 증명되었다. 그렇다면 엄밀성또한 증명할 수 있는가?

~~ㅈㄴ 쉽다.~~ 우리는 `nums` 의 **모든** 원소를 scan하며 push하려는 원소가 2의 역할로서 132패턴을 완성시키는지 검증하고있기 때문에, 알고리즘의 엄밀성또한 증명되었다고 볼 수 있다. (132패턴이 존재한다면, 무조건 찾아 낼 수 있을것)

<aside>
🤔 **누군가는 push시에 132의 존재여부를 판단한 후에, 패턴이 존재하지 않음에도 왜 굳이 push하냐고 물어볼 수 있다. (그럼 정말 완벽하게 이해하신거다!)**
이미 mono stack안에 값이 더 큰 원소가 존재하고, push할 값이 2로서의 132 패턴이 존재하지 않는다면, 3으로서의 후보군에서 제외해도 상관없지 않냐는 이유로 위의 주장은 충분히 합리적이다.

> `(...),10,4,(...)` 이 4를 2로하는 132 패턴을 가지고 있지 않다면, 3으로 하는 132패턴은 10이 있기때문에 4가 없어져도 132패턴을 가질 수 있으므로, 결국 4는 1의 역할을 담당하는 상황만 고려하면 된다.
> 

이건 내가 충분한 설명을 하지 못해서인데, 밑의 구현을 보면 알겠지만, 난 깔끔한 코드구현을 위해서 num[k]의 후보군들과 minLeft를 pair로서 mono stack에 관리했다. minLeft값은 의미가 있기때문에 push해놓은것.
엄밀히 말하면, “해당 위치에서의 minLeft를 기록해라” 라고 말하는편이 더 맞긴하다.

</aside>

결국 위의 의사코드를 기반으로 다음과같이 구현할 수 있겠다.
```cpp
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        stack< pair<int,int> > mono_s;
        mono_s.push({nums[0],nums[0]});

        for(int i = 1 ; i < nums.size(); i++){
            int to_compare = mono_s.top().first;
            int leftMin = mono_s.top().second;
            while(!mono_s.empty() && mono_s.top().first <= nums[i]){
                mono_s.pop();
            }
            if(!mono_s.empty() && mono_s.top().second < nums[i]) return true;
            mono_s.push({nums[i], min(leftMin,nums[i])});
        }
        return false;
    }
};
```