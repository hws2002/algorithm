#include <iostream>
#include <vector>

// #define DEBUG_SIEVE
#define MAX_N 4'000'001
using namespace std;

int N;
bool removed[MAX_N] = {false};
vector<int> primes;
int res = 0;

// n 보다 작거나 같은 소수를 모은다.
void Sieve(int n){
    // primes.push_back(0);
    int start = 2;
    while(true){
        while(removed[start] == true) start++;
        if(start > n) break;
        primes.push_back(start);
        for(int toremove = start; toremove <= n; toremove += start){
            if( removed[toremove] == false){
                removed[toremove] = true;
            }
        }
    }
}

// TODO
void twoPointer(){
    int lo = 0;
    int hi = 0;
    int partial_sum = 0;
    while(lo < primes.size()){
        if( partial_sum < N){
            if( hi >= primes.size()) return;
            partial_sum += primes[hi++];
        } else if ( partial_sum > N){
            partial_sum -= primes[lo++];
        } else {
            res++;
            partial_sum -= primes[lo++];
        }
    }
}

int main(){
    cin>>N;
    // solve - using eratosthenes's sieve
    Sieve(N);
#ifdef DEBUG_SIEVE
for(auto p : primes){
    cout<<p<<" ";
}    
cout<<endl;
#endif

    // count number of partial sums - two pointers
    twoPointer();
    
    //output
    cout<<res<<endl;
    return 0;
}