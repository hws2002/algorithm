//dfs

#include <iostream>
#include <queue>

using namespace std;

int N,M;
int MAP[602][602] = {0};
bool VISIT[602][602] = {false};
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int res = 0;

void solveBfs(int y, int x){
	for(int i = 0 ; i <4 ; i++){
		if( MAP[y + dy[i]][x + dx[i]] && !VISIT[y + dy[i]][x + dx[i]]){
			if(MAP[y + dy[i]][x + dx[i]] == 2) res++;
			VISIT[y + dy[i]][x + dx[i]] = true;
			solveBfs(y + dy[i], x + dx[i]);
		}
	}
}

int main(){
	//input
	int x, y;
	cin>>N>>M;
	char temp;
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= M; j++){
			cin>>temp;
			if(temp == 'O'){
				MAP[i][j] = 1;
			} else if (temp == 'I'){
				MAP[i][j] = 1;
				y = i; x = j;
			} else if(temp == 'P'){
				MAP[i][j] = 2;
			} else { // temp == 'X'
				//do nothing
			}
		}
	}
	
	//solve - bfs
	solveBfs(y,x);
	
	
	//output
	if(res) cout<<res<<endl;
	else cout<<"TT"<<endl;
	return 0;
}