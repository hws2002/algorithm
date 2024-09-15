#include <iostream>

using namespace std;

int main(){
	int N,M;
	cin>>N>>M;
	
	int ** MAP;
	bool ** VISIT;

	MAP = new int * [N+2];
	VISIT = new bool * [N+2];

	for(int i = 0 ; i <= N+1; i++){
		MAP[i] = new int[M+2];
		VISIT[i] = new bool[M+2];
		std::fill(MAP[i], MAP[i] + M + 2, 1);
		std::fill(VISIT[i]+1, VISIT[i] + M + 1, false);
		VISIT[i][0] = true;  VISIT[i][M+1] = true;
	
	}
	
	std::fill(VISIT[0], VISIT[0] + M + 2, true);
	std::fill(VISIT[N+1], VISIT[N+1] + M + 2, true);
	
	
	//printout
	
	for(int i = 0; i < N+2 ; i++){
		for(int j = 0; j < M+2; j++){
			cout<<VISIT[i][j]<<" ";	
		}
		cout<<endl;
	}
	
    for (int i = 0; i < N + 2; i++) {
        delete[] MAP[i];
    }
    delete[] MAP;
	return 0;
}