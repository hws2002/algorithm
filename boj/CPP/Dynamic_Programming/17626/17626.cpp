#include <iostream>
#include <cmath>

using namespace std;

int cache[50001] = {0};

int FourSquares(int n){
	if( n <= 0 ) return 0;
	int& ret = cache[n];
	if(ret) return ret;
	ret = 4;
	// cout<<sqrt(n)<<endl;
	for(int i = sqrt(n); i>=1; i--){
		ret = min(ret, 1 + FourSquares(n-i*i) );
		if(ret == 1) return ret;
	}
	return ret;
}

int main(){
	int n; // 1<= n <= 50'000
	cin>>n;
	cache[1] = 1;
	cache[2] = 2;
	cache[3] = 3;

	cout<<FourSquares(n)<<endl;
	return 0;
}