//dnq

#include <iostream>
#include <vector>

// #define DEBUG_SOLVE
#define MAX_N 100'002

typedef long long ll;
using namespace std;

int N;
vector<ll> H(MAX_N, 0);

ll solve(int left, int right){
    if(left == right) return H[left];
    // [left,mid] , [mid+1, right]
    int mid = (left+right)>>1;
    ll ret = max(solve(left,mid), solve(mid+1, right));
    
    ll lo = mid, hi = mid+1;
    ll height = min(H[lo], H[hi]);
    ret = max(ret, height*2);
    
    while(left < lo || hi < right){
        if( hi < right && ( lo == left || H[hi+1] > H[lo-1])){
            hi++;
            height = min(height, H[hi]);
        } else {
            lo--;
            height = min(height, H[lo]);
        }
        ret = max(ret, height * (hi-lo+1));
    }
    return ret;
}

int main(){
    cin>>N;
    for(int i = 0 ; i < N; i++){
        cin>>H[i];
    }
    
    //solve
    cout<<solve(0,N-1)<<endl;
    return 0;
}