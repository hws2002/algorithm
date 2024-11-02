// floyd
#include <iostream>
#include <vector>
#include <limits.h>

#define MAX_V 400

#define INF 1'000'000'000
#define endl '\n'
using namespace std;

int adj[MAX_V][MAX_V] = {0};

int V,E;

void floyd(){
    for(int i = 0; i < V; i++)
        for(int j = 0 ; j < V; j++){
            if(i == j) adj[i][j] = 0;
            else {
                if(!adj[i][j]) adj[i][j] = INF;
            }
        }

    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            // if(adj[i][k] >= INF) continue;
            for(int j = 0 ; j < V; j++){
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>V>>E;
    int a , b, c;
    for(int i = 0; i < E; i++){
        cin>>a>>b>>c;
        adj[a-1][b-1] = c;
    }
    
    //floyd
    floyd();
    
    int res = INT_MAX;
    for(int i = 0; i < V; i++){
        for(int j = i+1; j < V; j++){
            if(adj[i][j] < INF && adj[j][i] < INF){
                res = min( res, adj[i][j] + adj[j][i] );
            }
        }
    }
    
    if(res >= INT_MAX) cout<<-1<<endl;
    else cout<<res<<endl;
    return 0;
}