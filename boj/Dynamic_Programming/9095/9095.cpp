#include <iostream>

using namespace std;


int RES[12] = {0};

int dp(const int & n){
    if( n <= 0) return 0;
    if( n == 1) return 1;
    if( n == 2) return 2;
    if( n == 3) return 4;
    if(RES[n]) return RES[n];
    int res = dp(n-1) + dp(n-2) + dp(n-3);
    RES[n] = res;
    return res;
}

int main(){
    int T,n;
    cin>>T;
    for(int i = 0; i < T; i++){
        cin>>n;
        cout<<dp(n)<<endl;
    }
    return 0;
}
