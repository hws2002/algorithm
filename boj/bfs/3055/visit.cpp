#include <iostream>

using namespace std;

int main(){
	bool VISIT[4][4] = {false};
	
	for(int i = 0 ; i < 4 ; i++){
		for(int j = 1; j< 4; j++){
			cout<<VISIT[i][j];
		}
		cout<<endl;
	}
	return 0;
}