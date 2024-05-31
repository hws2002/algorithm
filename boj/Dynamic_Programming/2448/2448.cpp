#include <iostream>
#include <cmath>

using namespace std;

int N;
int K;

void printBlock(const int start_r, const int start_c, const int end_r, const int end_c, const int blockSize, bool isleft){
/*
- print out triangle blocks whose upper vertex position is (start_r, start_c)
- blockSize 0 will print out the answer of this problem when input is 3
	- 1 will print out that of 6
- recursive function
	- end up when start_r >= total_length or start_c < 0 or start_c >= total_width
	- decrease size for the next function call
*/
	//base1
	if(blockSize < 0) return;

	//base2
	if( start_r >= total_length || start_c < 0 || start_c >= total_width) return ;
	
	//base3
	if(blockSize == 0){
		for(int r = 0 ; r < start_r; r++) cout<<" ";
		cout<<"*";
		for(int r = start_r+1; r < )
	}
	
	total_length =
	pinrtBlock(start_r - 0, start_c - 0, blockSize - 1);
	printBlock(start_r + 3*blockSize, start_c - 3*, blockSize-1, true);
	printBlock(start_r + 3*blockSize, start_c + 3*, blockSize-1, false);
}

void printStar11(){
	cin>>N;
	K = log2(N);
	int end_r = N;
	int end_c = 1 + 2 * (N-1);
	int start_r = 0; start_c = total_width/2;
	printBlock(r,c,end_r, end_c, K+1);
}

int main(){
	printStar11();
	return 0;
}