// 음수 간선 x, 모든 쌍에 대해서 최단 거리 구하기
// e(u,v)가 하나이상일 수 있는 그래프
// 플로이드 와샬
// sliding window
// vertex number starts with 0!!!!!!
// INF 적당히 조절하기

#include <iostream>
#include <vector>
#include <limits.h>

#define MAX_V 100
#define INF (LLONG_MAX>>1)

typedef long long ll;
 
using namespace std;

int n,m;
ll adj[MAX_V][MAX_V] = {0};
ll dist[2][MAX_V][MAX_V] = {0};

void floyd(){
    //base C_0(u,v) = min( adj[u][v] , adj[u][0] + adj[0][v])로 설정하고, C_1(u,v) 에서부터 bottom-up
    for(int u = 0; u < n; u++){
        for(int v = 0 ; v < n; v++){
            if( u == v) dist[0][u][v] = 0;
            else {
                dist[0][u][v] = min( adj[u][v], adj[u][0] + adj[0][v] );
            }
        }
    }
    
    //floyd
    for(int k = 1; k < n; k++){
        for(int u = 0 ; u < n ; u++){
            for(int v = 0; v < n; v++){
                dist[k%2][u][v] = min( dist[(k-1)%2][u][v], dist[(k-1)%2][u][k] + dist[(k-1)%2][k][v]);
            }
        }
    }
}

int main(){
    //input
    cin>>n>>m;
    int a,b;
    ll c; // 1 <= c <= 100000
    
    for(int i = 0; i < n; i++){
        std::fill(adj[i], adj[i] + n, INF);
    }
    
    for(int i = 0 ; i < m;i++){
        cin>>a>>b>>c;
        if ( adj[a-1][b-1] > c)
            adj[a-1][b-1] = c;
        // adj[a-1][b-1] = min( adj[a-1][b-1], c); 
    }
    
    //floyd
    floyd();
    
    //output
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < n; j++){
            if(dist[(n-1)%2][i][j] >= INF) cout<<0<<" ";
            else 
            cout<<dist[(n-1)%2][i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}