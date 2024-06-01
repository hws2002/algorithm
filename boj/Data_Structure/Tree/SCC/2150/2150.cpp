// Tarjan's algorithm
// directed graph

#include <iostream>
#include <vector>
#include <stack>

#define INT 20'000
using namespace std;

int V,E; // 1<= V <= 10'000 , 1 <= E <= 100'000
vector<int> adj[10'000];
vector<int> discovered;
vector<int> sccId;
stack<int> st;

int vertexCnt = 0;
int sccCnt = 0;

// 역방향 간선이나 교차 간선을 통해 갈 수 있는 vertex중 가장 높은 간선을 return 한다. (가장 높은 간선이라하면 discovered가 가장 작은 간선)
int scc(const int here){
	discovered[here] = vertexCnt++;
	int ret = discovered[here];
	
	st.push(here);
	for(auto neighbor : adj[here]){
		if(discovered[neighbor] == -1){
			// 트리 간선이다.
			ret = min(ret, scc(neighbor));
		} else {
			// 역방향인지, 순방향인지, 교차 간선인지 알아야한다
			if(discovered[here] > discovered[neighbor]){
				// 역방향인지, 교차 간선인지 알아내야 한다.
				
				
			} else { // discovered[here] < discovred[neighbor]
				// 순방향간선이다.
				
			}
		}
	}
	finished[here] = true;
	return ret;
}

void tarjan(){
	discovered = vector<int> (V, -1);
	sccId = vector<int> (V, -1);
	for(int i = 0 ; i <V; i++)
		if(discovered[i] == -1) scc(i);
}

int main(){
	//input
	cin>>V>>E;

	int A,B;
	for(int i = 0; i < E; i++){
		cin>>A>>B;
		adj[A-1].push_back(B-1);
	}
	
	//tarjan
	tarjan();
	
	//output
	
	return 0;
}