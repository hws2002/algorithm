#include <iostream>
#include <vector>

using namespace std;

int cache[100][100001] = {0};
vector<int> W;
vector<int> V;

int N,K;
int dp(const int idx, const int availableWeight){
    //base
    if( idx >= N || availableWeight <= 0) return 0;
    int& ret = cache[idx][availableWeight];
    if(ret) return ret;
    if( availableWeight >= W[idx]) {
        ret = max( V[idx] + dp(idx+1, availableWeight - W[idx]), dp(idx+1, availableWeight) );
    } else {
        ret = dp(idx+1, availableWeight);
    }
    return ret;
}

int main(){
    //input

    cin>>N>>K;

    int w,v;
    for(int i = 0 ; i < N; i++){
        cin>>w>>v;
        W.push_back(w);
        V.push_back(v);
    }
    
    //solve
    cout<<dp(0,K)<<endl;
    
    return 0;
}