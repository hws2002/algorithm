//classic RMQ
#include <iostream>
#include <vector>
#include <limits.h>

#define endl '\n'
#define MAX_N 100'000
#define INF INT_MAX
using namespace std;

int N,M;

struct RMQ{
public: 
    int n; // 각 구간의 최소치
    vector<int> rangeMin;
    
    //constructor
    RMQ(const vector<int> & array){
        n = array.size();
        rangeMin = vector<int> (4*n);
        init(array,1, 0 ,n-1);
    }

    //init
    int init(const vector<int> & array, int node, int left, int right){
        if(right <= left) return rangeMin[node] = array[left];
        int mid = (left + right)>>1;
        int leftMin = init(array, node*2, left, mid);
        int rightMin = init(array, node*2 + 1, mid+1, right);
        return rangeMin[node] = min(leftMin, rightMin);
    }

    //query
    int query(const int left, const int right, int node, int nodeLeft, int nodeRight){
        //공집합
        if(right < nodeLeft || nodeRight < left) return INF;
        // node가 포함하는 범위가 query하는 범위의 부분집합
        if(left <= nodeLeft && nodeRight <= right){
            return rangeMin[node];
        }

        //나머지 경우
        int mid = (nodeLeft + nodeRight) >> 1;
        return min(
            query(left, right, node*2, nodeLeft, mid),
            query(left, right, node*2+1, mid+1, nodeRight)
        );
    }
    //query-interface
    int query(const int left, const int right){
        return query(left,right, 1, 0 , n-1);
    }

    //update - unnecessary
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    vector<int> array(N,0);
    //input
    for(int i = 0 ; i < N; i++){
        cin>>array[i];
    }

    //create SegmentTree
    RMQ rmq(array);

    //query
    int a,b;
    while(M--){
        cin>>a>>b;
        cout<<rmq.query(a-1,b-1)<<endl;
    }
    return 0;
}