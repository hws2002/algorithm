
# 低吗架构
## Constants.hpp

# 算法实现
## 1. Brute Force

## 2. Improved Brute Force

## 3. Divㅑde and Conquer
이 알고리즘은 위의 두 알고리즘과 비교해 정답의 start index와 end index를 구하기 어렵다는것을 발견했다.


이상하게도, 다음과같은 output을 얻었다
```text
Given Vector : ...
Largest sum of contiguous subarray : 1364 . Start index : 398, End index : 559
The algorithm took 1219806 microseconds
Largest sum of contiguous subarray : 1364 . Start index : 398, End index : 559
The algorithm took 4200 microseconds
Largest sum of contiguous subarray : 1364. Cannot provide index for this algorithm now 
The algorithm took 56994 microseconds
```
어째서?? Divide and Conquer 이 더느리지...?

## 4. Kadane's Algorithm (Dynamic Progamming)

extremely fast!


