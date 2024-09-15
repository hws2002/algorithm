#include <iostream>

#define endl '\n'

typedef long long ll;

using namespace std;

ll N;
ll k;
bool divisible = false;

void input(){
    cin>>N;
    cin>>k;
}


ll upper_bound_m1(const ll & mid){
    ll res = 0;
    divisible = false;
    ll full = mid / N;
    res += N * full;
    for(ll i = full+1; i <= N; i++){
        res += mid / i;
        if( (mid%i) == 0) divisible = true;
    }
    if(!divisible){
        for(ll i = 1; i <= full; i++){
            if((mid%i) == 0 && ( (mid / i) <= N )) {
                divisible = true;
                break;
            }
        }
    }
    return res;
}

ll lower_bound(const ll & mid){
    ll res = 0;
    ll full = mid / N;
    res += N * full;
    if( (mid%N) == 0) res--;
    for(ll i = full+1; i <= N; i++){
        res += mid / i;
        if( (mid%i) == 0) {
            res--;
        }
    }

    return ++res;
}

/*
parametric search
*/

void solve(){
    ll lo = 0;
    ll hi;
    if( 1e9 < N*N ) 
        hi = (ll)1e9 +1;
    else hi = N*N + 1;
    ll mid, u_index;
    while( lo <= hi) {
        mid = (lo + hi) >> 1;
        divisible = false;
        u_index = upper_bound_m1(mid);
        if (divisible){
            if(u_index > k){
                if(lower_bound(mid) <= k){
                    cout<<mid<<endl;
                    return ;
                } else {
                    hi = mid-1;
                }
            } else if(u_index < k){
                lo = mid+1;
            } else{
                cout<<mid<<endl;
                return ;
            }
        } else {
            if ( u_index < k){
                lo = mid + 1;
            } else if (u_index > k){
                hi = mid - 1;
            } else {
                hi = mid - 1;
            }
        }
    }
}

int main(){
    input();
    solve();
    return 0;
}