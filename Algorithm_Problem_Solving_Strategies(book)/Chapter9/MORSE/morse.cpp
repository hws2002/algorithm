#include <iostream>
#include <cstring>

#define INF 1000000001
#define MAX_N 101
#define endl '\n'
using namespace std;
typedef long long ll;


string ret;

int cache[MAX_N<<1][MAX_N] = {0};

int nchooser(int n, int r){
    int & ret = cache[n][r];
    if(ret) return ret;
    if( r == 0 ) return ret = 1;
    if( n <= 0 ) return ret = 1;
    if( n == r ) return ret = 1;
    return ret = min( nchooser(n-1,r) + nchooser(n-1,r-1), INF);
}

void kth(int n, int m, int k){
    if( n > 0){
        if( nchooser(n+m-1,n-1) < k ){
            ret+='o';
            kth(n, m-1, k - nchooser(n+m-1,n-1) );
            return ;
        } else {
            ret+='-';
            kth(n-1,m,k);
            return ;
        }
    } else {
        while(m--) ret+='o';
        return ;
    }
}

void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    ret = "";
    kth(n,m,k);
    cout<<ret<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}