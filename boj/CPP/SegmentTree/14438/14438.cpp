// range min query
#include <iostream>
#include <vector>

#define endl '\n'
#define MAX_N 100'000
#define INF 2'000'000'000
// #define DEBUG_RMQ
using namespace std;
typedef pair<int,int> pii;
int N,M;

struct RMQ {
public:
    vector<int> rangeMin;
    int n;
    RMQ(const vector<int> & array){
        n = array.size();
        rangeMin = vector<int> (4*n, 0);
        init(array, 1, 0, n-1);
    }
    
    int init(const vector<int> & array, int node, int nodeLeft, int nodeRight){
        if(nodeRight <= nodeLeft) return rangeMin[node] = array[nodeLeft];
        int mid = (nodeLeft + nodeRight) >> 1;
        return rangeMin[node] = min(
                init(array, node*2, nodeLeft, mid),
                init(array, node*2+1, mid+1 , nodeRight)
            );
    }
    
    // update
    int update(int idx, int value, int node, int nodeLeft, int nodeRight){
        if( idx < nodeLeft || nodeRight < idx) return rangeMin[node];
        if( nodeRight <= nodeLeft) return rangeMin[node] = value;
        int mid = (nodeLeft + nodeRight) >> 1;
        return rangeMin[node] = min(
                update(idx, value, node*2, nodeLeft, mid),
                update(idx, value, node*2 + 1, mid+1, nodeRight)
            );
    }
    
    void update(int idx, int value){
        update(idx, value, 1, 0, n-1);    
    }
    
    // query
    int query(int left, int right, int node, int nodeLeft, int nodeRight){
        if( right < nodeLeft || nodeRight < left) return INF;
        if( left <= nodeLeft && nodeRight <= right) return rangeMin[node];
        int mid = (nodeLeft + nodeRight) >> 1;
        return min( query(left, right, node*2, nodeLeft, mid) , query(left, right, node*2 + 1, mid+1, nodeRight));
    }
    
    int query(int left, int right){
        return query(left, right, 1, 0, n-1);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    vector<int> array(N);
    for(int i = 0; i < N; i++){
        cin>>array[i];
    }
    
    //create RMQ instance
    RMQ rmq(array);
    cin>>M;
    int a,b,c;
    for(int i = 0; i < M; i++){
        cin>>a>>b>>c;
        if( a == 1){
            //update
            rmq.update(b-1,c);        
#ifdef DEBUG_RMQ
for(int i = 1; i <= 2*N-1; i++){
    cout<<rmq.rangeMin[i]<<" ";
}
cout<<endl;
#endif
        } else {
            //query
            cout<<rmq.query(b-1,c-1)<<endl;
        }
    }
    return 0;
}
