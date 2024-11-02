#include <iostream>

using namespace std;
typedef long long ll;

ll A[100];
int main(){
	freopen("input.txt","r",stdin);
	int N;
	cin>>N;
	for(int i = 0 ; i < N; i++){
		cin>>A[i];
	}
	
	ll K;
	cin>>K;
	
	for(int i = 0; i < N; i++){
		cout<< A[i] % K <<endl;
	}
	return 0;
}
