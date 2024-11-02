#include <iostream>
#include <queue>
using namespace std;

int main(int argc, char* argv[]){
	
	// take input and store into array
	int N,M;
	
	cin>>N>>M;
	
	// prepare ladder and snake
	int LADDER[101] = {0};
	int SNAKE[101] = {0};
	for (int i = 0 ; i< N; i++) {
		int x, y;
		cin >> x >> y;
		LADDER[x] = y;
	}
	
	for (int i = 0; i< M; i++){
		int u,v;
		cin >> u >> v;
		SNAKE[u] = v;
	}
	// BFS
	
	// 1. initialize a queue so as to store latent "current" posits
	queue<int> Q[18];
	Q[0].push(1);
	int steps = 0;
	int current_posi = 0;
	
	// 2. initialize a array which will record the visitation of posits
	bool VISITED[101] = {false};
	VISITED[1] = true;
	
	// loop
	while(current_posi < 100){
		if(!Q[steps].empty()){
			current_posi = Q[steps].front(); Q[steps].pop();

			// check if we can reach 100
			if (current_posi + 6 >= 100){
				cout<<++steps<<endl;
				return 0;
			}

			for(int i = 6; i >=1 ; i--){// if not, check every possible steps
				int next_posi = current_posi + i;
				// if the position is already in queue, or have been visitd before, skip that
				if (VISITED[next_posi]) continue;

				if (SNAKE[next_posi]) {
					VISITED[next_posi] = true;
					next_posi = SNAKE[next_posi];
					if (VISITED[next_posi]) continue;
				} else if (LADDER[next_posi]) {
					VISITED[next_posi] = true;
					next_posi = LADDER[next_posi];
					if (VISITED[next_posi]) continue;
				} else {
					//do nothing;
				}

				// we can insert this new position into queue
				VISITED[next_posi] = true;
				Q[steps+1].push(next_posi);
			}
		} else {
			steps++;
		}
	}
	cout<<++steps<<endl;
	return 0;
}