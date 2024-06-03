#include <iostream>
#include <cmath>
#include <string.h>

#define MAX_N (3*(1<<10))
using namespace std;

int N;
int K;
char canvas[MAX_N][MAX_N*2+1] = {" "};

void drawBlock(const int start_r, const int start_c, const int blockSize){
/*
- print out triangle blocks whose upper vertex position is (start_r, start_c)
- blockSize 0 will print out the answer of this problem when input is 3
	- 1 will print out that of 6
- recursive function
	- end up when start_r >= total_length or start_c < 0 or start_c >= total_width
	- decrease size for the next function call
*/

	//base2
	if(blockSize == 0){
		canvas[start_r][start_c] = '*';
		canvas[start_r+1][start_c-1] = '*'; canvas[start_r+1][start_c+1] = '*';
		canvas[start_r+2][start_c-2] = '*'; canvas[start_r+2][start_c-1] = '*';
		canvas[start_r+2][start_c] = '*'; 
	    canvas[start_r+2][start_c+1] = '*'; canvas[start_r+2][start_c+2] = '*';
		return ;
	}
	
	drawBlock(start_r - 0, start_c - 0, blockSize - 1);
	drawBlock(start_r + 3*(1<<blockSize-1), start_c - 3*(1<<blockSize-1), blockSize-1);
	drawBlock(start_r + 3*(1<<blockSize-1), start_c + 3*(1<<blockSize-1), blockSize-1);
}

void printStar11(){
	for(int i = 0 ; i < MAX_N; i++){
		memset(canvas[i], ' ',MAX_N*2);
		canvas[i][MAX_N*2] = '\0';
	}
	
	cin>>N;
	K = log2(N);
	int end_r = N;
	int end_c = 1 + 2 * (N-1);
	int start_r = 0; int start_c = end_c/2; // N-1
	
	drawBlock(start_r,start_c,K-1);
	
	for(int i = 0 ; i < end_r; i++){
	    for(int j = 0 ; j < end_c; j++){
	        cout<<canvas[i][j];
	    }
	    cout<<endl;
	}
}

int main(){
	printStar11();
	return 0;
}