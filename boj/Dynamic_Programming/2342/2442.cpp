// 15:38 - 
// dp?
/*

*/
#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>

#define MAX_N 100'000
#define INF 5'000'000

// #define DEBUG_DP
using namespace std;

vector<int> S;

int N; // length of sequence
int cache[MAX_N][20] = {0};

int S2I[5][5] = {
    {-1,  0,  1,  2,  3},
    { 4, -1,  5,  6,  7},
    { 8,  9, -1, 10, 11},
    {12, 13, 14, -1, 15},
    {16, 17, 18, 19, -1}
};

int CM[5][5] = {
    {0,2,2,2,2},
    {0,1,3,4,3},
    {0,3,1,3,4},
    {0,4,3,1,3},
    {0,3,4,3,1}
};

int state2idx(int state[2]){
    return S2I[state[0]][state[1]];
}

int costMove(int from, int to){
    return CM[from][to];
}

int dp(int idx, int state[2]){
    //base
    if( idx+1 >= N) return 0;
    int stateIdx = state2idx(state);
#ifdef DEBUG_DP
cout<<"state : ("<<state[0]<<","<<state[1]<<"), stateidx : "<<stateIdx;
cout<<" | S[idx] : "<<S[idx]<<endl;
#endif
    if( stateIdx == -1) {cout<<"sth went wrong"<<endl; return -100;}
    int& ret = cache[idx][stateIdx];
    if(ret) return ret;
    if(state[0] == S[idx] || state[1] == S[idx]){
#ifdef DEBUG_DP
cout<<"one feet is one the place"<<endl;
#endif
        return ret = 1 + dp(idx+1, state);
#ifdef DEBUG_DP
cout<<"ret : "<<ret<<endl;
#endif
    } else {
        // none of the feet is on S[idx+1]
#ifdef DEBUG_DP
cout<<"none of the feet is on S[idx+1]"<<endl;
#endif
        // compare moving left foot and right foot
        int state1[2] = {S[idx], state[1]};
        int state2[2] = {state[0], S[idx]};
        ret = min(
                  costMove( state[0], S[idx] ) + dp( idx+1, state1 ),
                  costMove( state[1], S[idx] ) + dp( idx+1, state2 )
                );
#ifdef DEBUG_DP
cout<<"ret : "<<ret<<endl;
#endif
        return ret;
    }
}

int main(){
    
    //input
    int temp = 1;
    while(temp){
        cin>>temp;
        S.push_back(temp);
    }
    N = S.size();
    if(N == 1){
        cout<<0<<endl;
        return 0;
    }
    //dp & output
    int state1[2] = {0,S[0]}; // right foot
    int state2[2] = {S[0], 0}; // left foot
    cout<<2 + min( dp(1, state1), dp(1, state2) )<<endl;
    
    return 0;
}