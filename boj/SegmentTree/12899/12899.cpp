#include <iostream>
#include <vector>

#define MAX_N 2'000'000
#define FOR(i,s,e) for(int i = s; i < e; i++)

#define endl '\n'
// #define DEBUG_RSQ
using namespace std;

struct RSQ{ // range sum query
public:
    int n;
    vector<int> rangeSum;
    vector<int> rsI2arI;
    
    //constructor
    RSQ(const int N){
        n = N;
        rangeSum.resize(4*N,0);
        rsI2arI.resize(4*N,0);
    }
    
    
    // update
    int update(const int num, const int toadd, const int nodeNum, const int nodeLeft, const int nodeRight){
        if(num < nodeLeft || nodeRight < num) return rangeSum[nodeNum];
        if(nodeRight <= nodeLeft) {
            if(!rsI2arI[nodeNum]) rsI2arI[nodeNum] = num;
            return rangeSum[nodeNum] += toadd;
            // if(rangeSum[nodeNum] < 0) cout<<"sth went wrong!"<<endl;
        }
        
        int mid = (nodeLeft + nodeRight) >> 1;
        int leftSum = update(num, toadd, nodeNum << 1, nodeLeft, mid);
        int rightSum = update(num, toadd, (nodeNum << 1) + 1, mid+1, nodeRight);
        return rangeSum[nodeNum] = leftSum + rightSum;
    }

    // update - interface
    void update(const int num, const int toadd){
        update(num, toadd, 1, 0, n-1);
    }
    
    // query
    int query(const int idx, const int nodeNum, const int nodeLeft, const int nodeRight){
        if(nodeRight <= nodeLeft) return rsI2arI[nodeNum];
        
        //try left child or right child
        int leftcn = nodeNum << 1; int rightcn = (nodeNum<<1) + 1; int mid = (nodeLeft + nodeRight) >> 1;
        
        if(rangeSum[leftcn] >= idx){
            return query(idx, leftcn, nodeLeft, mid);
        } else {
            return query(idx - rangeSum[leftcn], rightcn, mid+1, nodeRight); 
        }
    }
    
    // query - interface
    int query(const int idx){
        return query(idx, 1, 0, n-1);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    //pre
    RSQ rsq(MAX_N);
    
    int N,T,X;
    cin>>N;

    FOR(i,0,N){
#ifdef DEBUG_RSQ
    printf("rsq.rangeSum[1] : %d \n", rsq.rangeSum[1]);
#endif
        cin>>T>>X;
        if(T == 1){ // add
            rsq.update(X-1,1);
        } else { // query && remove
            int num = rsq.query(X);
            cout<<num+1<<endl;
            rsq.update(num,-1);
        }
    }
    
    return 0;
}