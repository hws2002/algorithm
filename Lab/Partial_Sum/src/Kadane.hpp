#include "constants.hpp"

/***
 * @brief Kadane's algorithm for maximum sum of contiguous subarray
 * @param const vector<int> A : a vector of integers
*/
int Kadane_MaxSum(const vector<int> & A){
    int N = A.size(), ret = MIN, psum = 0;
    for(int i=0; i<N; ++i){
        psum = max(psum,0) + A[i];
        ret = max(psum,ret);
    }
    return ret;
}