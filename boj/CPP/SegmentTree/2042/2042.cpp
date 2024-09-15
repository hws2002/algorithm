// range sum query

/*
정답이 -2^63보다 크거나 같고, 2^63-1보다 작거나 같은 정수라는게 확정이라고 쳐도,
과연 rangeSum의 모든 값이 long long안에 있다는 걸 보장할 수 있을까?
*/
#include <iostream>
#include <vector>

#define MAX_N 1'000'001
#define MAX_K 10'000
#define MAX_M 10'000
#define endl '\n'
typedef long long ll;
using namespace std;


int N,M,K;
ll A[MAX_N];

struct RSQ {
public:
    vector<ll> rangeSum;
    int n;
    //constructor
    
    RSQ(const ll array[], const int n_){
        n = n_;
        rangeSum = vector<ll> (4*n);
        init(array, 1, 0, n-1);
    }
    
    ll init(const ll array[], int node, int left, int right){
        if( right <= left) return rangeSum[node] = array[left];
        int mid = (left + right)>>1;
        return rangeSum[node] = init(array, node*2, left, mid) + init(array, node*2+1, mid+1, right);
    }
    
    //update
    ll update(const int idx, const ll value, int node, int nodeLeft, int nodeRight){
        if( idx < nodeLeft || nodeRight < idx) return rangeSum[node];
        if( nodeRight <= nodeLeft) return rangeSum[node] = value;
        int mid = (nodeLeft + nodeRight) >> 1;
        return rangeSum[node] = update(idx, value, node*2, nodeLeft, mid) + update(idx, value, node*2+1, mid+1, nodeRight);
    }
    
    ll update(const int idx, const ll value){
        return update(idx, value, 1, 0, n-1);
    }
    
    //query
    ll query(int left, int right, int node, int nodeLeft, int nodeRight){
        if(right < nodeLeft || nodeRight < left) return 0;
        if(left <= nodeLeft && nodeRight <= right) return rangeSum[node];
        int mid = (nodeLeft + nodeRight) >> 1;
        return query(left, right, node*2, nodeLeft, mid) + query(left, right, node*2+1, mid+1, nodeRight); 
    }
    
    ll query(int left, int right){
        return query(left, right, 1, 0, n-1);
    }
};



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M>>K;
    for(int i = 0 ; i < N; i++){
        cin>>A[i];
    }
    
    //creat RSQ instance
    RSQ rsq(A,N);
    
    int a, b;
    ll c;
    for(int i = 0 ; i < M+K ; i++){
        cin>>a>>b>>c;
        if(a == 1){
            //update
            rsq.update(b-1,c);
        } else {
            //query
            cout<<rsq.query(b-1,(int)c-1)<<endl;
        }    
    }
    return 0;
}
