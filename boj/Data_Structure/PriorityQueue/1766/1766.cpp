// priority queue?

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_N 32'000
#define MAX_M 100'000
#define endl '\n'
using namespace std;

vector<int> adj[MAX_N];
vector<int> inDegree;

int N,M;

void bfs(){
	priority_queue<int, vector<int> , greater<> > pq; // ascending order
	for(int i = 0; i < N; i++){
		if(inDegree[i] <= 0) pq.push(i);
	}
	while(!pq.empty()){
		int here = pq.top(); pq.pop();
		cout<<here+1<<" ";
		for(int i = 0; i < adj[here].size(); i++){
			int next = adj[here][i];
			inDegree[next]--;
			if(inDegree[next] <= 0) {
				pq.push(next);
			}
		}
	}
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    inDegree = vector<int> (N,0);
    int A,B;
    for(int i = 0 ; i < M; i++){
        cin>>A>>B;
        adj[A-1].push_back(B-1);
		inDegree[B-1] += 1;
    }
    
    //solve
	bfs();
	
    return 0;
}