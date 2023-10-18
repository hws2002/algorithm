# 14 Oct 2023 - 2742. Painting the Walls (Google)

[Painting the Walls - LeetCode](https://leetcode.com/problems/painting-the-walls/description/?envType=daily-question&envId=2023-10-14)

You are given two **0-indexed** integer arrays, `cost` and `time`, of size `n` representing the costs and the time taken to paint `n` different walls respectively. There are two painters available:

- A **paid painter** that paints the `i^th` wall in `time[i]` units of time and takes `cost[i]` units of money.
- A **free painter** that paints **any** wall in `1` unit of time at a cost of `0`. But the free painter can only be used if the paid painter is already **occupied**.

Return *the minimum amount of money required to paint the* `n` *walls.*

**Example 1:**

```
Input: cost = [1,2,3,2], time = [1,2,3,2]
Output: 3
Explanation: The walls at index 0 and 1 will be painted by the paid painter, and it will take 3 units of time; meanwhile, the free painter will paint the walls at index 2 and 3, free of cost in 2 units of time. Thus, the total cost is 1 + 2 = 3.

```

**Example 2:**

```
Input: cost = [2,3,4,2], time = [1,1,1,1]
Output: 4
Explanation: The walls at index 0 and 3 will be painted by the paid painter, and it will take 2 units of time; meanwhile, the free painter will paint the walls at index 1 and 2, free of cost in 2 units of time. Thus, the total cost is 2 + 2 = 4.

```

**Constraints:**

- `1 <= cost.length <= 500`
- `cost.length == time.length`
- `1 <= cost[i] <= 10^6`
- `1 <= time[i] <= 500`

---

## Intuition & Approach

보자마자 처음 생각난 것은 greedy 사상이다. 엄밀한 수학적 증명을 두지 않고, 그냥 내 감대로 다음처럼 우선순위를 정해보았다.

> free painter는 최대한 cost가 비싼 벽을 패인트칠하고, 만약 cost가 같다면, time이 더 낮은 벽을 우선으로 칠한다. paid painter는 cost/time 이 가장 작은 벽을 먼저 패인트칠한다. 만약 cost/time이 같다면, cost가 낮은것을 우선으로 칠한다.
> 

이를 토대로 다음과같이 알고리즘을 짤 수 있었다.

```cpp
class Solution {
public:
    int length;
    bool lastWallExists(){
        return false;
    }
    int paintWalls(vector<int>& cost, vector<int>& time) {
    // prepare cost/time vector
        length = cost.size();
        vector<double> cost_time(length);
        for(int i= 0; i< length ; i++){
            cost_time[i] = (double)cost[i] / (double)time[i];
        }
    // prepare index tables
        std::vector<size_t> freeindices(length);
        std::vector<size_t> paidindices(length);
        std::vector<bool> painted(length,false);
        std::iota(freeindices.begin(), freeindices.end(),0); // Fill with 0, 1, 2, ...
        std::iota(paidindices.begin(), paidindices.end(),0);

        // Sort the index vector based on the values in the cost and time vectors
        std::sort(freeindices.begin(), freeindices.end(),
            [&cost, &time](size_t i1, size_t i2) {
                if (cost[i1] != cost[i2]) return cost[i1] < cost[i2]; // primary: descending cost
                return time[i1] > time[i2]; // secondary: ascending time
            }
        );

        // Sort the index vector based on the values in the cost/time and cost vectors
        std::sort(paidindices.begin(), paidindices.end(),
            [&cost_time, &cost](size_t i1, size_t i2){
                if (cost_time[i1] != cost_time[i2]) return cost_time[i1] > cost_time[i2];
                return cost[i1] > cost[i2];
            }
        );

        int res = 0;
        int available_time = 0;
        int painted_walls = 0;
        while(painted_walls <= length){
        // check if there exists last wall
        // last wall : the wall that can end up painting.
            printf("Current painted walls : %d \n", painted_walls);
            if(lastWallExists()){
                painted_walls++;
                // res += lastwallcost;
                break;
            }
        // paid painter paint
            while(painted[paidindices.back()])
                paidindices.pop_back();

            if(!paidindices.empty()){
                // printf("index of currently painted wall : %d , cost of currently paintd wall : %d \n", paidindices.back(), cost[paidindices.back()]);
                res += cost[paidindices.back()];
                painted_walls++;
                available_time += time[paidindices.back()];
                painted[paidindices.back()] = true;
                paidindices.pop_back();
            }

            if(available_time + painted_walls >= length){
                break;
            }

        // free painter paint
            while(available_time){
                if(!painted[freeindices.back()]){
                    painted_walls++;
                    available_time--;
                    // printf("free painter gonna paint wall : %d, which is of cost %d, and of time %d \n",freeindices.back(),cost[freeindices.back()],time[freeindices.back()]);
                    painted[freeindices.back()] = true;
                } else {
                    // printf("the wall is already painted by paid painter \n");
                }
                freeindices.pop_back();    
            }
        }
        return res;
    }
};
```

패인트칠하는 과정을 $O(1)$시간 안에 해결하기 위해 미리 `index table`을 준비하여 해결하였다.

free painter는 매번 cost가 가장 비싼 벽을 패인트칠해야하기 때문에, cost를 기준으로 오른차순 배열,

paid painter는 매번 cost/time이 가장 작은 벽을 패인트칠해야하기 때문에, cost/time을 기준으로 내림차순 배열하였다.

여기서 free painter는 cost가 같을때, time이 더 낮은 벽을 뒤에 배치한다.

paid painter는 같은 값이 나올때 cost가 더 낮은것을 뒤에 배치한다. 

```cpp
    // prepare index tables
        std::vector<size_t> freeindices(length);
        std::vector<size_t> paidindices(length);
        std::vector<bool> painted(length,false);
        std::iota(freeindices.begin(), freeindices.end(),0); // Fill with 0, 1, 2, ...
        std::iota(paidindices.begin(), paidindices.end(),0);

        // Sort the index vector based on the values in the cost and time vectors
        std::sort(freeindices.begin(), freeindices.end(),
            [&cost, &time](size_t i1, size_t i2) {
                if (cost[i1] != cost[i2]) return cost[i1] < cost[i2]; // primary: descending cost
                return time[i1] > time[i2]; // secondary: ascending time
            }
        );

        // Sort the index vector based on the values in the cost/time and cost vectors
        std::sort(paidindices.begin(), paidindices.end(),
            [&cost_time, &cost](size_t i1, size_t i2){
                if (cost_time[i1] != cost_time[i2]) return cost_time[i1] > cost_time[i2];
                return cost[i1] > cost[i2];
            }
        );
```

![result1](14%20Oct%202023%20-%202742%20Painting%20the%20Walls%20(Google)%20d0381af2b40948548602e99f5421d452/Untitled.png)

result1

하지만, 다음과 같은 간단한 test case에도 옳은 답을 도출하지 못했다.

```
cost = [50,2]
time = [100,1]
```

```
cost= [49,35,32,20,30,12,42]
time = [1,1,2,2,1,1,2]

Output
64
Expected
62
```

옳은 답을 도출하지 못하는 이유는 남은 벽이 2개인 상황에서, (2,1) 을 paid painter가 색칠하고, (50,100)을 free painter가 색칠해서 모든 벽을 칠할 수 있지만, (50,100)의 cost/time값이 0.5로 2보다 작기 때문이다. 이러한 현상을 해결하기 위해서는 만약 아직 패인트칠하지않은 벽들중에서 time ≥ `앞으로 칠해야할 페인트의 숫자-1`인 벽이 있다면, 그 중 cost가 가장 작은 벽을 칠하도록 하는 규칙을 추가시키면 된다.

그렇게 `isLastWallExist` 함수를 brue_force로 추가해서 다시 코드를 적어봤다. 이젠 

```cpp
if(available_time + painted_walls >= length){
   break;
}
```

이 break조건이 필요없음을 알 수 있다.

```cpp
class Solution {
public:
    int length;
    int lastPaintingCost;
    bool islastWallExist(vector<bool>& painted,vector<int>& cost, vector<int>& time,int painted_walls){
        lastPaintingCost=INT_MAX;
        bool exist = false;
        for(int i = 0 ; i < length ; ++i){
            if(!painted[i]){
                if(time[i] + painted_walls >= length-1){
                    lastPaintingCost = min(cost[i],lastPaintingCost);
                    exist = true;
                }
            }   
        }
        return exist;
    }
    int paintWalls(vector<int>& cost, vector<int>& time) {
    // prepare cost/time vector
        length = cost.size();
        vector<double> cost_time(length);
        for(int i= 0; i< length ; i++){
            cost_time[i] = (double)cost[i] / (double)time[i];
        }
    // prepare index tables
        std::vector<size_t> freeindices(length);
        std::vector<size_t> paidindices(length);
        std::vector<bool> painted(length,false);
        std::iota(freeindices.begin(), freeindices.end(),0); // Fill with 0, 1, 2, ...
        std::iota(paidindices.begin(), paidindices.end(),0);

        // Sort the index vector based on the values in the cost and time vectors
        std::sort(freeindices.begin(), freeindices.end(),
            [&cost, &time](size_t i1, size_t i2) {
                if (cost[i1] != cost[i2]) return cost[i1] < cost[i2]; // primary: descending cost
                return time[i1] > time[i2]; // secondary: ascending time
            }
        );

        // Sort the index vector based on the values in the cost/time and cost vectors
        std::sort(paidindices.begin(), paidindices.end(),
            [&cost_time, &cost](size_t i1, size_t i2){
                if (cost_time[i1] != cost_time[i2]) return cost_time[i1] > cost_time[i2];
                return cost[i1] > cost[i2];
            }
        );

        int res = 0;
        int available_time = 0;
        int painted_walls = 0;
        while(painted_walls <= length){
        // check if there exists last wall
        // last wall : the wall that can end up painting.
            printf("Current painted walls : %d \n", painted_walls);
            if(islastWallExist(painted,cost,time, painted_walls)){
                res += lastPaintingCost;
                break;
            }
        // paid painter paint
            while(painted[paidindices.back()])
                paidindices.pop_back();

            if(!paidindices.empty()){
                res += cost[paidindices.back()];
                painted_walls++;
                available_time += time[paidindices.back()];
                painted[paidindices.back()] = true;
                paidindices.pop_back();
            }

        // free painter paint
            while(available_time){
                if(!painted[freeindices.back()]){
                    painted_walls++;
                    available_time--;
                    painted[freeindices.back()] = true;
                }
                freeindices.pop_back();    
            }
        }
        return res;
    }
};
```

![result2](14%20Oct%202023%20-%202742%20Painting%20the%20Walls%20(Google)%20d0381af2b40948548602e99f5421d452/Untitled%201.png)

result2

그러나 이번에도 틀린 케이스들이 존재해서, 그 케이스를 분석해보기로 했다.

![Untitled](14%20Oct%202023%20-%202742%20Painting%20the%20Walls%20(Google)%20d0381af2b40948548602e99f5421d452/Untitled%202.png)

```
Current painted walls : 0 
index of currently painted wall : 8 , cost of currently paintd wall : 2 
free painter gonna paint wall : 2, which is of cost 96, and of time 1 
free painter gonna paint wall : 7, which is of cost 88, and of time 3 
Current painted walls : 3 
index of currently painted wall : 9 , cost of currently paintd wall : 5 
free painter gonna paint wall : 4, which is of cost 85, and of time 1 
Current painted walls : 5 
index of currently painted wall : 5 , cost of currently paintd wall : 19 
free painter gonna paint wall : 0, which is of cost 76, and of time 1 
free painter gonna paint wall : 3, which is of cost 46, and of time 3 
free painter gonna paint wall : 6, which is of cost 29, and of time 3 
Current painted walls : 9
```

애초에 (25,2),(19,3),(2,1)으로 비용46만에 해결할 수 있지만, 내 greedy알고리즘으로는 (2,2),(5,1), (19,3), (25,2)으로 51의 비용이 필요하다.

여기서 애초에 알고리즘 자체를 뒤엎어야 하나 생각했는데, 생각해보니 그냥 잉여 painting을 줄이면 되지않을까란 생각이 들었다.

```cpp
class Solution {
public:
    int length;
    int lastPaintingCost;
    int lastPaintingTime;
    vector< pair<int,int> > resPainting;
    bool islastWallExist(vector<bool>& painted,vector<int>& cost, vector<int>& time,int painted_walls){
        lastPaintingCost=INT_MAX;
        bool exist = false;
        for(int i = 0 ; i < length ; ++i){
            if(!painted[i]){
                if(time[i] + painted_walls >= length-1){
                    if(cost[i] < lastPaintingCost){
                        lastPaintingCost = cost[i];
                        lastPaintingTime = time[i];
                    }
                    exist = true;
                }
            }   
        }
        return exist;
    }
    int paintWalls(vector<int>& cost, vector<int>& time) {
    // prepare cost/time vector
        length = cost.size();
        vector<double> cost_time(length);
        for(int i= 0; i< length ; i++){
            cost_time[i] = (double)cost[i] / (double)time[i];
        }
    // prepare index tables
        std::vector<size_t> freeindices(length);
        std::vector<size_t> paidindices(length);
        std::vector<bool> painted(length,false);
        std::iota(freeindices.begin(), freeindices.end(),0); // Fill with 0, 1, 2, ...
        std::iota(paidindices.begin(), paidindices.end(),0);

        // Sort the index vector based on the values in the cost and time vectors
        std::sort(freeindices.begin(), freeindices.end(),
            [&cost, &time](size_t i1, size_t i2) {
                if (cost[i1] != cost[i2]) return cost[i1] < cost[i2]; // primary: descending cost
                return time[i1] > time[i2]; // secondary: ascending time
            }
        );

        // Sort the index vector based on the values in the cost/time and cost vectors
        std::sort(paidindices.begin(), paidindices.end(),
            [&cost_time, &cost](size_t i1, size_t i2){
                if (cost_time[i1] != cost_time[i2]) return cost_time[i1] > cost_time[i2];
                return cost[i1] > cost[i2];
            }
        );

        int res = 0;
        int available_time = 0;
        int painted_walls = 0;
        while(painted_walls <= length){
        // check if there exists last wall
        // last wall : the wall that can end up painting.
            printf("Current painted walls : %d \n", painted_walls);
            if(islastWallExist(painted,cost,time, painted_walls)){
                res += lastPaintingCost;
                resPainting.push_back(make_pair(lastPaintingCost,lastPaintingTime));
                painted_walls = painted_walls + lastPaintingTime +1;
                printf("painting ended with lastwall! \n");
                break;
            }
        // paid painter paint
            while(painted[paidindices.back()])
                paidindices.pop_back();

            if(!paidindices.empty()){
                printf("index of currently painted wall : %d , cost of currently paintd wall : %d \n", paidindices.back(), cost[paidindices.back()]);
                res += cost[paidindices.back()];
                painted_walls++;
                available_time += time[paidindices.back()];
                painted[paidindices.back()] = true;
                resPainting.push_back(make_pair(cost[paidindices.back()],time[paidindices.back()]));
                paidindices.pop_back();
            }

            if(available_time + painted_walls >= length){
                break;
            }

        // free painter paint
            while(available_time){
                if(!painted[freeindices.back()]){
                    painted_walls++;
                    available_time--;
                    printf("free painter gonna paint wall : %d, which is of cost %d, and of time %d \n",freeindices.back(),cost[freeindices.back()],time[freeindices.back()]);
                    painted[freeindices.back()] = true;
                } else {
                    printf("the wall is already painted by paid painter \n");
                }
                freeindices.pop_back();
            }
        }
        printf("painted_walls : %d \n", painted_walls);
        for(vector<pair<int,int>>::iterator it = resPainting.begin(); it != resPainting.end(); ++it){
            printf("cost : %d, time : %d \n",it->first,it->second);
            if(painted_walls - 1 - it->second >= length)
                res -= it->first;
        }
        return res;
    }
};
```

![Untitled](14%20Oct%202023%20-%202742%20Painting%20the%20Walls%20(Google)%20d0381af2b40948548602e99f5421d452/Untitled%203.png)

30개의 test case를 추가로 통과했지만, 여전히 문제가 되는 케이스가 있었다.

```
cost = [45,32,61,61,61,23,47,34]
time = [1,1,1,1,2,1,1,2]
```

```
Current painted walls : 0 
index of currently painted wall : 7 , cost of currently paintd wall : 34 
free painter gonna paint wall : 3, which is of cost 61, and of time 1 
free painter gonna paint wall : 2, which is of cost 61, and of time 1 
Current painted walls : 3 
index of currently painted wall : 5 , cost of currently paintd wall : 23 
free painter gonna paint wall : 4, which is of cost 61, and of time 2 
Current painted walls : 5 
index of currently painted wall : 1 , cost of currently paintd wall : 32 
free painter gonna paint wall : 6, which is of cost 47, and of time 1 
Current painted walls : 7 
painting ended with lastwall! 
painted_walls : 9 
cost : 34, time : 2 
cost : 23, time : 1 
cost : 32, time : 1 
cost : 45, time : 1
```

두번째 케이스에서 (23,1)을 고르는것이 아니라, (61,2)를 골랐어야 했지만, cost/time 값이 더 작으므로 이러한 결과가 발생했다.

결국 알고리즘 자체를 갈아 엎어야 했다. 애초에 greedy 방식을 수학적으로 증명하지 않고 시도했기 때문에, 안될거라는건 어느정도 예상되었었다.

스스로 해결해보려 하였지만, 아무리 오래 고민해봐도 떠오르는 방법이 없어서 이미 있는 solution을 참고하였다.(Neetcode)

### Neetcode

[Painting the Walls - Leetcode 2742 - Python](https://www.youtube.com/watch?v=qMZJunF5UaI)

모든 벽들을 iterrate하면서, paid painter가 이벽을 칠하냐, 마냐로 접근하는 방식을 사용했다. 

![모든 벽들을 순회하며 paid painter가 칠하냐 마냐를 결정한다.](14%20Oct%202023%20-%202742%20Painting%20the%20Walls%20(Google)%20d0381af2b40948548602e99f5421d452/Untitled%204.png)

모든 벽들을 순회하며 paid painter가 칠하냐 마냐를 결정한다.

즉 모든 case들을 순회하기 때문에 정확한 답을 얻어낼 수 있다. 시간복잡도는 $O(n^2)$인데, 애초에 $O(n^2)$를 넘을 수 없을것 같다. 뭔가 애초에 $O(n^2)$를 넘을 수 없을것같다는 생각이 들었을때, 모든 case들을 순회하는 방식을 고려할수 있었을텐데, 너무 바보같았다는 생각이 든다.. ㅠㅠ

dp식은 다음과 같이 정의한다.

dp[index,remaining] : index위치의 벽부터 마지막 위치의 벽까지 색칠하는데 필요한 최소비용. 그중 remaining벽은 아직 색칠하지 않은 벽의 개수이다.

base는 다음과 같이 잡을수 있고,

> 1. dp[i,remaining] = 0 where `remaining` ≤ 0
2. dp[i,remaining] = INT_MAX where i ≥ n
3. dp[i,remaining] = 0 where i≥n && remaining ≤ 0
> 

첫번째 base조건은 더이상 색칠해야할 벽의 갯수가 0보다 적으므로, 비용또한 0 이되는것이고,
두번째 base조건은 i(i ≥ n)부터 n까지 색칠해야 하는 경우는 애초에 모든 벽을 색칠하지 못한 경우이므로, return INT_MAX로 제외시켜버려야 한다.(밑의 dp식을 보면 INT_MAX인 이유를 알 것이다)
세번째 base조건은 첫번째와 두번째 조건을 모두 만족하는 경우인데, 이럴때는 애초에 벽을 모두 색칠했기때문에, 똑같이 0을 리턴하면된다.

그러면 자세한 식은 다음처럼 될것이다.

> dp[i,remaining] = min(cost[i] + dp[i+1,remaining-1-time[i]],dp[i+1, remaining])
> 

그리고 우리가 구하고 싶은 값은 dp[0,n]이 될것이다. 그리고 연산과정에서 이미 구했던 dp값을 또 구하는 상황이 발생할수 있기때문에,`memoization` 을 쓰면 된다.

우선 memoization을 구현하지 않은 코드는 다음과 같고,

```cpp
class Solution {
public:

    vector<int> _cost;
    vector<int> _time;
    int threshold;

    long long dp(int index, int remaining){
        if(remaining <= 0 ) return 0;
        if(index >= threshold) return INT_MAX;
        return std::min(
            _cost[index] + dp(index+1, remaining-1-_time[index]),
            dp(index+1, remaining)
        );
    }

    int paintWalls(vector<int>& cost, vector<int>& time) {
        _cost = cost;
        _time = time;
        threshold = cost.size();
        int res = (int) dp(0,threshold);
        return res;
    }
};
```

memoization을 구현하면 다음처럼 코드를 수정할 수 있다.

```cpp
class Solution {
public:

    vector<int> _cost;
    vector<int> _time;
    int threshold;
    long long memoization[500][501] = {0};

    long long dp(int index, int remaining){
        if(remaining <= 0 ) return 0;
        if(index >= threshold) return INT_MAX;
        if(memoization[index][remaining]) return memoization[index][remaining];
        long long paint = _cost[index] + dp(index+1, remaining-1-_time[index]);
        long long skip = dp(index+1, remaining);
        memoization[index][remaining] = std::min(paint,skip);
        return memoization[index][remaining];
    }

    int paintWalls(vector<int>& cost, vector<int>& time) {
        _cost = cost;
        _time = time;
        threshold = cost.size();
        int res = (int) dp(0,threshold);
        return res;
    }
};
```

### Time Complexity & Space Complexity

시간 복잡도는 위에 서술했듯이 $O(n^2)$이고, 공간복잡도는 memoization때문에 $O(n^2)$이다.

그러나 최선의 상황에서 memoization에 의해 계산횟수를 줄여준다면, 얼마나 줄일 수 있는지 알아보고싶어졌다.

### Follow-up (TODO)

그래서 memoization이 계산 횟수를 얼마나 줄여줄 수 있는지 계산해보았다.

memoizatoin이 계산 횟수를 줄여주는 상황은 다음과 같다.

- [ ]  

그러므로 이건 주어진 상황에 따라 단한번도 계산 횟수를 못줄일수도 있고, 최대 ?번의 계산 횟수를 줄여줄 수도있다.

### Debugging Code

- Greedy
    
    ```cpp
    class Solution {
    public:
        int length;
        int lastPaintingCost;
        bool islastWallExist(vector<bool>& painted,vector<int>& cost, vector<int>& time,int painted_walls){
            lastPaintingCost=INT_MAX;
            bool exist = false;
            for(int i = 0 ; i < length ; ++i){
                if(!painted[i]){
                    if(time[i] + painted_walls >= length-1){
                        lastPaintingCost = min(cost[i],lastPaintingCost);
                        exist = true;
                    }
                }   
            }
            return exist;
        }
        int paintWalls(vector<int>& cost, vector<int>& time) {
        // prepare cost/time vector
            length = cost.size();
            vector<double> cost_time(length);
            for(int i= 0; i< length ; i++){
                cost_time[i] = (double)cost[i] / (double)time[i];
            }
        // prepare index tables
            std::vector<size_t> freeindices(length);
            std::vector<size_t> paidindices(length);
            std::vector<bool> painted(length,false);
            std::iota(freeindices.begin(), freeindices.end(),0); // Fill with 0, 1, 2, ...
            std::iota(paidindices.begin(), paidindices.end(),0);
    
            // Sort the index vector based on the values in the cost and time vectors
            std::sort(freeindices.begin(), freeindices.end(),
                [&cost, &time](size_t i1, size_t i2) {
                    if (cost[i1] != cost[i2]) return cost[i1] < cost[i2]; // primary: descending cost
                    return time[i1] > time[i2]; // secondary: ascending time
                }
            );
    
            // Sort the index vector based on the values in the cost/time and cost vectors
            std::sort(paidindices.begin(), paidindices.end(),
                [&cost_time, &cost](size_t i1, size_t i2){
                    if (cost_time[i1] != cost_time[i2]) return cost_time[i1] > cost_time[i2];
                    return cost[i1] > cost[i2];
                }
            );
    
            int res = 0;
            int available_time = 0;
            int painted_walls = 0;
            while(painted_walls <= length){
            // check if there exists last wall
            // last wall : the wall that can end up painting.
                printf("Current painted walls : %d \n", painted_walls);
                if(islastWallExist(painted,cost,time, painted_walls)){
                    res += lastPaintingCost;
                    break;
                }
            // paid painter paint
                while(painted[paidindices.back()])
                    paidindices.pop_back();
    
                if(!paidindices.empty()){
                    printf("index of currently painted wall : %d , cost of currently paintd wall : %d \n", paidindices.back(), cost[paidindices.back()]);
                    res += cost[paidindices.back()];
                    painted_walls++;
                    available_time += time[paidindices.back()];
                    painted[paidindices.back()] = true;
                    paidindices.pop_back();
                }
    
                // if(available_time + painted_walls >= length){
                //     break;
                // }
    
            // free painter paint
                while(available_time){
                    if(!painted[freeindices.back()]){
                        painted_walls++;
                        available_time--;
                        printf("free painter gonna paint wall : %d, which is of cost %d, and of time %d \n",freeindices.back(),cost[freeindices.back()],time[freeindices.back()]);
                        painted[freeindices.back()] = true;
                    } else {
                        printf("the wall is already painted by paid painter \n");
                    }
                    freeindices.pop_back();    
                }
            }
            return res;
        }
    };
    ```
## Notion Link
[14 Oct 2023  - 2742. Painting the Walls (Google)](https://mixed-hurricane-243.notion.site/14-Oct-2023-2742-Painting-the-Walls-Google-d0381af2b40948548602e99f5421d452?pvs=4)