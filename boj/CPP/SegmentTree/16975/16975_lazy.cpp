#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 500'000
#define INF 1'000'000'001
#define endl '\n'

using namespace std;
typedef long long ll;

int N,M;
vector<ll> A;

struct RSQ{ // range sum query
public:
    int n;
    vector<ll> rangeSum;
    vector<ll> lazy;
    
    //constructor
    RSQ(const vector<ll> & array){
        n = array.size();
        rangeSum.resize(4*n);
        lazy.resize(4*n,0);
        init(array, 1, 0, n-1);
    }
    
    ll init(const vector<ll> & array, const int nodeNum, const int nodeLeft, const int nodeRight){
        if(nodeRight <= nodeLeft) {
            return rangeSum[nodeNum] = array[nodeLeft];
        }
        
        int mid = (nodeLeft + nodeRight) >> 1;

        return rangeSum[nodeNum] = init(array, nodeNum << 1, nodeLeft , mid) +
                                   init(array, (nodeNum << 1) + 1, mid + 1, nodeRight);
    }
    
    // update
    void update(const int left, const int right, const ll toadd, const int nodeNum, const int nodeLeft, const int nodeRight){
        if( nodeRight < left || right < nodeLeft) 
            return;
        
        if( nodeRight <= nodeLeft){ 
            rangeSum[nodeNum] += toadd;
            return ;
        }
        
        if( left <= nodeLeft && nodeRight <= right) {
            lazy[nodeNum] += toadd;
            return;
        }

        int mid = (nodeLeft + nodeRight) >> 1;
        update(left, right, toadd, nodeNum << 1, nodeLeft, mid);
        update(left, right, toadd, (nodeNum << 1) + 1, mid+1, nodeRight);
    }
    
    // update-interface
    void update(const int left, const int right, const ll toadd){
        update(left, right, toadd, 1 , 0, n-1);
    }

    
    ll query(const int idx, const int nodeNum, const int nodeLeft, const int nodeRight, ll toadd){
        if(toadd) {
            lazy[nodeNum] += toadd;
        }
        
        if( nodeRight < idx || idx < nodeLeft) return 0;
        
        if( nodeRight <= nodeLeft) {
            ll temp = lazy[nodeNum];
            lazy[nodeNum] = 0;
            return rangeSum[nodeNum] += temp;
        }
        
        int mid = (nodeLeft + nodeRight) >> 1;
        ll temp = lazy[nodeNum];
        lazy[nodeNum] = 0;
        return query(idx, nodeNum<<1, nodeLeft, mid, temp) +
                query(idx, (nodeNum<<1) + 1, mid+1, nodeRight, temp);
    }
    
    // query - interface
    ll query(const int idx){
        return query(idx, 1, 0, n-1,0);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    A.resize(N);

    for(int i = 0; i < N; i++){
        cin>>A[i];
    }
    
    RSQ rsq(A);
    
    cin>>M;
    
    int op, i, j, x;
    ll k;
    
    while(M--){
        cin>>op;
        if( op == 1){
            cin>>i>>j>>k;
            rsq.update(i-1,j-1,k);
        } else {
            cin>>x;
            cout<<rsq.query(x-1)<<endl;
        }
    }
    return 0;
}
