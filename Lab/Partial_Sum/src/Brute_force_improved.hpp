#include "constants.hpp"
/***
 * @brief Brute force algorithm for maximum sum of contiguous subarray
 * @param const vector<int> A : a vector of integers
 * @param int s : start index
 * @param int e : end index
 * @remark 만약 중복된 답이 있을경우, start index가 더 큰 답을 선택하고, start index마저도 같다면, end index가 더 큰 답을 선택한다.
*/
int Improved_Brute_force_MaxSum(const std::vector<int> A){
    int N = A.size(), ret = MIN;
    for(int i=0; i<A.size();++i){
        int sum = 0;
        for(int j=i; j<A.size(); ++j){
            sum += A[j];
            if (ret <= sum){
                ret = sum;
                s = i;
                e = j;
            }
        }
    }
    return ret;
}