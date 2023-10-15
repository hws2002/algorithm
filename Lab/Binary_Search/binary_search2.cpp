#include <iostream>
using namespace std;

/***
 * @brief 二分查找
 * @param vector<int> &A : a sorted vector of integers
 * @param x : the value to search for
 * @return int type index: A[i-1] < x <= A[i]인 i를 반환한다.
 * @remark A[-1] = -INF, A[n] = INF 
 * @remark A[i-1] < x <= A[i]인 i가 여러개인 경우 그 중 더 작은 수를 반환한다.
*/
int binsearch_less(const vector <int> & A, int x){
    int n = A.size();
    int lo = -1, hi = n;
    while(lo<=hi){
        
    }

}

/***
 * @brief 二分查找
 * @param vector<int> &A : a sorted vector of integers
 * @param x : the value to search for
 * @return int type index: A[i-1] < x <= A[i]인 i를 반환한다.
 * @remark A[-1] = -INF, A[n] = INF 
 * @remark A[i-1] < x <= A[i]인 i가 여러개인 경우 그 중 더 큰 수를 반환한다.
*/
int binsearch_more(const vector <int> & A, int x){
    int n = A.size();
    int lo = -1, hi = n;
    while(lo<=hi){

    }

}
int main(){

}