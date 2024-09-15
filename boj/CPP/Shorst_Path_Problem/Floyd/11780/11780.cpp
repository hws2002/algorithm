// 사이클 x, 음수간선 x
// 방향 그래프
// 플로이드

#include <iostream>
#include <vector>
#include <limits.h>

#define MAX_N 100
#define MAX_M 100'000
#define INF 1000'000'000'000

#define DEBUG_INPUT

#define endl '\n'
typedef long long ll;
using namespace std;

ll dist[MAX_N][MAX_N] = {0};
int n,m;
vector<int> shortestPaths[MAX_N][MAX_N];

void update(int i, int k, int j){
    shortestPaths[i][j].clear();
    shortestPaths[i][j] = shortestPaths[i][k];
    shortestPaths[i][j].insert(shortestPaths[i][j].end(), ++shortestPaths[k][j].begin(), shortestPaths[k][j].end());
}

void floyd(){
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            if( dist[i][k] >= INF) continue;
            for(int j = 0; j < n; j++){
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    //update shortestPaths
                    update(i,k,j);
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main(){
    cin>>n>>m;
    int a, b; ll c;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if( i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }
    
    for(int i = 0 ; i < m; i++){
        cin>>a>>b>>c;
        dist[a-1][b-1] = min( dist[a-1][b-1], c);
        if(shortestPaths[a-1][b-1].empty()){
            shortestPaths[a-1][b-1].push_back(a-1);
            shortestPaths[a-1][b-1].push_back(b-1);
        }
    }
    // floyd
    // get routes simultaneously
    floyd();
    
    
    //output
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < n; j++){
			if( i == j || dist[i][j] >= INF) cout<<0<<" ";
			else cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < n; j++){
            cout<<shortestPaths[i][j].size()<<" ";
            for(auto p : shortestPaths[i][j]){
                cout<<p+1<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}