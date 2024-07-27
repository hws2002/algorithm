#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

#define MAX_N 1'000'000
#define MAX_K 10'000
#define FOR(i,s,e) for(int i = s; i < e; i++)

// #define DEBUG_PARAM
using namespace std;
typedef long long ll;

vector<ll> lane;
ll K;
ll N;
ll res = 0;

ll numGeq(const ll & h){
    
    // auto it1 = lower_bound(lane.begin(), lane.end(), h);
    // auto it2 = lower_bound(lane.begin(), lane.end(), 2*h);
    // return (lane.end() - it1) + (lane.end() - it2);
    
    ll res = 0;
    for(auto l : lane){
        res += l/h;
    }
    return res;
}

int main(){
    cin>>K>>N;
    ll temp;
    ll longest = -1;
    // int shortest = INT_MAX;
    
    FOR(i,0,K){
        cin>>temp;
        lane.push_back(temp);
        longest = max(longest,temp);
        // shortest = min(shortest, temp);
    }
    
    // sort
    // std::sort(lane.begin(), lane.end());
    
    //parametric search, [)
    ll lo = 1; ll hi = longest+1;
    ll mid;
    
    while(lo < hi){
        mid = (lo + hi)>>1;
        ll numgeqn = numGeq(mid);
#ifdef DEBUG_PARAM
printf("lo, hi, mid, numgeqn : %d, %d, %d, %d \n", lo, hi, mid, numgeqn);
#endif
        if( numgeqn >= N){
            if( lo == mid) break;
            lo = mid;
        } else {// numGeqn > N
            hi = mid;
        }
    }
    
    cout<<mid<<endl;
    return 0;
}