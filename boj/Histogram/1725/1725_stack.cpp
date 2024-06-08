//stack

#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

// #define DEBUG_SOLVE
#define MAX_N 100'002

typedef long long ll;
using namespace std;

int N;
vector<int> H(MAX_N, 0);
ll res = 0;

int val = -1;
void solve(){
    stack<int> st;
    for(ll i = 0; i <= N+1; i++){
        while(!st.empty() && H[st.top()] >= H[i]){
            ll h = H[st.top()]; 
            st.pop(); if(st.empty()) break;
            res = max( res , h * ( i - (ll)st.top() - 1 ) );
#ifdef DEBUG_SOLVE
cout<<"candidate rectangle : h, i, st.top() + 1 : "<<h<<", "<<i<<", "<<st.top()+1<<endl;
#endif           
        }
        st.push(i);
    }
}

int main(){
    cin>>N;
    for(int i = 1 ; i <= N; i++){
        cin>>H[i];
    }
    H[0] = -1;
    H[N+1] = -1;
    //solve()
    solve();
    
    //output
    cout<<res<<endl;
    return 0;
}