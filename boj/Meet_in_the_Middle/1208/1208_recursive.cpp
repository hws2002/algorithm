#include <iostream>
#include <map>

using namespace std;
typedef long long ll;

ll res = 0;
int N,S;
int A[41];
map<int,ll> m;

void rightSeq(int idx, int sum){
    if( idx == N){
        m[sum]++;
        return;
    }
    rightSeq(idx+1, sum+A[idx]);
    rightSeq(idx+1, sum);
}


void leftSeq(int idx, int sum){
    
    if( idx == N/2){
        res += m[S-sum];
        return;
    }
    
    leftSeq(idx+1, sum + A[idx]);
    leftSeq(idx+1, sum);
}

int main(){
	cin.tie(0); cout.tie(0);
	ios::sync_with_stdio(NULL);
    cin>>N>>S;
    for(int i = 0 ; i < N; i++){
        cin>>A[i];
    }
    
    rightSeq(N/2,0);
    leftSeq(0,0);
    
    if(S == 0) cout<<res-1<<endl;
    else cout<<res<<endl;
    return 0;    
}