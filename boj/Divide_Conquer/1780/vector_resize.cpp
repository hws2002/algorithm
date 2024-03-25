#include <iostream>
#include <vector>

using namespace std;

int main(){
	vector< vector<int> > Vector_v;
	int N = 5;
	Vector_v.resize( N-1, vector<int> (N,1));
	for(int i = 0; i < N; i++){
		for(int j = 0 ; j < N; j++){
			cout<<Vector_v[i][j];
		}
		cout<<endl;
	}
	return 0;
}