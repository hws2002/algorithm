#include <iostream>
#include <vector>
#include <cmath>

#define MAX_N (ll) 1'000'000'000'000
#define SQRTN (ll) 1'000'000
#define NAIVE
#define ERATOS
typedef long long ll;

using namespace std;

#ifdef NAIVE
vector<ll> factorNaive(ll n){
    if( n == 1) return vector<ll> (1,1);
    vector<ll> ret;
    ll sqrtn = (ll)sqrt(n);
    for(ll i = 2; i <= sqrtn; i++){
        if( n % i == 0){
            ret.push_back(i);
            while(n % i == 0){
                n/=i;
            }
        }
    }
    if(n > 1) ret.push_back(n);
    return ret;
}

#endif

#ifdef ERATOS
vector<int> Primes;
bool isPrime[SQRTN+1];
void eratosthenes(ll n){
    
}
#endif

ll phi(ll n){
    //1은 예외 처리한다
    if( n <= 1) return 1;
    vector<ll> factors;
#ifdef NAIVE
    factors = factorNaive(n);
#endif

#ifdef ERATOS

#endif
    ll res = n;
    for(auto factor : factors){
        res /= factor;
        res *= (factor - 1);
    }
    return res;
}

int main(){
    ll n;
    cin>>n;
    cout<<phi(n)<<endl;
}
