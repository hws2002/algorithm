#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 500'000
#define INF 1'000'000'001
using namespace std;
typedef long long ll;

int N;
vector<pair<int,int>> A;
ll res = 0;

bool compare(pair<int,int> & a, pair<int,int> & b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

struct RSQ{ // range sum query
public:
    int n;
    vector<int> rangeSum;

    //constructor
    RSQ(const vector<int> & array){
        n = array.size();
        rangeMax.resize(4*n,0);
    }

    // query & update
    void update(const int left, const int right, const int nodeNum, const int nodeLeft, const int nodeRight){
        if( nodeRight < left || right < nodeLeft) return rangeSum[nodeNum];
        if( nodeRight <= nodeLeft && left == nodeLeft) {
            rangeSum[nodeNum]++;
            
        }

        if( left <= nodeLeft  && nodeRight <= right ) {
            res += rangeSum[nodeNum];
            return rangeSum[nodeNum];
        }

        int mid = (nodeLeft + nodeRight) >> 1;
        int leftSum = update(idx, left, right, nodeNum<<1    , nodeLeft, mid);
        int rightSum = update(idx, left, right, (nodeNum<<1)+1, mid + 1 , nodeRight);
        return rangeSum[nodeNum] = leftSum + rightSum;
    }


    //cnt를 세줌과 동시에 update한다
    void update(const int left, const int right){
        update(left, right, 1, 0, n-1);
    }
};

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

    //pre
    std::sort(A.begin(), A.end(), compare);
    RSQ rsq(A);

    // solve
    for(int i = 0; i < N; i++){
        rsq.update(A[i].second, N-1);
    }

    cout << res << endl;
    return 0;
}
