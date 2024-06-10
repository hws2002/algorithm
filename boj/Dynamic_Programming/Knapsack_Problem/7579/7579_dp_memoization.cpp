//dp - 메모리 초과

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits.h>

#define MAX_N 100
#define INF INT_MAX

#define DEBUG_VCM
#define DEBUG_DP
using namespace std;

int N,M;
int m[MAX_N];
int c[MAX_N];

vector< int > VCM[MAX_N+1];//vector[cost] = {memory}
int cache[10001][101][100] = {0};

bool compare(const int & a, const int & b){
    return a > b;
}

// int ret = INF;
int largestC = 0;

int greedy(int totalCost, int cost, int idx, int m2Get){
    //base
    int& res = cache[totalCost][cost][idx];
    if(res) return res;
    res = INF;
#ifdef DEBUG_DP
cout<<"totalCost, cost, idx, m2Get : "<<totalCost<<", "<<cost<<", "<<idx<<", "<<m2Get<<endl;
#endif
    if(m2Get <= 0 ) { 
        return res = min(res, totalCost);
    }
    
    if( cost > largestC ) return INF;
    
    if(VCM[cost].empty()) {
        return greedy(totalCost, cost+1, 0, m2Get);
    }
    

    //close this app
    if(idx+1 >= VCM[cost].size()) {
#ifdef DEBUG_DP
cout<<totalCost<<", "<<cost<<", "<<idx<<", "<<m2Get<<" calling : greedy("<<totalCost+cost<<", "<<cost+1<<", "<<0<<", "<<m2Get-VCM[cost][idx]<<")"<<endl;
#endif
        res = min(res,greedy(totalCost + cost, cost+1, 0, m2Get-VCM[cost][idx]));
    } else {
#ifdef DEBUG_DP
cout<<totalCost<<", "<<cost<<", "<<idx<<", "<<m2Get<<" calling : greedy("<<totalCost+cost<<", "<<cost<<", "<<idx+1<<", "<<m2Get-VCM[cost][idx]<<")"<<endl;
#endif
        res = min(res,greedy(totalCost+cost, cost, idx+1, m2Get-VCM[cost][idx]));
    }
#ifdef DEBUG_DP
cout<<totalCost<<", "<<cost<<", "<<idx<<", "<<m2Get<<"calling : greedy("<<totalCost<<", "<<cost+1<<", 0, "<<m2Get<<")"<<endl;
#endif
    //do not close this app -> consider next cost
    return res = min(res,greedy(totalCost, cost+1, 0, m2Get));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    
    //memory
    for(int i = 0; i < N; i++){
        cin>>m[i];
    }
    
    // cost
    for(int i = 0; i < N; i++){
        cin>>c[i]; largestC = max(largestC, c[i]);
    }
    
    for(int i = 0 ; i < N; i++){
        VCM[c[i]].push_back(m[i]);
    }
    
    //sort
    for(int i = 0 ; i < MAX_N+1; i++){
        std::sort(VCM[i].begin(), VCM[i].end(), compare);
    }
#ifdef DEBUG_VCM
for(int i = 0; i <MAX_N+1; i++){
    if(VCM[i].empty()) continue;
    for(auto m : VCM[i]){
        cout<<"("<<i<<","<<m<<") ";
    }
    cout<<endl;
}
#endif
    
    
    //greedy
    cout<<greedy(0,0,0,M)<<endl;
    return 0;
}