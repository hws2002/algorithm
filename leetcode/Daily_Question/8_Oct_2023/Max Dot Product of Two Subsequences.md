# 8 Oct 2023 - 1458. Max Dot Product of Two Subsequences

[LeetCode - The World's Leading Online Programming Learning Platform](https://leetcode.com/problems/max-dot-product-of-two-subsequences/description/?envType=daily-question&envId=2023-10-08)

Given two arrays `nums1` and `nums2`.

Return the maximum dot product between **non-empty** subsequences of nums1 and nums2 with the same length.

A subsequence of a array is a new array which is formed from the original array by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, `[2,3,5]` is a subsequence of `[1,2,3,4,5]` while `[1,5,3]` is not).

**Example 1:**

```
Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
Output: 18
Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
Their dot product is (2*3 + (-2)*(-6)) = 18.
```

**Example 2:**

```
Input: nums1 = [3,-2], nums2 = [2,-6,7]
Output: 21
Explanation: Take subsequence [3] from nums1 and subsequence [7] from nums2.
Their dot product is (3*7) = 21.
```

**Example 3:**

```
Input: nums1 = [-1,-1], nums2 = [1,1]
Output: -1
Explanation:Take subsequence [-1] from nums1 and subsequence [1] from nums2.
Their dot product is -1.
```

**Constraints:**

- `1 <= nums1.length, nums2.length <= 500`
- `1000 <= nums1[i], nums2[i] <= 1000`

---

## Intuition & Approach

문제 자체는 굉장히 간단하지만, 푸는 방법은 그렇지 않아보였다.

