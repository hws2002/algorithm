#include <iostream>
#include <vector>
#include <memory.h>

#define MAX_V 200
#define INF 250000000

#define endl '\n'
using namespace std;

int V,M,N;
int adj[MAX_V][MAX_V] = {{INF}};
int via[MAX_V][MAX_V] = {{-1}};

void floyd(){
    for(int i = 0 ; i < V; i++) adj[i][i] = 0;
    memset(via, -1, sizeof(via));
    for(int k = 0; k < V; k++){
        for(int i = 0 ; i <V; i++){
            if(adj[i][k] != INF)
            for(int j = 0; j < V; j++){
                if( adj[i][j] > adj[i][k] + adj[k][j]){
                    adj[i][j] = adj[i][k] + adj[k][j];
                    via[i][j] = k;
                }
            }
        }
    }
}

void solve(){
    cin>>V>>M>>N;
    int a,b,c;
    
    //reset
    for(int i = 0 ; i < V; i++){
        fill(adj[i], adj[i] + V, INF);
    }
    
    for(int i = 0; i < M; i++){
        cin>>a>>b>>c;
        adj[a][b] = min( adj[a][b], c);
        adj[b][a] = min( adj[b][a], c);
    }
    
    floyd();
    
    int ret = 0;
    for(int i = 0 ; i < N; i++){
        cin>>a>>b>>c;
        if( adj[a][b] <= c || adj[b][a] <= c){
            //useless
            ret++;
        } else {
            // cout<<"build the highway and update adj"<<endl;
            adj[a][b] = c; adj[b][a] = c;
            for(int u = 0; u < V; u++){
                for(int v= 0; v < V; v++){
                    int candid = min( adj[u][a] + adj[a][b] + adj[b][v],
                                    adj[u][b] + adj[b][a] + adj[a][v]);
                    adj[u][v] = min( adj[u][v], candid );
                }
            }
            
        }
    }
    cout<<ret<<endl;
}

int main (){
    int C; cin>>C; while(C--) solve();
    return 0;
}