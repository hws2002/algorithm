// 비트마스킹을 이용한 에라토스테네스의 체
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

#define LAST_NUM 1'000'000
// #define DEBUG_ERA
typedef long long ll;
using namespace std;

// 비트마스킹을 활용한 에라토스테네스의 체를 구현하기 위한 unsigned char 배열
unsigned char sieve[(LAST_NUM + 7)/8 + 1];

// n 의 소인수들을 담는다
vector<ll> fprimes;

// sqrt(MAX_N)보다 작은 수들 중 소수들을 담는다.
vector<ll> Primes;

ll factorPhi(ll n){
    ll res = n;
    for(auto p : Primes){
        if( n % p == 0) {
#ifdef DEBUG_ERA
            cout<<p<<endl;
#endif
            fprimes.push_back(p);
            res /= p;
            res *= (p-1);
            while( n % p == 0) n /= p;
        }
    }
    
    if( n != 1){
#ifdef DEBUG_ERA
        cout<<n<<endl;
#endif
        res /= n;
        res *= (n-1);
    }
    return res;
}

ll phi(ll n){
    //base
    if( n <= 1) return 1;
    //소인수분해를 한 후 phi까지 적용한다
    return factorPhi(n);
}

bool isPrime(int n){
    return sieve[n>>3] & (1 << (n&7) );
}

void setComposite(int n){
    sieve[n>>3] &= ~( 1 << (n&7));
}


// 1부터 sqrt(MAX_N)까지의 수들 중 소수들을 구한다
void eratosthenes13926(){
    memset(sieve, 255, sizeof(sieve)); // 모든 비트를 1로 켠다
    setComposite(0); // 0과 1은 합성수 처리한다
    setComposite(1);
    
    int sqrtn = (int)sqrt(LAST_NUM);
    for(int d = 2; d <= sqrtn; d++){
        if(isPrime(d)){
            Primes.push_back(d);
            for(int i = d*d; i <= LAST_NUM; i+=d){
                setComposite(i);
            }
        }
    }
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output2.txt","w",stdout);
    //preprocessing
    //먼저 10^9보다 작은 소수들을 먼저 구한다
    eratosthenes13926();
    
    ll n;
    cin>>n;
    cout<<phi(n)<<endl;
    return 0;
}