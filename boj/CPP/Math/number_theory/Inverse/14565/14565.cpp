#include <iostream>

typedef long long ll;

// #define DEBUG_GCD
using namespace std;

ll sumInverse(const ll N, const ll A){
    return N-A;
}

ll gcd( ll N, ll A){
    ll c;
    while(A != 0){
        c = N % A;
        N = A;
        A = c;
    }
    return N;
}

ll solveAxNn(ll A, ll N){
    ll x0 = 0; ll x1 = 1;
    ll n0 = 1; ll n1 = 0;
    ll q,r,n,temp;
    ll x = 1;
    while( A != 1){
        q = N/A; r = N % A;
        N = A; A = r;
        // if(r == 0) break;
        x = x0 - q*x1; x0 = x1; x1 = x;
        n = n0 - q*n1; n0 = n1; n1 = n;
    }
    
    return x;
}


ll mulInverse(const ll N, const ll A){
    ll gcdNA = gcd(N,A);
#ifdef DEBUG_GCD
cout<<"gcdNA : "<<gcdNA<<endl;
#endif
    if(gcdNA != 1) return -1;
    //solve equation Ax + Nn = 1
    ll x = solveAxNn(A,N);
    while( x <= 0 ) x += N;
    return x;
}

int main(){
    ll N,A;
    cin>>N>>A;
    //sumInverse
    cout<<sumInverse(N,A)<<' ';
    
    //mulInverse
    cout<<mulInverse(N,A)<<endl;
    return 0;
}