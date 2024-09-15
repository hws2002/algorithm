#include <iostream>
#define MOD 1000000009
#define endl '\n'

using namespace std;

int RES[100001][4] = {0};

int solve(const int n, const int last){
    if(RES[n][last]) return RES[n][last];
    int res = 0;
    if( last == 1){
        res = (solve(n-2,2) + solve(n-3, 3)) % MOD;
    } else if ( last == 2){
        res = (solve(n-1,1) + solve(n-3, 3)) % MOD;
    } else if (last == 3){
        res = (solve(n-1,1) + solve(n-2, 2)) % MOD;
    } else {
        res = ((solve(n-1,1) + solve(n-2, 2))% MOD + solve(n-3, 3) ) % MOD;
    }
    RES[n][last] = res;
    return res;
}

int main(){
    //input
    int N,T;
    RES[1][0] = 1;RES[1][1] = 0;RES[1][2] = 1;RES[1][3] = 1;
    RES[2][0] = 1;RES[2][1] = 1;RES[2][2] = 0;RES[2][3] = 1;
    RES[3][0] = 3;RES[3][1] = 2;RES[3][2] = 2;RES[3][3] = 2;
    RES[4][0] = 3;RES[4][1] = 1;RES[4][2] = 3;RES[4][3] = 2;
    cin>>T;
    for(int i = 0 ; i < T; i++){
        cin>>N;
        cout<<solve(N,0)<<endl;
    }
    return 0;
}