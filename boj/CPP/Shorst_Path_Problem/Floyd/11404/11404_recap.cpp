#include <iostream>
#include <limits.h>

#define MAX_N 100
#define INF 1'000'000'000'000
typedef long long ll;
using namespace std;

int n, m;
ll dist[MAX_N][MAX_N] = {0};

void floyd(){
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dist[i][j] = min( dist[i][k] + dist[k][j] , dist[i][j] );
            }
		}
    }
}

int main(){
    cin>>n>>m;
    int a,b;
    ll c;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			if( i == j ) dist[i][j] = 0;
			else dist[i][j] = INF;
	}
    for(int i = 0; i < m ; i++){
        cin>>a>>b>>c;
        dist[a-1][b-1] = min( dist[a-1][b-1] , c);
    }
    //floyd
    
    floyd();
    
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n ;j++){
            if( dist[i][j] == INF) cout<<0<<" ";
            else cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}