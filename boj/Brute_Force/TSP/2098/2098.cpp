//2098

#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;


int N;
int MAP[17][17] = {0};

ll shortestPath(){
	
}

int main(){
	//input
	cin>>N;
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			cin>>MAP[i][j];
	}
		
	//solve
	vector<int> path;
	vector<int> visited(N+1, false);
	path.push_back(1); visited[1] = true;
	cout<<shortestPath(path, visited, 0)<<endl;
	return 0;
}