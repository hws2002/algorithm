# 16 Oct 2023 - 119.Pascal’s Triangle II

[Pascal's Triangle II - LeetCode](https://leetcode.com/problems/pascals-triangle-ii/description/?envType=daily-question&envId=2023-10-16)

Given an integer `rowIndex`, return the `rowIndex^{th}` (**0-indexed**) row of the **Pascal's triangle**.

In **Pascal's triangle**, each number is the sum of the two numbers directly above it as shown:

![https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

**Example 1:**

```
Input: rowIndex = 3
Output: [1,3,3,1]

```

**Example 2:**

```
Input: rowIndex = 0
Output: [1]

```

**Example 3:**

```
Input: rowIndex = 1
Output: [1,1]

```

**Constraints:**

- `0 <= rowIndex <= 33`

**Follow up:** Could you optimize your algorithm to use only `O(rowIndex)` extra space?

---

## Intuition&Approach

전형적인 memoization으로 풀수있다.

`rowIndex` 가 주어졌을때,

답은 [$i\choose 0$,$i\choose2$,…,$i\choose i-1$,$i\choose i$]형식이 된다.

이때 파스칼 삼각형의 특징${i\choose j} = {i-1\choose j} + {i-1\choose j-1}$ 을 이용하여 값을 빠르게 구하면 된다.

```cpp
class Solution {
public:
    int pascal[34][34] = {0};
    int getPascal(int i, int j){
        if(j>i) return 0;
        if(i<0 || j < 0) return 0;
        if(i==j || j==0 || i<=1) return 1;
        if(pascal[i][j]) return pascal[i][j];
        pascal[i][j] = (getPascal(i-1,j) + getPascal(i-1,j-1));
        return pascal[i][j];
    }
    vector<int> getRow(int rowIndex) {
        vector<int> res;
        for(int j = 0; j <= rowIndex; j++){
            res.push_back(getPascal(rowIndex,j));
        }
        return res;
    }
};
```

![result](16%20Oct%202023%20-%20119%20Pascal%E2%80%99s%20Triangle%20II%20ae7d859b58a842d880d4417a3f0ea2e4/Untitled.png)

result