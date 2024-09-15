#include <iostream>
#include <vector>
#define MOD 1000000007

typedef long long ll;

using namespace std;

struct SquareMatrix{
public :
    int N;
    vector<vector<ll> > v;
    SquareMatrix(int _N);
    ~SquareMatrix();
    static SquareMatrix identity(int N);
    SquareMatrix operator * (const SquareMatrix& rhs) const;
    SquareMatrix operator % (const ll mod) const;
    SquareMatrix pow(ll n) const;
    ll * operator[] (int idx);
    
};

SquareMatrix::SquareMatrix(int _N){
    N = _N;
    v.resize(N, vector<ll>(N,0));
}

SquareMatrix::~SquareMatrix(){}

SquareMatrix SquareMatrix::identity(int N){
    SquareMatrix ret = SquareMatrix(N);
    for(int i = 0; i < N; i++) ret.v[i][i] = 1;
    return ret;
}

SquareMatrix SquareMatrix::operator * (const SquareMatrix & rhs) const {
    // assert(N == rhs.N);
    SquareMatrix ret = SquareMatrix(N);
    for(int k = 0 ; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N ; j++){
                ret.v[i][j] = (ret.v[i][j] + ((v[i][k] * rhs.v[k][j]) % MOD)) % MOD;
            }
        }
    }
    return ret;
}

SquareMatrix SquareMatrix::operator % (const ll mod) const {
    SquareMatrix ret = *this;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            ret.v[i][j] %= mod;
        }
    }
    return ret;
}

SquareMatrix SquareMatrix::pow(ll n) const {
    if( n==0 ) return SquareMatrix::identity(N);
    if( n%2 > 0) return (*this *  this->pow(n-1) ) % MOD;
    SquareMatrix half = this->pow(n/2) % MOD;
    return (half * half) % MOD;
}

ll * SquareMatrix::operator [](int idx){
    return &v[idx][0];
}

ll fib5(ll n){
    if( n == 0 ) return 0;
    SquareMatrix W(2);
    W[0][0] = 0;
    W[0][1] = W[1][0] = W[1][1] = 1;
    return W.pow(n-1)[1][1];
}

ll n;
int main(){
    //input
    cin>>n;
    cout<<fib5(n)<<endl;
    return 0;
}