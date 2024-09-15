// range product query

#include <iostream>
#include <vector>

#define endl '\n'
// #define DEBUG_RPQ
typedef long long ll;
#define MOD 1'000'000'007
using namespace std;

int N,M,K;

struct RPQ{
public:
    vector<int> rangeProduct;
    int n;
    //constructor
    RPQ(const vector<ll> & array){
        n = array.size();
        rangeProduct.resize(4*n);
        init(array,1,0,n-1);
    }
    
    ll init(const vector<ll> & array,int node, int nodeLeft, int nodeRight){
        if( nodeRight <= nodeLeft) return rangeProduct[node] = array[nodeLeft];
        int mid = (nodeLeft + nodeRight) >> 1;
        return rangeProduct[node] = ( (init(array, node*2  , nodeLeft, mid      ) % MOD ) * 
                                      (init(array, node*2+1, mid+1   , nodeRight) % MOD )  )% MOD;
    }
    
    // update
    ll update(const int idx, const int newValue, int node, int nodeLeft, int nodeRight){
        if( idx < nodeLeft || nodeRight < idx) return rangeProduct[node];
        if( nodeRight <= nodeLeft) return rangeProduct[node] = newValue;
        int mid = (nodeLeft + nodeRight) >> 1;
        return rangeProduct[node] = (
                                        ( update(idx, newValue, node*2  , nodeLeft, mid      ) % MOD) * 
                                        ( update(idx, newValue, node*2+1, mid+1   , nodeRight) % MOD)
                                    ) % MOD;
    }
    
    void update(int idx, int newValue){
        update(idx, newValue, 1, 0 , n-1);
    }
    
    // query
    ll query(int left, int right, int node, int nodeLeft, int nodeRight){
        if(right < nodeLeft || nodeRight < left) return 1;
        if(left <= nodeLeft && nodeRight <= right) return rangeProduct[node];
        int mid = (nodeLeft + nodeRight) >> 1;
        return (query(left, right, node*2, nodeLeft, mid) % MOD * query(left, right, node*2 + 1, mid+1, nodeRight) % MOD) % MOD;
    }
    
    ll query(int left, int right){
        return query(left, right, 1 ,0, n-1);
    }
    
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M>>K;
    vector<ll> array(N);
    for(int i = 0 ; i < N; i++){
        cin>>array[i];
    }
    //create RPQ
    RPQ rpq(array);
#ifdef DEBUG_RPQ
for(int j = 0; j < 2*N; j++){
    cout<<rpq.rangeProduct[j]<<" ";
}
cout<<endl;
#endif
    int a,b;
    ll c;
    for(int i = 0 ; i < M+K; i++){
        cin>>a>>b>>c;
        if( a == 1 ){ // update
            rpq.update(b-1,c);
        } else { // query
            cout<<rpq.query(b-1,(int)c-1)<<endl;        
        }
#ifdef DEBUG_RPQ
for(int j = 0; j < 2*N; j++){
    cout<<rpq.rangeProduct[j]<<" ";
}
cout<<endl;
#endif
    }
    return 0;
}