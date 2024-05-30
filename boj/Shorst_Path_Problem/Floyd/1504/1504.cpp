// 음수 간선 x -> Floyd로 해보자

#include <iostream>
#include <vector>
#include <utility>
#include <limits.h>
#include <algorithm>

#define MAX_N 800
#define INF INT_MAX
// #define DEBUG_FLOYD

typedef long long ll;
using namespace std;
ll adj[MAX_N][MAX_N] = {0};

int N,E;
int v1,v2;

void printADJ(){
    for(int u = 0; u < N; u++){
        for(int v = 0 ; v < N; v++){
            cout<<adj[u][v]<<" ";
        }
        cout<<endl;
    }
}
void floyd(){
    
    for(int i = 0; i < N; i++){
        adj[i][i] = 0;
    }
    
    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0 ; j < N; j++){
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
}

int main(){
    
    cin>>N>>E;
    for(int i = 0 ; i < N; i++){
        std::fill(adj[i], adj[i] + N, INF);
    }
    
    int a,b,c;
    
    while(E--){
        cin>>a>>b>>c;
        adj[a-1][b-1] = c;
        adj[b-1][a-1] = c;
    }
    cin>>v1>>v2;
    v1--;
    v2--;
    //floyd
    floyd();
#ifdef DEBUG_FLOYD
printADJ();
#endif
    ll res = min(adj[0][v1] + adj[v1][v2] + adj[v2][N-1] , adj[0][v2] + adj[v2][v1] + adj[v1][N-1]);
    if(res >= INF) cout<<-1<<endl;
    else cout<<res<<endl;
    return 0;
}
