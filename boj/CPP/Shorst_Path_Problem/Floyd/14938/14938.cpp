//floyd

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits.h>
#include <algorithm>

#define MAX_N 100
#define INF (INT_MAX>>1)


// #define DEBUG_FLOYD
using namespace std;

int n,m,r;
vector<int> items;
int adj[MAX_N][MAX_N];


void floyd(){
    for(int i = 0 ; i < n ; i++) adj[i][i] = 0;
    
    for(int k = 0 ; k < n ; k++){
        for(int i = 0 ; i < n; i++){
            for(int j = 0; j < n; j++){
                adj[i][j] = min(adj[i][j],adj[i][k] + adj[k][j]);
            }
        }
    }
    
}

int main(){
    cin>>n>>m>>r;
    items = vector<int> (n,0);
    
    for(int i = 0 ; i < n; i++){
        cin>>items[i]; 
    }
    
    for(int i = 0 ; i < MAX_N; i++){
        std::fill(adj[i] , adj[i] + MAX_N, INF);
    }
    
    int a,b,w;
    for(int i = 0 ; i < r; i++){
        cin>>a>>b>>w;
        adj[a-1][b-1] = w;
        adj[b-1][a-1] = w;
    }
    
    //floyd
    floyd();

#ifdef DEBUG_FLOYD
cout<<" printing out adj "<<endl;
for(int i = 0; i < n; i++){
    for(int j = 0 ; j < n ; j++){
        cout<<adj[i][j]<<" ";
    }
    cout<<endl;
}
#endif
    //find best place
    int maxItem = 0;
    for(int here = 0 ; here < n ; here++){
        // aggregate all the items that can be achieved when landing on thsi vertex
        int itemAchievable = 0;
        for(int there = 0; there < n; there++){
            if(adj[here][there] <= m){
                itemAchievable += items[there];
            }
        }
        maxItem = max(maxItem, itemAchievable);
    }
    
    //output
    cout<<maxItem<<endl;
    return 0;
}