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
    vector<pii> rangeMin;
    int n;
    RMQ(const vector<int> & array){
        n = array.size();
        rangeMin = vector<pii> (4*n);
        init(array, 1, 0, n-1);
    }
    
    pii init(const vector<int> & array, int node, int nodeLeft, int nodeRight){
        if(nodeRight <= nodeLeft) return rangeMin[node] = {nodeLeft, array[nodeLeft]};
        int mid = (nodeLeft + nodeRight) >> 1;
        auto leftMinP = init(array, node*2, nodeLeft, mid);
        auto rightMinP = init(array, node*2 + 1, mid + 1, nodeRight);
        if( leftMinP.second <= rightMinP.second){
            rangeMin[node] = leftMinP;
        } else { // leftMinP.second > rightMinP.second
            rangeMin[node] = rightMinP;
        }
        return rangeMin[node];
    }
    
    // update
    pii update(int idx, int value, int node, int nodeLeft, int nodeRight){
        if( idx < nodeLeft || nodeRight < idx) return rangeMin[node];
        if( nodeRight <= nodeLeft) return rangeMin[node] = {idx, value};
        int mid = (nodeLeft + nodeRight) >> 1;
        auto leftMinP = update(idx, value, node * 2, nodeLeft, mid);
        auto rightMinP = update(idx, value, node * 2 + 1, mid + 1, nodeRight);
        if( leftMinP.second <= rightMinP.second){
            rangeMin[node] = leftMinP;
        } else {
            rangeMin[node] = rightMinP;
        }
        return rangeMin[node];
    }
    
    void update(int idx, int value){
        update(idx, value, 1, 0, n-1);    
    }
    
    // query
    pii query(int left, int right, int node, int nodeLeft, int nodeRight){
        if( right < nodeLeft || nodeRight < left) return {INF,INF};
        if( left <= nodeLeft && nodeRight <= right) return rangeMin[node];
        int mid = (nodeLeft + nodeRight) >> 1;
        auto leftMinP = update(left, right, node * 2, nodeLeft, mid);
        auto rightMinP = update(left, right, node * 2 + 1, mid + 1, nodeRight);
        if(leftMinP.second <= rightMinP.second) return leftMinP;
        else return rightMinP;
    }
    
    int query(int left = 0, int right = N-1){
        return query(left, right, 1, 0, n-1).first;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
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
        cin>>a;
        if( a == 1){
            cin>>b>>c;
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
            cout<<rmq.query()+1<<endl;
        }
    }
    return 0;
}
