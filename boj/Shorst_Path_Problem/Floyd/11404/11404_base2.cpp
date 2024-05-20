// 음수 간선 x, 모든 쌍에 대해서 최단 거리 구하기
// e(u,v)가 하나이상일 수 있는 그래프
// 플로이드 와샬
// without memory optimization
// vertex number starts with 1!!!!!!
#include <iostream>
#include <vector>

#define MAX_V 101

typedef long long ll;
 
using namespace std;

int n,m;
ll dist[MAX_V][MAX_V][MAX_V] = {0};

void floyd(){
    //floyd
    for(int k = 1 ; k <=n ; k++){
        for(int u = 1; u <= n ; u++){
            for(int v = 1; v <= n; v++){
                if(u==v) dist[k][u][v] = 0;
                else {
                    ll u_k = dist[k-1][u][k];
                    ll k_v = dist[k-1][k][v];
                    if( dist[k-1][u][v] == 0){
                        if( u_k && k_v){
                            dist[k][u][v] = u_k + k_v;    
                        } else {
                            dist[k][u][v] = 0;
                        }
                    } else {
                        if( u_k && k_v) {
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
    ll c; // 1 <= c <= 100000
    
//base C_{0}(u,v) = adj[u][v] 로 설정하고, C_1(u,v) 에서부터 C_n(u,v)까지 bottom-up
    for(int i = 0 ; i < m;i++){
        cin>>a>>b>>c;
        if ( dist[0][a][b] ) {
            dist[0][a][b] = min( dist[0][a][b], c); 
        } else dist[0][a][b] = c;
    }
    
    //floyd
    floyd();
    
    //output
    for(int i = 1 ; i <= n; i++){
        for(int j = 1 ; j <= n; j++){
            cout<<dist[n][i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}