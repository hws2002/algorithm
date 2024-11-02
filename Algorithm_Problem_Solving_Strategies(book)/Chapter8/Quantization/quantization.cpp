#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 101
#define MAX_S 11
#define INF 999999999

// #define DEBUG_PS
using namespace std;
typedef long long ll;

int N,S;
vector<ll> arr;
ll cache[MAX_N][MAX_S];
ll preSum[MAX_N] = {0}; // preSum[i] : arr[0,i-1] 까지의 합
ll preSSum[MAX_N] = {0}; // preSSum[i] : arr[0, i-1] 까지의 제곱합

// arr[s, e)의 최소 오차 제곱합을 반환한다
ll minSSE(int s, int e){
    ll mean = int((double(preSum[e] - preSum[s]) / (e-s)) + 0.5);
    return preSSum[e] - preSSum[s] - 2*mean*(preSum[e] - preSum[s]) + (e-s)*mean*mean;
}

ll dp(int idx, int s){
    if( idx >= arr.size()) return 0;
    ll & ret =  cache[idx][s];
    if(ret > -1) return ret;
    
    if(s==1){
        return ret = minSSE(idx, arr.size());
    }
    
    ret = INF;
    for(int w = 1; idx + w <= arr.size(); w++){
        ret = min(ret, minSSE(idx, idx + w) + dp(idx+w, s-1));
    }
    
    return ret;
}

void solve(){
    cin>>N>>S;
    //reset
    for(int i = 0 ; i < N; i++)
        fill(cache[i], cache[i] + S + 1, -1);
    
    arr.resize(N);
    for(int i = 0; i < N; i++)
        cin>>arr[i];

	sort(arr.begin(), arr.end());
	for(int i = 0; i < N; i++){
        preSum[i+1] = arr[i] + preSum[i];
        preSSum[i+1] = arr[i] * arr[i] + preSSum[i];
	}
#ifdef DEBUG_PS
for(int i = 0; i <= N; i++)
	cout<<preSum[i]<< " ";
cout<<endl;
	
for(int i = 0; i <= N; i++)
	cout<<preSSum[i]<< " ";
cout<<endl;
#endif
    cout<<dp(0,S)<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}