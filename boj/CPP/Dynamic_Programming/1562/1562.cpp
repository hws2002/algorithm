#include <iostream>

#define MAX_N 101
#define PREV 10
#define MOD 1'000'000'000
// #define DEBUG_DP
using namespace std;

typedef long long ll;

int cache[MAX_N][PREV][1<<10] = {0};

int dp(int n, int p, int set){    
#ifdef DEBUG_DP
    printf("dp (%d, %d,  ", n, p);
    string sset = "";
    for(int i = 0; i < 10; i++){
        if(set & (1<<i)) sset+="1";
        else sset+="0";
    }
    for(int i = sset.size()-1; i>=0; i--){
        cout<<sset[i];
    }
    cout<<") "<<set<<endl;
#endif
    int & ret = cache[n][p][set];
    if( n == 0) {
        if(set == 0) return ret = 1;
        return ret = 0;
    }
    
    if( n < 10 ){
        int num1 = 0;
        int set_ = set;
        while(set_){
            if( set_ & 1) num1++;
            set_ >>= 1;
        }
        // printf("num1 : %d \n", num1);
        if( num1 > n) return ret = 0;
    }
    
    if(ret > -1) return ret;
    ret = 0;
    if( 0 < p && p < 9){
        ret = (dp(n-1, p-1, set & ~(1<<(p-1))) + dp(n-1, p+1, set & ~(1<<(p+1)))) % MOD;
    } else if ( p == 0 ) {
        ret = dp(n-1, 1, set & ~(1<<1));
    } else { // p == 9
        ret = dp(n-1, 8, set & ~(1<<8));
    }
    return ret;
}

int main(){
    int N;
    cin>>N;
    for(int j = 0 ; j < MAX_N; j++){
        for(int k = 0 ; k < PREV; k++){
            fill(cache[j][k] , cache[j][k] + (1<<10), -1);
        }
    }
    
    int ret = 0;
    int set = (1<<10)-1;
    for(int s = 1; s <=9; s++){
        ret = (ret + dp(N-1,s, set & ~(1<<s))) % MOD;
    }
    cout<<ret<<endl;
    return 0;
}
