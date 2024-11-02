// meet in the middle

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 30
#define MAX_C 1'000'000'000
// #define DEBUG_RIGHTSEQ
using namespace std;
typedef long long ll;

int N;
ll C;

ll Weights[MAX_N];
vector<ll> availableW;
ll res = 0;
void rightSeq(const int idx, ll s){
    if( s > C) return;
    if( idx >= N) {
        availableW.push_back(s);
        return ;
    }
    rightSeq(idx+1, s + Weights[idx]);
    rightSeq(idx+1, s);
}

void leftSeq(const int idx, ll s){
    if( s > C) return;
    if( idx >= N/2){
        auto it = upper_bound(availableW.begin(), availableW.end(), C - s);
        res += it - availableW.begin();
        return ;
    }
    leftSeq(idx+1, s + Weights[idx]);
    leftSeq(idx+1, s);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>N>>C;
    
    for(int i = 0; i < N; i++){
        cin>>Weights[i];
    }
    
    rightSeq(N/2,0);
    sort(availableW.begin(), availableW.end());
#ifdef DEBUG_RIGHTSEQ
for(auto w : availableW){
    printf("%d ", w);
}
cout<<endl;
#endif
    leftSeq(0,0);
    
    cout<<res<<endl;
    return 0;
}