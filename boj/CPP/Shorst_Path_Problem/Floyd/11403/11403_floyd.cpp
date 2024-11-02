// floyd변형 : 두 정점사이에 경로가 존재하는지 구하기

#include <iostream>
#define MAX_N 100
// #define DEBUG_FLOYD
using namespace std;

int N;

bool adj[MAX_N][MAX_N] = {false};

void printadj(){
	for(int i = 0; i < N; i++){
		for(int j = 0 ; j < N; j++)
			cout<<adj[i][j]<<" ";
		cout<<endl;
	}
}
void floyd(){
	for(int k = 0; k < N; k++){
#ifdef DEBUG_FLOYD
printadj();
#endif
		for(int i = 0; i < N; i++){
			// if(adj[i][k]){
				for(int j = 0 ; j < N; j++){
					adj[i][j] = ( adj[i][j] || ( adj[i][k]  && adj[k][j] ) );
				}
			// }
		}
	}
}

int main(){
	cin>>N;
	// for(int i = 0 ; i < N; i++){
	// 	fill(adj[i], adj[i] + N, INF);
	// }
	
	for(int i = 0 ; i < N; i++){
		for(int j = 0 ; j < N; j++){
			cin>>adj[i][j];
		}
	}

	//floyd
	floyd();
	
	//output
	for(int i = 0 ; i < N; i++){
		for(int j = 0; j < N; j++){
			cout<<adj[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}