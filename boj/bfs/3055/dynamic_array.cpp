#include <iostream>

using namespace std;

int main(){
	int N,M;
	cin>>N,M;
	
	int MAP[N][M] = {0};
	for(int i = 0 ; i < N; i++){
		std::fill(MAP[i],MAP[i]+M,1);		
	}
	MAP[1][3] = 12;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			cout<<MAP[i][j];
		}
		cout<<endl;
	}

	return 0;
}