#include <iostream>

#define MAX_N 1'000'000'000'000'000'000
#define MAX_M 2'000
#define DEBUG_CACHE
#define DEBUG_SOLVE
using namespace std;

int ncache[MAX_M+1] = {0};
int dcache[MAX_M+1] = {0};

typedef long long ll;
ll N,K,M;

int powM(int a, int p, int MOD){
    int res = 1;
    while(p){
        if(p&1){
            res *= a;
            res %= MOD;
        }
        a *= a;
        a %= MOD;
        p >>= 1;
    }
    return res;
}

int getinverse(int a, int p, int MOD){
    return powM(a,p-2, MOD);
}

void init(){
    ncache[1] = 1;
    dcache[1] = 1;
    for(int i = 2; i <= M; i++){
        ncache[i] = (ncache[i-1] * i) % M;
    }
    
    dcache[M-1] = getinverse(ncache[M-1], M, M);
    
    for(int i = M-2; i >= 1; i--){
        dcache[i] = (dcache[i+1] * (i+1)) % M;
    }
}


int main(){
    cin>>N>>K>>M;
//pre 
    init();
    int res = 1;
#ifdef DEBUG_CACHE
 for(int i = 1; i <= M; i++){
     printf("ncache[%d] : %d , dcache[%d] : %d \n", i, ncache[i], i, dcache[i]);
 }
#endif
    while(N || K){
        int ni = N % M;
        int ki = K % M;
#ifdef DEBUG_SOLVE
 printf("ni, ki : %d, %d \n", ni, ki);
#endif
        if(ki > ni) { res = 0; break;}
        if(ki == 0 || ki == ni)
            res *= 1; 
        else res *= (((ncache[ni] * dcache[ni-ki]) % M) * dcache[ki]) % M; 
        res %= M;
        N /= M;
        K /= M;
    }
    cout<<res<<endl;
    return 0;
}