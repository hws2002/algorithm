#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 500'000
using namespace std;
typedef long long ll;

int N;
vector<int> A;
ll res = 0;
vector<int> temp(MAX_N);

void merge(const int left, const int right){
    
    int lidx = left; 
    int mid = (left+right) >> 1;
    int ridx = mid + 1; 
    int tidx = 0;
    
    while(lidx <= mid && ridx <= right){
        if(A[lidx] > A[ridx]){
            res += (mid + 1 - lidx);
            temp[tidx++] = A[ridx++];
        } else {
            temp[tidx++] = A[lidx++];
        }
    }

    while(lidx <= mid){
        temp[tidx++] = A[lidx++]; 
    }

    while(ridx <= right){
        temp[tidx++] = A[ridx++];
    }

    for(int i = 0; i < tidx; i++){
        A[left+i] = temp[i];
    }
}

// A[left,right] 를 정렬한다.
void mergeSort(const int left, const int right){
    if(right<=left) return;
    int mid = (left + right) >> 1;
    mergeSort(left, mid);
    mergeSort(mid+1, right);
    merge(left,right);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    A.resize(N);
    for(int i = 0; i < N; i++){
        cin >> A[i];
    }
    
    // solve
    mergeSort(0,N-1);

    cout << res << endl;
    return 0;
}
