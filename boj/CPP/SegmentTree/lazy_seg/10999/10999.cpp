#include <iostream>
#include <vector>
#define endl '\n'
#define FOR(i,s,e) for(int i = s; i < e; i++)

using namespace std;
typedef long long ll;

int N,M,K;

struct RSQ{
public :
    int n;
    vector<ll> rangeSum;
    vector<ll> lazy;
    
    RSQ(const vector<ll> & arr){
        n = arr.size();
        rangeSum.resize(4*n);
        lazy = vector<ll>(4*n,0);
        init(arr, 1, 0, n-1);
    }
    
    ll init(const vector<ll> & arr, int nodeNum, int nodeLeft, int nodeRight){
        if( nodeRight <= nodeLeft) return rangeSum[nodeNum] = arr[nodeLeft];
        int mid = (nodeLeft + nodeRight) >> 1;
        return rangeSum[nodeNum] = init(arr, nodeNum<<1, nodeLeft, mid) + init(arr, (nodeNum<<1)+1, mid+1, nodeRight);
    }
    
    void propagate(const int nodeNum, const int nodeLeft, const int nodeRight){
        if( lazy[nodeNum] ==0 ) return;
        rangeSum[nodeNum] += (nodeRight - nodeLeft + 1) * lazy[nodeNum];
        if( nodeLeft < nodeRight){ // 리프 노드가 아니라면 propagate!
            lazy[nodeNum<<1] += lazy[nodeNum];
            lazy[(nodeNum<<1) + 1] += lazy[nodeNum];
        }        
        lazy[nodeNum] = 0;
        return ;
    }
    
    //add
    ll add(const int l , const int r, ll toadd, const int nodeNum, const int nodeLeft, const int nodeRight){
        
        propagate(nodeNum, nodeLeft, nodeRight);
        
        //out of range
        if( r < nodeLeft || nodeRight < l) return rangeSum[nodeNum];
        
        //inside range
        if( l <= nodeLeft && nodeRight <= r) {
            rangeSum[nodeNum] += (nodeRight - nodeLeft + 1) * toadd;
            if( nodeLeft < nodeRight ){ // 리프 노드가 아니라면
                lazy[nodeNum<<1] += toadd;
                lazy[(nodeNum<<1) + 1] += toadd;
            }
            return rangeSum[nodeNum];
        }

        int mid = (nodeLeft + nodeRight) >> 1;
        return rangeSum[nodeNum] = add(l,r, toadd, nodeNum<<1, nodeLeft, mid) 
                                + add(l,r, toadd, (nodeNum<<1) + 1, mid+1, nodeRight);
    }

    //add - interface
    void add(const int l, const int r, const ll toadd){
        add(l,r,toadd,1,0,n-1);
    }

    //query
    ll query(const int l, const int r, const int nodeNum, const int nodeLeft, const int nodeRight){
        //push
        propagate(nodeNum, nodeLeft, nodeRight);

        //out of range
        if( r < nodeLeft || nodeRight < l) return 0;

        //inside range
        if( l <= nodeLeft && nodeRight <= r) {
            return rangeSum[nodeNum];
        }

        int mid = (nodeLeft + nodeRight) >> 1;
        return query(l,r,nodeNum<<1, nodeLeft, mid) + query(l,r,(nodeNum<<1) + 1, mid+1, nodeRight);
    }

    //query - interface
    ll query(const int l, const int r){
        return query(l,r,1,0,n-1);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M>>K;
    vector<ll> arr(N);
    
    //input
    FOR(i,0,N){
        cin>>arr[i];
    }
    
    RSQ rsq(arr);

    int a,b,c;
    ll d;
    FOR(i,0,M+K){
        cin>>a;
        if( a== 1){ // sum
            cin>>b>>c>>d;
            b--; c--;
            rsq.add(b,c,d);
        } else { // query
            cin>>b>>c;
            b--; c--;
            cout<<rsq.query(b,c)<<endl;
        }
    }

    return 0;
}