#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 500'000
#define INF 1'000'000'001
using namespace std;
typedef long long ll;

int N;
vector<pair<int,int> > A;
ll res = 0;


struct RSQ{ // range sum query
public:
    int n;
    vector<int> rangeSum;

    //constructor
    RSQ(const vector<pair<int,int>> & array){
        n = array.size();
        rangeSum.resize(4*n,0);
    }
    
    // query
    ll query(const int left, const int right, const int nodeNum, const int nodeLeft, const int nodeRight){
        if( nodeRight < left || right < nodeLeft) return 0;
        if( left <= nodeLeft && nodeRight <= right) return rangeSum[nodeNum];
        
        int mid = (nodeLeft + nodeRight) >> 1;
        return query(left, right, nodeNum<<1, nodeLeft, mid) + query(left, right, (nodeNum<<1) + 1, mid+1, nodeRight);
    }

    // query - interface
    ll query(const int left ,const int right){
        return query(left, right, 1, 0 , n-1);
    }
    
    // update
    ll update(const int idx, const int value, const int nodeNum, const int nodeLeft, const int nodeRight){
        if( nodeRight < idx || idx < nodeLeft) return rangeSum[nodeNum];
        if( nodeRight <= nodeLeft) return rangeSum[nodeNum] = value;
        
        int mid = (nodeLeft + nodeRight) >> 1;
        ll leftSum = update(idx, value, nodeNum << 1, nodeLeft, mid);
        ll rightSum = update(idx, value, (nodeNum << 1) + 1, mid+1, nodeRight);
        return rangeSum[nodeNum] = leftSum + rightSum;
    }
    
    
    // update-interface
    void update(const int idx, const int value){
        update(idx, value, 1 , 0, n-1);
    }
};


bool compare(pair<int,int> & a, pair<int,int> & b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}    

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    A.resize(N);
    int temp;
    for(int i = 0; i < N; i++){
        cin>>temp;
        A[i] = {temp,i};
    }
    
    RSQ rsq(A);
    
    //sort
    std::sort(A.begin(), A.end(), compare);
    
    // solve
    for(int i = 0; i < N; i++){
        if(A[i].second + 1 <= rsq.n -1)
            res += rsq.query(A[i].second+1, rsq.n - 1);
        rsq.update(A[i].second, 1);
    }
    
    cout << res << endl;
    return 0;
}
