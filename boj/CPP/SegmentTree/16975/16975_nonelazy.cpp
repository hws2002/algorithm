#include <iostream>
#include <vector>

#define endl '\n'
// #define DEBUG_SEG
using namespace std;
typedef long long ll;

struct Segtree{
public:
    int n;
    vector<ll> rangeSum;
    
    Segtree(const vector<ll> & arr){
        n = arr.size();
        rangeSum.resize(4*n,0);
    }
    
    
    //update
    ll update(const int idx, const ll toadd, const int nn, const int nl, const int nr){
        if( nr < idx || idx < nl) return rangeSum[nn];
        if( idx <= nl && nr <= idx) return rangeSum[nn] += toadd;
        int mid = (nl + nr) >> 1;
        return rangeSum[nn] = update(idx, toadd, nn*2, nl, mid) + update(idx, toadd, nn*2+1, mid+1, nr);
    }    
    
    //update - interface
    void update(const int l, const int r, const ll toadd){
        update(l, toadd, 1 ,0, n-1);
        if( r+1 <= n-1) update(r+1, -toadd, 1, 0, n-1);
    }
    
    // query
    ll query(const int l, const int r, const int nn, const int nl, const int nr){
        if( nr < l || r < nl) return 0;
        if( l <= nl && nr <= r) return rangeSum[nn];
        int mid = (nl + nr) >> 1;
        return query(l, r, nn*2, nl, mid) + query(l, r, nn*2 + 1, mid+1, nr);
    }    
    
    // query - interface
    ll query(const int idx){
        return query(0, idx, 1, 0, n-1);
    }
};

int N;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    vector<ll> arr(N);

    for(int i = 0 ; i < N; i++){
        cin>>arr[i];
    }

    Segtree seg(arr);
    
#ifdef DEBUG_SEG
for(int i = 0 ; i < 9; i++) cout<<i<<" ";
cout<<endl;
#endif
    int M;
    cin>>M;
    int op,i,j,x;
    ll k;
    while(M--){
#ifdef DEBUG_SEG
for(int l = 1 ; l < 10; l++){
    cout<<seg.rangeSum[l]<<" ";
}
cout<<endl;
#endif
        cin>>op;
        if (op == 1) {
            cin>>i>>j>>k;
            i--; j--;
            seg.update(i,j,k);
        } else {
            cin>>x;
            x--;
            cout<<arr[x] + seg.query(x)<<endl;
        }
    }
    
    return 0;
}