//DFS
#include <iostream>
#include <vector>
#include <limits.h>
typedef long long ll;
using namespace std;
vector<int> path;

int N;
int MAP[11][11] = {false};
int VISIT[11] = {false};
ll res=LLONG_MAX;
ll length=0;

void shortestPathDFS(){
	if(path.size() == N){
		if(MAP[path.back()][path[0]]) {
			res = min(res, length+MAP[path.back()][path[0]]);
		}
		return ;
	}
	
	int here = path.back();
	
	for(int next = 1; next <= N; next++){
		if(!VISIT[next] && MAP[here][next]){
			path.push_back(next);
			VISIT[next] = true;
			length += MAP[here][next];	
			shortestPathDFS();
			path.pop_back();
			VISIT[next] = false;
			length -= MAP[here][next];
		}
	}
}

int main(){
	//input
	cin>>N;
	for(int i = 1 ; i <=N; i++){
		for(int j = 1; j <=N; j++)
			cin>>MAP[i][j];
	}
	
	//solve
	path.push_back(1); VISIT[1] = true;
	shortestPathDFS();
	cout<<res<<endl;
	return 0;
}