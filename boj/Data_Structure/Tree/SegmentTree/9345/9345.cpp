#include <iostream>
#include <vector>
#include <limits.h>

#define FOR(i,s,e) for(int i = s; i < e; i++)

#define endl '\n'
// #define DEBUG_RMMQ
using namespace std;
typedef pair<int,int> pii;

struct RMMQ{ // range max/min query
public:
    int n;
    vector<pii> rangeMaxMin;
    vector<int> arI2rmmI;
    
    //constructor
    RMMQ(const int N){
        n = N;
        rangeMaxMin.resize(4*N);
        arI2rmmI.resize(4*N,0);
        init(1, 0, n-1);
    }
    
    pii init(const int nodeNum, const int nodeLeft, const int nodeRight){
        if(nodeRight <= nodeLeft) {
            arI2rmmI[nodeRight] = nodeNum;
            return rangeMaxMin[nodeNum] = {nodeRight,nodeRight};
        }
        
        int mid = (nodeLeft + nodeRight) >> 1;
        auto lmm = init( nodeNum << 1, nodeLeft, mid );
        auto rmm = init( (nodeNum << 1) + 1, mid+1, nodeRight);
        return rangeMaxMin[nodeNum] = { max(lmm.first, rmm.first), min(lmm.second, lmm.second) };
    }
    
    // update
    void update(const int left, const int right){
        // bottom - up
        swap(rangeMaxMin[arI2rmmI[left]], rangeMaxMin[arI2rmmI[right]]);
        // left
        int here = arI2rmmI[left]/2;
        pii leftc, rightc;
        while(here){
            leftc = rangeMaxMin[here<<1]; rightc = rangeMaxMin[(here<<1)+1];
            rangeMaxMin[here] = {max( leftc.first, rightc.first), 
                                 min( leftc.second, rightc.second)
                                };
            here /= 2; // parent가 되버렷!
        }
        
        //right
        here = arI2rmmI[right]/2;
        while(here){
            leftc = rangeMaxMin[here<<1]; rightc = rangeMaxMin[(here<<1)+1];
            rangeMaxMin[here] = {max( leftc.first, rightc.first), 
                                 min( leftc.second, rightc.second)
                                };
            here /= 2; // parent가 되버렷!
        }
    }
    
    // query
    pii query(const int s, const int e, const int nodeNum, const int nodeLeft, const int nodeRight){
        if( nodeRight < s || e < nodeLeft ) return {INT_MIN, INT_MAX};
        if( nodeRight <= nodeLeft) return rangeMaxMin[nodeNum];
        if( s <= nodeLeft && nodeRight <= e) return rangeMaxMin[nodeNum];
        
        int leftc = nodeNum << 1; int rightc = (nodeNum<<1) + 1; int mid = (nodeLeft + nodeRight) >> 1;
        auto lmm = query(s,e, leftc, nodeLeft, mid);
        auto rmm = query(s,e, rightc, mid+1, nodeRight); 
        return { max(lmm.first, rmm.first), min(lmm.second, rmm.second) };
    }
    
    // query - interface
    bool query(const int s,const int e){
        auto mm = query(s, e, 1, 0, n-1); // s부터 e까지의 구간중 max와 min값을 반환한다.
#ifdef DEBUG_RMMQ
        printf(" query(%d,%d), mm = (%d,%d) \n", s, e, mm.first, mm.second);
#endif
        if(mm.first == e && mm.second == s) return true;
        return false;
    }
};

void solve(){
    int N,K;
    cin>>N>>K;

    //pre
    RMMQ rmmq(N);
#ifdef DEBUG_RMMQ
for(int i = 1; i < 10; i++){
    // if(rmmq.arI2rmmI[i]){
        auto mm = rmmq.rangeMaxMin[i];
        printf("rangeMaxMin[%d] : (%d, %d) \n", i, mm.first, mm.second);
    // }
}
#endif
    int Q,A,B;
    FOR(i,0,K){

        cin>>Q>>A>>B;
        if(Q){
            if(rmmq.query(A,B)) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        } else { // change
            rmmq.update(A,B);
#ifdef DEBUG_RMMQ
for(int i = 1; i < 10; i++){
    // if(rmmq.arI2rmmI[i]){
        auto mm = rmmq.rangeMaxMin[i];
        printf("rangeMaxMin[%d] : (%d, %d) \n", i, mm.first, mm.second);
    // }
}
#endif
        }
    }
    
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}