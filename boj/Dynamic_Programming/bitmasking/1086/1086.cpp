#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cmath>

#define MAX_N 10
#define MAX_K 100
#define DEBUG_PRE
using namespace std;
typedef long long ll;

int N,K;
int A[MAX_N] = {0};
int Length[MAX_N] = {0};
ll cache[MAX_N][1<<MAX_N][MAX_K];

/*
dp(i,chosen,k) : 
선택된 숫자들이 chosen이고, i번째 숫자부터 고려할때, K로 나누었을때 나머지가 k인 순열의 개수

chosen : 1이면 아직 사용하지 않은 수, 0 이면 이미 사용한 수
*/

// ll dp(const int idx, const int chosen, const int k, int length){
//     ll& ret = cache[idx][chosen][k];
//     if(ret > -1) return ret;
    
//     ret = 0;
//     //TODO : 지금까지의 길이는 chosen에 의해 유일하게 결정된다.
    
//     //아직 사용하지 않은 수들중에서
//     for(int i = 0; i < N; i++){
//         ll num = A[i];
//         if( chosen){
//             int k_ = ( (num)%K * ( LENGTH )%K )%K;
//             //-k_
//             k_ = 
//             ret += dp(idx+1, chosen&(~(1<<i)), k_);
//         }
//     }
    
//     return ret;
// }
    
ll fac(ll n){
    if(n <=1 ) return 1;
    return n * fac(n-1);
}

ll gcd(ll a, ll b){
    ll c = a % b;
    while(c != 0){
        a = b;
        b = c;
        c = a % b;
    }
    return b;
}

int main(){
	freopen("input.txt", "r", stdin);
	
    cin>>N;
    vector<string> As(N);
    for(int i = 0 ; i< N; i++){
        cin>>As[i];
    }
    
    cin>>K;
    
    if(K==1){cout<<"1/1"<<endl;return 0;}
    
    //solve
    //preprocessing
    for(int i = 0 ; i < N; i++){
        string s = As[i];
        Length[i] = s.length();
        A[i] = 0;
        ll sub = 1;
        while(s.length() >= 18){
			A[i] = (A[i] + ((stoll(s.substr(s.length()-17, s.length())) % K) * (sub % K)) % K) % K;
            s = s.substr(0, s.length() - 17);
            sub = ( (sub % K) * (ll)pow(10,17) ) % K;
		}
        A[i] = (A[i] + ((stoll(s)%K) * (sub%K)) % K) % K;
    }
#ifdef DEBUG_PRE
for(int i = 0; i < N; i++){
    cout<<"A["<<i<<"] , Length["<<i<<"] : "<<A[i]<<" , "<<Length[i]<<endl;
}
#endif 
    for(int i = 0; i <N; i++){
        for(int j = 0 ; j < (1<<N); j++){
            std::fill(cache[i][j], cache[i][j] + K, -1);
        }
    }
    
    // ll nume = dp(0, (1<<N)-1,0,0);
    // ll deno = fac(N);
    // if(nume == 0) cout<<"0/1"<<endl;
    // else{
    //     ll gcd_ = gcd(nume,deno);
    //     cout<<nume/gcd_<<"/"<<deno/gcd_<<endl;
    // }
    
    return 0;
}