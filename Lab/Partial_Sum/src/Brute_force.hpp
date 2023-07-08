extern const int MIN;
extern int s,e;

/***
 * @brief Brute force algorithm for maximum sum of contiguous subarray
 * @param A : a vector of integers
 * @remark 만약 중복된 답이 있을경우, start index가 더 큰 답을 선택하고, start index마저도 같다면, end index가 더 큰 답을 선택한다.
 * @remark s, e에 각각 정답의 start index 와 end index를 저장함.
*/
int Brute_force_MaxSum(const std::vector<int> A){
    int N = A.size(), ret = MIN;
    for(int i=0; i<A.size();++i){
        for(int j=i; j<A.size(); ++j){
            int sum = 0;
            for(int k=i; k<=j; ++k){
                sum += A[k];
            }
            if (ret <= sum){
                ret = sum;
                s = i;
                e = j;
            }
        }
    }
    return ret;
}