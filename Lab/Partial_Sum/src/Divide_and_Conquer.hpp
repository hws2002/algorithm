#include "constants.hpp"
/***
 * @brief Algorithm for maximum sum of contiguous subarray, using divide and conquer
 * @details A[lo~hi]의 largest partial sum 을 찾음, not A[lo~hi)
 * @param A : a vector of integers
 * @param lo : 
 * @param hi : 
 * @remark 만약 중복된 답이 있을경우, start index가 더 큰 답을 선택하고, start index마저도 같다면, end index가 더 큰 답을 선택한다.
 * @remark 단점 : starting index, end index를 구할 수 없음
*/

int Divide_and_Conquer_MaxSum(const std::vector<int> A, int lo, int hi){
    //base
    if(lo == hi) return A[lo];
    // Divide array into two subarrays. A[lo]~A[mid] and A[mid+1]~A[hi]
    int mid = (lo+hi)>>1;
    // 두 부분에 모두 걸쳐 있는 최대 합 구간을 구한다.
    // A[i,mid] + A[mid+1,j]형식일 것.
    int left = MIN, right = MIN, sum = 0;
    for (int i=mid; i>=lo; --i){
        sum += A[i];
        left = max(sum,left);
    }
    sum = 0;
    for (int j = mid+1; j<= hi; ++j){
        sum += A[j];
        right = max(sum,right);
    }
    int single = max(Divide_and_Conquer_MaxSum(A,lo,mid),
                    Divide_and_Conquer_MaxSum(A,mid+1,hi));
    return max(left+right, single);
}