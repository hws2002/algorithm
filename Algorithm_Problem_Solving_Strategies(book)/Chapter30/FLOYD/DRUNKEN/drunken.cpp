#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_V 500
#define INF 25000000

#define endl '\n'
using namespace std;

int V,E;
vector<int> T;

int adj[MAX_V][MAX_V] = {{0}};
int W[MAX_V][MAX_V] = {{0}};

void floyd(){

	vector< pair<int, int > > order;
	for(int i = 0 ; i < V; i++) order.push_back({T[i], i});
	sort(order.begin(), order.end());
	
	for(int i = 0; i <V; i++){
		for(int j =0 ; j < V; j++){
			if( i == j ) W[i][j] = 0;
			else W[i][j] = adj[i][j];
		}
	}
	
    for(int k = 0; k < V; k++){
		int w = order[k].second;
        for(int i = 0 ; i < V; i++){
            for(int j = 0; j < V; j++){
                adj[i][j] = min( adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min( adj[i][w] + T[w] + adj[w][j], W[i][j]);
            }
        }
    }
}

int main (){
    //input
    cin>>V>>E;
    T.resize(V);
    for(int i = 0; i < V; i++) {
		cin>>T[i];
		//reset
		fill( adj[i], adj[i] + V, INF);
	}

    int u,v,c;
    for(int i = 0;  i < E; i++){
        cin>>u>>v>>c;
        --u;--v;
        adj[u][v] = c; adj[v][u] = c;
    }

	floyd();
// for(int i = 0; i < V; i++){
// 	for(int j = 0; j < V; j++){
// 		cout<<"("<<adj[i][j].first<<","<<adj[i][j].second<<") ";
// 	}
// 	cout<<endl;
// }
    //query
    int Q;
    cin>>Q;
    while(Q--){
        cin>>u>>v; u--;v--;
        cout<<W[u][v]<<endl;
    }
    return 0;
}