하지만 [painting the walls](https://www.notion.so/14-Oct-2023-2742-Painting-the-Walls-d0381af2b40948548602e99f5421d452?pvs=21) 문제에서 접근했던 방식과 비슷하게 dynamic programming으로 해결할 수 있었다.

다음과같이 dp식의 의미를 정의한다

> dp[i,j] := nums1는 i번째 인덱스부터, nums2는 j번째 인덱스부터 유효하다고 할때, 이둘의 Max Dot Product 이다.
> 

그러면 dp식의 점화식은

> if(nums1[i] * nums2[j] > 0) dp[i,j] = max(nums1[i]*nums2[i] + dp[i+1,j+1],dp[i,j+1],dp[i+1,j])
else : dp[i,j] = max(dp[i+1,j+1],dp[i,j+1],dp[i+1,j]
> 

이 될것이고, base case는 다음과 같을 것이다.

> dp[i,j] = INT_MIN where i≥ nums1.length or j≥ nums2.length
> 

식을 세운후에, 코드로 짜는건 굉장히 쉬울것이라 예상했었다. 그러나 막상 코드를 적기 시작하니 은근히 고려해야할 상황들이 많았다. 또한, 내가 처음 세운 점화식을 약간 수정해야함을 깨달았다.

우선 점화식에 있는 오류부터 설명하자면, 직접적인 원인은 배열이 음수도 포함하기때문이였다.

다음과같은 test case를 보자

```
nums1 = [-1,-1]
nums2 = [1,1]
```

위의 점화식을 써서 풀면, `-1*1=-1`으로 음수이기 때문에, 

`dp[0,0] = max(dp[1,1], dp[0,1], dp[1,0])` 이 된다. 자세한 설명을 생략하고 바로 각각의 값들을 구해보면,

`dp[1,1]`, `dp[0,1]`, `dp[1,0]`모두 `INT_MIN`을 반환해서, 결국에 `INT_MIN`이라는 잘못된 답을 얻게 된다.

즉, `nums1[i]*nums2[j]`가 음수일때, 무시하는사상자체는 좋지만, 애초에 정해진 답자체가 음수인 경우에도 옳은 답을 유도하기 위해서는, `nums1[i]*nums2[j]`값을 버리지 않고 가지고있다가 답이 0보다 크다는것이 확정된 순간에는 버리고, 0보다 작을때는 버리지 않고 그 값을 활용해야 했다. 

또한 base case또한 틀렸었는데, 처음에는 `i`나 `j`가 `length`를 넘어가게 되서 존재하지 않는 상황을 배재시키려고 INT_MIN을 반환하려 했던 것이지만, 그렇게 하면 실제 값이 변동되게 되어, (예를 들어 `nums1[i]*nums2[i] + dp[i+1,j+1]`가 최대값인데, `dp[i+1,j+1]`이 `INT_MIN`을 반환하는경우) 올바른 답을 얻지 못하게 된다. 

그렇게 dp식을 수정하여 코드를 짜보았다. (수정한 dp식은 ~~귀찮아서~~ 생략한다. 코드를 보시면 된다…)

문제의 constraints를 활용하여 base case에 -1000001을 리턴하고, `end{2,3}` flag를 사용하여 각 상황에 따른 최대값을 고르도록 하였고, `isAnswerNegative` 라는 flag를 세워, 답이 음수인 경우에도 옳은 답을 얻을 수 있도록 하였다.

- `1000 <= nums1[i], nums2[i] <= 1000`
- Code1
    
    ```cpp
    class Solution {
    public:
    
        int memoization[501][501];
        // bool calculated[501][501] = {false};
        vector<int> _nums1;
        vector<int> _nums2;
        int length1;
        int length2;
        bool isAnswerNegative = true;
        int MaxNegativeAnswer = INT_MIN;
        int dp(int i, int j){
            printf("start caluclate dp[%d][%d] \n",i,j);
            if(i>=length1 || j >= length2) {
                printf("index out of range \n");
                return -1000001;
            }
            if(memoization[i][j] != INT_MIN) {
                printf("already calculated! memozation[%d][%d] = %d \n", i,j,memoization[i][j]);
                return memoization[i][j];
            }
            if(isAnswerNegative && _nums1[i] * _nums2[j] >= 0) isAnswerNegative = false;
            else MaxNegativeAnswer = max(_nums1[i] * _nums2[j], MaxNegativeAnswer);
            int choice1 = dp(i+1,j+1) == -1000001 ? (_nums1[i]*_nums2[j]) : (max(0,(_nums1[i]*_nums2[j])) + dp(i+1,j+1));
            int choice2 = dp(i,j+1);
            int choice3 = dp(i+1,j);
            bool end2 = choice2 == -1000001 ? true : false;
            bool end3 = choice3 == -1000001 ? true: false;
            printf("choice1, choice2, choice3 = %d, %d ,%d \n",choice1,choice2,choice3);
            if(!end2&&!end3) memoization[i][j] = max({choice1,choice2,choice3});
            else if(!end2&&end3) memoization[i][j] = max(choice1, choice2);
            else if(end2&&!end3) memoization[i][j] = max(choice1, choice3);
            else memoization[i][j] = choice1; // (end2&&end3)
            // calculated[i][j] = true;
            printf("i : %d, j : %d, memoization[i][j] = %d \n",i,j,memoization[i][j]);
            return memoization[i][j];
        }
        int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
            length1 = nums1.size(); length2 = nums2.size();
            for (int i = 0; i < 501; ++i) {
                for (int j = 0; j < 501; ++j) {
                    memoization[i][j] = INT_MIN;
                }
            }
            _nums1 = nums1;
            _nums2 = nums2;
            int i = 0; int j = 0;
            int res = dp(i,j);
            if(isAnswerNegative) return MaxNegativeAnswer;
            else return res;
        }
    };
    ```
    

하지만 아래와 같은 test case를 고려하지못했다.

![result1 - test case44 fail](8%20Oct%202023%20-%201458%20Max%20Dot%20Product%20of%20Two%20Subsequen%202bb49fd7c49c4e6d8b1eef204b418830/Untitled.png)

result1 - test case44 fail

- log
    
    ```
    start caluclate dp[0][0] 
    start caluclate dp[1][1] 
    start caluclate dp[2][2] 
    start caluclate dp[3][3] 
    start caluclate dp[4][4] 
    start caluclate dp[5][5] 
    index out of range 
    start caluclate dp[4][5] 
    start caluclate dp[5][6] 
    index out of range 
    start caluclate dp[4][6] 
    start caluclate dp[5][7] 
    index out of range 
    start caluclate dp[4][7] 
    start caluclate dp[5][8] 
    index out of range 
    start caluclate dp[4][8] 
    start caluclate dp[5][9] 
    index out of range 
    start caluclate dp[4][9] 
    start caluclate dp[5][10] 
    index out of range 
    start caluclate dp[4][10] 
    index out of range 
    start caluclate dp[5][9] 
    index out of range 
    choice1, choice2, choice3 = -16, -1000001 ,-1000001 
    i : 4, j : 9, memoization[i][j] = -16 
    start caluclate dp[5][8] 
    index out of range 
    choice1, choice2, choice3 = -36, -16 ,-1000001 
    i : 4, j : 8, memoization[i][j] = -16 
    start caluclate dp[5][7] 
    index out of range 
    choice1, choice2, choice3 = -40, -16 ,-1000001 
    i : 4, j : 7, memoization[i][j] = -16 
    start caluclate dp[5][6] 
    index out of range 
    choice1, choice2, choice3 = -20, -16 ,-1000001 
    i : 4, j : 6, memoization[i][j] = -16 
    start caluclate dp[5][5] 
    index out of range 
    choice1, choice2, choice3 = 16, -16 ,-1000001 
    i : 4, j : 5, memoization[i][j] = 16 
    start caluclate dp[5][4] 
    index out of range 
    choice1, choice2, choice3 = 8, 16 ,-1000001 
    i : 4, j : 4, memoization[i][j] = 16 
    start caluclate dp[4][4] 
    already calculated! memozation[4][4] = 16 
    start caluclate dp[3][4] 
    start caluclate dp[4][5] 
    already calculated! memozation[4][5] = 16 
    start caluclate dp[4][5] 
    already calculated! memozation[4][5] = 16 
    start caluclate dp[3][5] 
    start caluclate dp[4][6] 
    already calculated! memozation[4][6] = -16 
    start caluclate dp[4][6] 
    already calculated! memozation[4][6] = -16 
    start caluclate dp[3][6] 
    start caluclate dp[4][7] 
    already calculated! memozation[4][7] = -16 
    start caluclate dp[4][7] 
    already calculated! memozation[4][7] = -16 
    start caluclate dp[3][7] 
    start caluclate dp[4][8] 
    already calculated! memozation[4][8] = -16 
    start caluclate dp[4][8] 
    already calculated! memozation[4][8] = -16 
    start caluclate dp[3][8] 
    start caluclate dp[4][9] 
    already calculated! memozation[4][9] = -16 
    start caluclate dp[4][9] 
    already calculated! memozation[4][9] = -16 
    start caluclate dp[3][9] 
    start caluclate dp[4][10] 
    index out of range 
    start caluclate dp[3][10] 
    index out of range 
    start caluclate dp[4][9] 
    already calculated! memozation[4][9] = -16 
    choice1, choice2, choice3 = -36, -1000001 ,-16 
    i : 3, j : 9, memoization[i][j] = -16 
    start caluclate dp[4][8] 
    already calculated! memozation[4][8] = -16 
    choice1, choice2, choice3 = -16, -16 ,-16 
    i : 3, j : 8, memoization[i][j] = -16 
    start caluclate dp[4][7] 
    already calculated! memozation[4][7] = -16 
    choice1, choice2, choice3 = -16, -16 ,-16 
    i : 3, j : 7, memoization[i][j] = -16 
    start caluclate dp[4][6] 
    already calculated! memozation[4][6] = -16 
    choice1, choice2, choice3 = -16, -16 ,-16 
    i : 3, j : 6, memoization[i][j] = -16 
    start caluclate dp[4][5] 
    already calculated! memozation[4][5] = 16 
    choice1, choice2, choice3 = 20, -16 ,16 
    i : 3, j : 5, memoization[i][j] = 20 
    start caluclate dp[4][4] 
    already calculated! memozation[4][4] = 16 
    choice1, choice2, choice3 = 34, 20 ,16 
    i : 3, j : 4, memoization[i][j] = 34 
    start caluclate dp[4][3] 
    start caluclate dp[5][4] 
    index out of range 
    start caluclate dp[4][4] 
    already calculated! memozation[4][4] = 16 
    start caluclate dp[5][3] 
    index out of range 
    choice1, choice2, choice3 = 8, 16 ,-1000001 
    i : 4, j : 3, memoization[i][j] = 16 
    choice1, choice2, choice3 = 34, 34 ,16 
    i : 3, j : 3, memoization[i][j] = 34 
    start caluclate dp[3][3] 
    already calculated! memozation[3][3] = 34 
    start caluclate dp[2][3] 
    start caluclate dp[3][4] 
    already calculated! memozation[3][4] = 34 
    start caluclate dp[3][4] 
    already calculated! memozation[3][4] = 34 
    start caluclate dp[2][4] 
    start caluclate dp[3][5] 
    already calculated! memozation[3][5] = 20 
    start caluclate dp[3][5] 
    already calculated! memozation[3][5] = 20 
    start caluclate dp[2][5] 
    start caluclate dp[3][6] 
    already calculated! memozation[3][6] = -16 
    start caluclate dp[3][6] 
    already calculated! memozation[3][6] = -16 
    start caluclate dp[2][6] 
    start caluclate dp[3][7] 
    already calculated! memozation[3][7] = -16 
    start caluclate dp[3][7] 
    already calculated! memozation[3][7] = -16 
    start caluclate dp[2][7] 
    start caluclate dp[3][8] 
    already calculated! memozation[3][8] = -16 
    start caluclate dp[3][8] 
    already calculated! memozation[3][8] = -16 
    start caluclate dp[2][8] 
    start caluclate dp[3][9] 
    already calculated! memozation[3][9] = -16 
    start caluclate dp[3][9] 
    already calculated! memozation[3][9] = -16 
    start caluclate dp[2][9] 
    start caluclate dp[3][10] 
    index out of range 
    start caluclate dp[2][10] 
    index out of range 
    start caluclate dp[3][9] 
    already calculated! memozation[3][9] = -16 
    choice1, choice2, choice3 = -28, -1000001 ,-16 
    i : 2, j : 9, memoization[i][j] = -16 
    start caluclate dp[3][8] 
    already calculated! memozation[3][8] = -16 
    choice1, choice2, choice3 = -16, -16 ,-16 
    i : 2, j : 8, memoization[i][j] = -16 
    start caluclate dp[3][7] 
    already calculated! memozation[3][7] = -16 
    choice1, choice2, choice3 = -16, -16 ,-16 
    i : 2, j : 7, memoization[i][j] = -16 
    start caluclate dp[3][6] 
    already calculated! memozation[3][6] = -16 
    choice1, choice2, choice3 = -16, -16 ,-16 
    i : 2, j : 6, memoization[i][j] = -16 
    start caluclate dp[3][5] 
    already calculated! memozation[3][5] = 20 
    choice1, choice2, choice3 = 12, -16 ,20 
    i : 2, j : 5, memoization[i][j] = 20 
    start caluclate dp[3][4] 
    already calculated! memozation[3][4] = 34 
    choice1, choice2, choice3 = 34, 20 ,34 
    i : 2, j : 4, memoization[i][j] = 34 
    start caluclate dp[3][3] 
    already calculated! memozation[3][3] = 34 
    choice1, choice2, choice3 = 48, 34 ,34 
    i : 2, j : 3, memoization[i][j] = 48 
    start caluclate dp[3][2] 
    start caluclate dp[4][3] 
    already calculated! memozation[4][3] = 16 
    start caluclate dp[4][3] 
    already calculated! memozation[4][3] = 16 
    start caluclate dp[3][3] 
    already calculated! memozation[3][3] = 34 
    start caluclate dp[4][2] 
    start caluclate dp[5][3] 
    index out of range 
    start caluclate dp[4][3] 
    already calculated! memozation[4][3] = 16 
    start caluclate dp[5][2] 
    index out of range 
    choice1, choice2, choice3 = -4, 16 ,-1000001 
    i : 4, j : 2, memoization[i][j] = 16 
    choice1, choice2, choice3 = 16, 34 ,16 
    i : 3, j : 2, memoization[i][j] = 34 
    choice1, choice2, choice3 = 34, 48 ,34 
    i : 2, j : 2, memoization[i][j] = 48 
    start caluclate dp[2][2] 
    already calculated! memozation[2][2] = 48 
    start caluclate dp[1][2] 
    start caluclate dp[2][3] 
    already calculated! memozation[2][3] = 48 
    start caluclate dp[2][3] 
    already calculated! memozation[2][3] = 48 
    start caluclate dp[1][3] 
    start caluclate dp[2][4] 
    already calculated! memozation[2][4] = 34 
    start caluclate dp[2][4] 
    already calculated! memozation[2][4] = 34 
    start caluclate dp[1][4] 
    start caluclate dp[2][5] 
    already calculated! memozation[2][5] = 20 
    start caluclate dp[2][5] 
    already calculated! memozation[2][5] = 20 
    start caluclate dp[1][5] 
    start caluclate dp[2][6] 
    already calculated! memozation[2][6] = -16 
    start caluclate dp[2][6] 
    already calculated! memozation[2][6] = -16 
    start caluclate dp[1][6] 
    start caluclate dp[2][7] 
    already calculated! memozation[2][7] = -16 
    start caluclate dp[2][7] 
    already calculated! memozation[2][7] = -16 
    start caluclate dp[1][7] 
    start caluclate dp[2][8] 
    already calculated! memozation[2][8] = -16 
    start caluclate dp[2][8] 
    already calculated! memozation[2][8] = -16 
    start caluclate dp[1][8] 
    start caluclate dp[2][9] 
    already calculated! memozation[2][9] = -16 
    start caluclate dp[2][9] 
    already calculated! memozation[2][9] = -16 
    start caluclate dp[1][9] 
    start caluclate dp[2][10] 
    index out of range 
    start caluclate dp[1][10] 
    index out of range 
    start caluclate dp[2][9] 
    already calculated! memozation[2][9] = -16 
    choice1, choice2, choice3 = -16, -1000001 ,-16 
    i : 1, j : 9, memoization[i][j] = -16 
    start caluclate dp[2][8] 
    already calculated! memozation[2][8] = -16 
    choice1, choice2, choice3 = -16, -16 ,-16 
    i : 1, j : 8, memoization[i][j] = -16 
    start caluclate dp[2][7] 
    already calculated! memozation[2][7] = -16 
    choice1, choice2, choice3 = -16, -16 ,-16 
    i : 1, j : 7, memoization[i][j] = -16 
    start caluclate dp[2][6] 
    already calculated! memozation[2][6] = -16 
    choice1, choice2, choice3 = -16, -16 ,-16 
    i : 1, j : 6, memoization[i][j] = -16 
    start caluclate dp[2][5] 
    already calculated! memozation[2][5] = 20 
    choice1, choice2, choice3 = 0, -16 ,20 
    i : 1, j : 5, memoization[i][j] = 20 
    start caluclate dp[2][4] 
    already calculated! memozation[2][4] = 34 
    choice1, choice2, choice3 = 28, 20 ,34 
    i : 1, j : 4, memoization[i][j] = 34 
    start caluclate dp[2][3] 
    already calculated! memozation[2][3] = 48 
    choice1, choice2, choice3 = 42, 34 ,48 
    i : 1, j : 3, memoization[i][j] = 48 
    start caluclate dp[2][2] 
    already calculated! memozation[2][2] = 48 
    choice1, choice2, choice3 = 48, 48 ,48 
    i : 1, j : 2, memoization[i][j] = 48 
    start caluclate dp[2][1] 
    start caluclate dp[3][2] 
    already calculated! memozation[3][2] = 34 
    start caluclate dp[3][2] 
    already calculated! memozation[3][2] = 34 
    start caluclate dp[2][2] 
    already calculated! memozation[2][2] = 48 
    start caluclate dp[3][1] 
    start caluclate dp[4][2] 
    already calculated! memozation[4][2] = 16 
    start caluclate dp[4][2] 
    already calculated! memozation[4][2] = 16 
    start caluclate dp[3][2] 
    already calculated! memozation[3][2] = 34 
    start caluclate dp[4][1] 
    start caluclate dp[5][2] 
    index out of range 
    start caluclate dp[4][2] 
    already calculated! memozation[4][2] = 16 
    start caluclate dp[5][1] 
    index out of range 
    choice1, choice2, choice3 = 4, 16 ,-1000001 
    i : 4, j : 1, memoization[i][j] = 16 
    choice1, choice2, choice3 = 25, 34 ,16 
    i : 3, j : 1, memoization[i][j] = 34 
    choice1, choice2, choice3 = 41, 48 ,34 
    i : 2, j : 1, memoization[i][j] = 48 
    choice1, choice2, choice3 = 52, 48 ,48 
    i : 1, j : 1, memoization[i][j] = 52 
    start caluclate dp[1][1] 
    already calculated! memozation[1][1] = 52 
    start caluclate dp[0][1] 
    start caluclate dp[1][2] 
    already calculated! memozation[1][2] = 48 
    start caluclate dp[1][2] 
    already calculated! memozation[1][2] = 48 
    start caluclate dp[0][2] 
    start caluclate dp[1][3] 
    already calculated! memozation[1][3] = 48 
    start caluclate dp[1][3] 
    already calculated! memozation[1][3] = 48 
    start caluclate dp[0][3] 
    start caluclate dp[1][4] 
    already calculated! memozation[1][4] = 34 
    start caluclate dp[1][4] 
    already calculated! memozation[1][4] = 34 
    start caluclate dp[0][4] 
    start caluclate dp[1][5] 
    already calculated! memozation[1][5] = 20 
    start caluclate dp[1][5] 
    already calculated! memozation[1][5] = 20 
    start caluclate dp[0][5] 
    start caluclate dp[1][6] 
    already calculated! memozation[1][6] = -16 
    start caluclate dp[1][6] 
    already calculated! memozation[1][6] = -16 
    start caluclate dp[0][6] 
    start caluclate dp[1][7] 
    already calculated! memozation[1][7] = -16 
    start caluclate dp[1][7] 
    already calculated! memozation[1][7] = -16 
    start caluclate dp[0][7] 
    start caluclate dp[1][8] 
    already calculated! memozation[1][8] = -16 
    start caluclate dp[1][8] 
    already calculated! memozation[1][8] = -16 
    start caluclate dp[0][8] 
    start caluclate dp[1][9] 
    already calculated! memozation[1][9] = -16 
    start caluclate dp[1][9] 
    already calculated! memozation[1][9] = -16 
    start caluclate dp[0][9] 
    start caluclate dp[1][10] 
    index out of range 
    start caluclate dp[0][10] 
    index out of range 
    start caluclate dp[1][9] 
    already calculated! memozation[1][9] = -16 
    choice1, choice2, choice3 = 8, -1000001 ,-16 
    i : 0, j : 9, memoization[i][j] = 8 
    start caluclate dp[1][8] 
    already calculated! memozation[1][8] = -16 
    choice1, choice2, choice3 = 2, 8 ,-16 
    i : 0, j : 8, memoization[i][j] = 8 
    start caluclate dp[1][7] 
    already calculated! memozation[1][7] = -16 
    choice1, choice2, choice3 = 4, 8 ,-16 
    i : 0, j : 7, memoization[i][j] = 8 
    start caluclate dp[1][6] 
    already calculated! memozation[1][6] = -16 
    choice1, choice2, choice3 = -6, 8 ,-16 
    i : 0, j : 6, memoization[i][j] = 8 
    start caluclate dp[1][5] 
    already calculated! memozation[1][5] = 20 
    choice1, choice2, choice3 = -16, 8 ,20 
    i : 0, j : 5, memoization[i][j] = 20 
    start caluclate dp[1][4] 
    already calculated! memozation[1][4] = 34 
    choice1, choice2, choice3 = 20, 20 ,34 
    i : 0, j : 4, memoization[i][j] = 34 
    start caluclate dp[1][3] 
    already calculated! memozation[1][3] = 48 
    choice1, choice2, choice3 = 34, 34 ,48 
    i : 0, j : 3, memoization[i][j] = 48 
    start caluclate dp[1][2] 
    already calculated! memozation[1][2] = 48 
    choice1, choice2, choice3 = 50, 48 ,48 
    i : 0, j : 2, memoization[i][j] = 50 
    start caluclate dp[1][1] 
    already calculated! memozation[1][1] = 52 
    choice1, choice2, choice3 = 48, 50 ,52 
    i : 0, j : 1, memoization[i][j] = 52 
    start caluclate dp[1][0] 
    start caluclate dp[2][1] 
    already calculated! memozation[2][1] = 48 
    start caluclate dp[2][1] 
    already calculated! memozation[2][1] = 48 
    start caluclate dp[1][1] 
    already calculated! memozation[1][1] = 52 
    start caluclate dp[2][0] 
    start caluclate dp[3][1] 
    already calculated! memozation[3][1] = 34 
    start caluclate dp[3][1] 
    already calculated! memozation[3][1] = 34 
    start caluclate dp[2][1] 
    already calculated! memozation[2][1] = 48 
    start caluclate dp[3][0] 
    start caluclate dp[4][1] 
    already calculated! memozation[4][1] = 16 
    start caluclate dp[4][1] 
    already calculated! memozation[4][1] = 16 
    start caluclate dp[3][1] 
    already calculated! memozation[3][1] = 34 
    start caluclate dp[4][0] 
    start caluclate dp[5][1] 
    index out of range 
    start caluclate dp[4][1] 
    already calculated! memozation[4][1] = 16 
    start caluclate dp[5][0] 
    index out of range 
    choice1, choice2, choice3 = 36, 16 ,-1000001 
    i : 4, j : 0, memoization[i][j] = 36 
    choice1, choice2, choice3 = 97, 34 ,36 
    i : 3, j : 0, memoization[i][j] = 97 
    choice1, choice2, choice3 = 97, 48 ,97 
    i : 2, j : 0, memoization[i][j] = 97 
    choice1, choice2, choice3 = 84, 52 ,97 
    i : 1, j : 0, memoization[i][j] = 97 
    choice1, choice2, choice3 = 52, 52 ,97 
    i : 0, j : 0, memoization[i][j] = 97
    ```
    

오류가 뜨는 이유는 다음과 같았다. (log의 100번째 라인 참고)

`dp[3,6] = max(36 + dp[4][7], dp[3,7], dp[4,6])`에서, dp[3,6]을 구하는 입장에서는 dp[4][7]이 음수라면, 0을 반환해야 한다. 그러나 우리의 [dp식정의](https://www.notion.so/8-Oct-2023-1458-Max-Dot-Product-of-Two-Subsequences-2bb49fd7c49c4e6d8b1eef204b418830?pvs=21)는 0 이 아닌 음수를 반환하기 때문에, 36+0이 아닌 36+-16이 되버린것이다. 이건 다음의 코드를

```cpp
int choice1 = dp(i+1,j+1) == -1000001 ? (_nums1[i]*_nums2[j]) : (max(0,(_nums1[i]*_nums2[j])) + dp(i+1,j+1));
```

아래와 같이 바꾸면 되었다.

```cpp
int choice1 = dp(i+1,j+1) == -1000001 ? (_nums1[i]*_nums2[j]) : (max(0,(_nums1[i]*_nums2[j])) + max(0,dp(i+1,j+1)));
```

마지막 코드는 다음과 같다.

- **Final Code**
    
    Debugging
    
    ```cpp
    class Solution {
    public:
    
        int memoization[501][501];
        // bool calculated[501][501] = {false};
        vector<int> _nums1;
        vector<int> _nums2;
        int length1;
        int length2;
        bool isAnswerNegative = true;
        int MaxNegativeAnswer = INT_MIN;
        int dp(int i, int j){
            // printf("start caluclate dp[%d][%d] \n",i,j);
            if(i>=length1 || j >= length2) {
                // printf("index out of range \n");
                return -1000001;
            }
            if(memoization[i][j] != INT_MIN) {
                // printf("already calculated! memozation[%d][%d] = %d \n", i,j,memoization[i][j]);
                return memoization[i][j];
            }
            if(isAnswerNegative && _nums1[i] * _nums2[j] >= 0) isAnswerNegative = false;
            else MaxNegativeAnswer = max(_nums1[i] * _nums2[j], MaxNegativeAnswer);
            int choice1 = dp(i+1,j+1) == -1000001 ? (_nums1[i]*_nums2[j]) : (max(0,(_nums1[i]*_nums2[j])) + max(0,dp(i+1,j+1)));
            int choice2 = dp(i,j+1);
            int choice3 = dp(i+1,j);
            bool end2 = choice2 == -1000001 ? true : false;
            bool end3 = choice3 == -1000001 ? true: false;
            // printf("choice1, choice2, choice3 = %d, %d ,%d \n",choice1,choice2,choice3);
            if(!end2&&!end3) memoization[i][j] = max({choice1,choice2,choice3});
            else if(!end2&&end3) memoization[i][j] = max(choice1, choice2);
            else if(end2&&!end3) memoization[i][j] = max(choice1, choice3);
            else memoization[i][j] = choice1; // (end2&&end3)
            // calculated[i][j] = true;
            // printf("i : %d, j : %d, memoization[i][j] = %d \n",i,j,memoization[i][j]);
            return memoization[i][j];
        }
        int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
            length1 = nums1.size(); length2 = nums2.size();
            for (int i = 0; i < 501; ++i) {
                for (int j = 0; j < 501; ++j) {
                    memoization[i][j] = INT_MIN;
                }
            }
            _nums1 = nums1;
            _nums2 = nums2;
            int i = 0; int j = 0;
            int res = dp(i,j);
            if(isAnswerNegative) return MaxNegativeAnswer;
            else return res;
        }
    };
    ```
    
    Simplified
    
    ```cpp
    class Solution {
    public:
    
        int memoization[501][501];
        bool calculated[501][501] = {false};
        vector<int> _nums1;
        vector<int> _nums2;
        int length1;
        int length2;
        bool isAnswerNegative = true;
        int MaxNegativeAnswer = INT_MIN;
        int dp(int i, int j){
            // printf("start caluclate dp[%d][%d] \n",i,j);
            if(i>=length1 || j >= length2) {
                // printf("index out of range \n");
                return -1000001;
            }
            if(calculated[i][j]) {
                // printf("already calculated! memozation[%d][%d] = %d \n", i,j,memoization[i][j]);
                return memoization[i][j];
            }
            if(isAnswerNegative && _nums1[i] * _nums2[j] >= 0) isAnswerNegative = false;
            else MaxNegativeAnswer = max(_nums1[i] * _nums2[j], MaxNegativeAnswer);
            int choice1 = dp(i+1,j+1) == -1000001 ? (_nums1[i]*_nums2[j]) : (max(0,(_nums1[i]*_nums2[j])) + max(0,dp(i+1,j+1)));
            int choice2 = dp(i,j+1);
            int choice3 = dp(i+1,j);
            bool end2 = choice2 == -1000001 ? true : false;
            bool end3 = choice3 == -1000001 ? true: false;
            // printf("choice1, choice2, choice3 = %d, %d ,%d \n",choice1,choice2,choice3);
            if(!end2&&!end3) memoization[i][j] = max({choice1,choice2,choice3});
            else if(!end2&&end3) memoization[i][j] = max(choice1, choice2);
            else if(end2&&!end3) memoization[i][j] = max(choice1, choice3);
            else memoization[i][j] = choice1; // (end2&&end3)
            calculated[i][j] = true;
            // printf("i : %d, j : %d, memoization[i][j] = %d \n",i,j,memoization[i][j]);
            return memoization[i][j];
        }
        int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
            length1 = nums1.size(); length2 = nums2.size();
            _nums1 = nums1;
            _nums2 = nums2;
            int i = 0; int j = 0;
            int res = dp(i,j);
            if(isAnswerNegative) return MaxNegativeAnswer;
            else return res;
        }
    };
    ```
    

![Untitled](8%20Oct%202023%20-%201458%20Max%20Dot%20Product%20of%20Two%20Subsequen%202bb49fd7c49c4e6d8b1eef204b418830/Untitled%201.png)

하지만 결과가 그닥 만족스럽지 못해서, 이미 있는 solution을 읽어보기로 했다

## Other Solutions

- [https://leetcode.com/problems/max-dot-product-of-two-subsequences/solutions/4143693/92-14-dp-recursive-iterative-explained-intuition/?envType=daily-question&envId=2023-10-07](https://leetcode.com/problems/max-dot-product-of-two-subsequences/solutions/4143693/92-14-dp-recursive-iterative-explained-intuition/?envType=daily-question&envId=2023-10-07)
- [https://leetcode.com/problems/max-dot-product-of-two-subsequences/solutions/4144453/98-32-dp-approach-with-explanation-and-visualization/](https://leetcode.com/problems/max-dot-product-of-two-subsequences/solutions/4144453/98-32-dp-approach-with-explanation-and-visualization/)

첫번째 링크에서 top-down, bottom-up 두가지 방식 모두 구현했는데, 내 코드보다 훨씬 깔끔하고 효율적이였다. 역시 잘하는 사람의 코드를 읽어보는건 언제나 도움이 되는것같다.