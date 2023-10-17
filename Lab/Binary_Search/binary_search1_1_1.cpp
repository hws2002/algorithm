#include <iostream>
#include <vector>
#include <random>
using namespace std;

/***
 * @brief Binary Search - CONDITION1
 * @param vector<int> &A : a sorted vector of integers
 * @param x : the value to search for
 * @return int type index: A[i-1] < x <= A[i]인 i를 반환한다.
 * @remark A[-1] = -INF, A[n] = INF 
 * @remark x = A[i]인 i가 여러개인 경우 그 중 아무거나 반환한다.
 * @remark x = A[i]인 i가 없는 경우
 *          * A[i] < x 인  i중 최대값을 반환한다. 
 *          * x 가 A[n-1] 보다 클경우, n-1을,
 *          * x 가 A[0] 보다 작을 경우, -1를 반환한다.
*/
// !TODO!
int binsearch(const vector <int> & A, int x){
    int n = A.size();
    int lo = -1, hi = n;
    while(lo+1 < hi){
        int mid = (lo+hi)/2;
        if (A[mid] < x)
            lo = mid;
        else 
            hi = mid;
    }
    return hi-1;
}

int main(){
    vector<int> to_search = {1,2,3,4,5,6,7,8,9,10};

    //Create a random device
    std::random_device rd;
    //Initialize a random number generator engine with the random device
    std::mt19937 eng(rd());
    //Create a uniform distribution of integers between -1 and 10 (inclusive)
    std::uniform_int_distribution<> distr(-1,11);
    //Generate a random number from the distribution bound by -1 and 10 (inclusive)
    int x = distr(eng);
    cout <<"x = " << x << endl;
    cout <<"Index = " << binsearch(to_search, x) << endl;
    return 0;
}