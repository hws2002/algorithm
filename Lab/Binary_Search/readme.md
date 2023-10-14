# LAB : BINARY SEARCH
각종 요구에 맞는 Binary Search를 구현하는 lab이다.  
기본 프레임에 맞춰서 조건에 해당하는 `binsearch`를 구현해보면 된다.  

# CONDITIONS
## CONDITION 1 : 답이 여러개인 경우
1. x = A[i]인 i가 여러개인 경우 그 중 아무거나 반환한다.

2. x = A[i]인 i가 여러개인 경우, 그 중 더 작은 수를 반환한다.

3. x = A[i]인 i가 여러개인 경우, 그 중 더 큰 수를 반환한다.

## CONDITION 2 : A[i-1] < x <= A[i]인 i가 없는 경우  
1. A[i] < x 인 i중 최대값을 반환한다. 세부요구사항은 다음과같이 나뉜다.
   1) x 가 A[n-1] 보다 클 경우 n-1을, x 가 A[0] 보다 작을 경우 -1를 반환한다.  
   2) x 가 A[n-1] 보다 클 경우 n을, x 가 A[0] 보다 작을 경우 0을 반환한다.  
2. x < A[i]인 i중 최소값을 반환한다. 세부요구사항은 다음과같이 나뉜다.
   1) x가 A[n-1]보다 클 경우 n-1을, x가 A[0]보다 작을 경우 -1를 반환한다.
   2) x가 A[n-1]보다 클 경우 n을, x가 A[0]보다 작을 경우 0을 반환한다.

# TASK
CONDITION1 과 CONDITION2를 조합하여 나올수 있는 모든 경우의 이분탐색을 구현해라.

## FILE NAMING
binary_search_{CONDITION1 number}_{CONDITION2 number}_{CONDITION2 detail}.cpp  
ex) binary_search_1_1_1.cpp