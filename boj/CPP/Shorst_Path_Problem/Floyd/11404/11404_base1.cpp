// 음수 간선 x, 모든 쌍에 대해서 최단 거리 구하기
// e(u,v)가 하나이상일 수 있는 그래프
// 플로이드 와샬
// without memory optimization
// vertex number starts with 0!!!!!!

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_V 100

typedef long long ll;
 
using namespace std;

int n,m;
int adj[MAX_V][MAX_V] = {0};
ll dist[MAX_V][MAX_V][MAX_V] = {0};

void floyd(){
    //base C_0(u,v) = min( adj[u][v] , adj[u][0] + adj[0][v])로 설정하고, C_1(u,v) 에서부터 bottom-up
    for(int u = 0; u < n; u++){
        for(int v = 0 ; v < n; v++){
            if( u == v) dist[0][u][v] = 0;
            else {
                ll u_zero = adj[u][0];
                ll zero_v = adj[0][v];
                if(adj[u][v] == 0){
                    if( u_zero && zero_v){
                        dist[0][u][v] = u_zero + zero_v;
                    } else {
                        dist[0][u][v] = 0;
                    }
                } else {
                    if( u_zero && zero_v) {
                        if( adj[u][v] > u_zero + zero_v)
                            dist[0][u][v] = u_zero + zero_v;
                        else 
                            dist[0][u][v] = adj[u][v];
                        // dist[0][u][v] = min( adj[u][v] , u_zero + zero_v);
                    } else {
                        dist[0][u][v] = adj[u][v];
                    }
                }
            }
        }
    }
    
    //floyd
    for(int k = 1; k < n; k++){
        for(int u = 0 ; u < n ; u++){
            for(int v = 0; v < n; v++){
                if( u == v) dist[k][u][v] = 0;
                else {
                    ll u_k = dist[k-1][u][k];
                    ll k_v = dist[k-1][k][v];
                    if(dist[k-1][u][v] == 0){
                        if( u_k && k_v){
                            dist[k][u][v] = u_k + k_v;
                        } else {
                            dist[k][u][v] = 0;
                        }
                    } else {
                        if (u_k && k_v){
                            dist[k][u][v] = min( dist[k-1][u][v] , u_k + k_v);
                        } else {
                            dist[k][u][v] = dist[k-1][u][v];
                        }
                    }
                }
            }
        }
    }
}

int main(){
    //input
    cin>>n>>m;
    int a,b;
    ll c; // 0 <= c <= 100000
    for(int i = 0 ; i < m;i++){
        cin>>a>>b>>c;
        if ( adj[a-1][b-1] ) {
            if ( adj[a-1][b-1] > c)
                adj[a-1][b-1] = c;
            // adj[a-1][b-1] = min( adj[a-1][b-1], c); 
        }else adj[a-1][b-1] = c;
    }
    
    //floyd
    // for(int i = 0 ; i < n ; i++)
    //     std::fill(dist[i], dist[i] + n , INF);
    floyd();
    
    //output
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < n; j++){
            // if(dist[i][j] >= INF) cout<<0<<" ";
            // else 
            cout<<dist[n-1][i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}