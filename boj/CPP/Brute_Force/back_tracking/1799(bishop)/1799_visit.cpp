#include <iostream>

#define DEBUG_VISIT

using namespace std;

int N;
bool MAP[11][11] = {false};
int WHITE[11][11] = {0};
int BLACK[11][11] = {0};
int res = 0;
int count = 0;

void visitWhite(const int & x, const int & y, const int & weight){
	//leftup
	int X = x; int Y = y;
	while(X >=1 && Y>=1) WHITE[--X][--Y] += weight;
	
	//rightup
	X = x; Y = y;
	while(X>=1&& Y <= N-2) WHITE[--X][++Y] += weight;
	
	//leftdown
	X = x; Y = y;
	while(X <= N-2 && Y >= 1) WHITE[++X][--Y] += weight;
	
	//rightdown
	X = x; Y = y;
	while(X <= N-2 && Y <= N-2) WHITE[++X][++Y] += weight;
	
	WHITE[x][y] += weight;	
	
}

void visitBlack (const int & x, const int & y, const int & weight){
	//leftup
	int X = x; int Y = y;
	while(X >=1 && Y>=1) BLACK[--X][--Y] += weight;
	
	//rightup
	X = x; Y = y;
	while(X>=1 && Y <= N-2) BLACK[--X][++Y] += weight;
	
	//leftdown
	X = x; Y = y;
	while(X <= N-2 && Y >= 1) BLACK[++X][--Y] += weight;
	
	//rightdown
	X = x; Y = y;
	while(X <= N-2 && Y <= N-2) BLACK[++X][++Y] += weight;
	
	BLACK[x][y] += weight;	
	
}
void printMAP(int MAP[11][11]){
	for(int i = 0; i < N; i++){
		for(int j = 0 ; j < N; j++){
			cout<<MAP[i][j];
		}
		cout<<endl;
	}
}

void bishop(const int lastBishop){
	bool white;
	int nextX, nextY;

	for(int nextBishop = lastBishop; nextBishop < N*N ; nextBishop++){
        nextX = nextBishop / N; nextY = nextBishop % N;
		if( (nextX + nextY) % 2) white = false;
		else white = true;
		if(white){
			if(MAP[nextX][nextY] && WHITE[nextX][nextY]==0){
				visitWhite(nextX,nextY,1);
				count++;
				bishop(nextBishop+1);
				count--;
				visitWhite(nextX,nextY,-1);
			}
		} else {
			if(MAP[nextX][nextY] && BLACK[nextX][nextY]==0){
				visitBlack(nextX,nextY,1);
				count++;
				bishop(nextBishop+1);
				count--;
				visitBlack(nextX,nextY,-1);
			}
		}
    }
    res = max(res,count);
	return ;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //input 
    cin>>N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin>>MAP[i][j];
        }
    }
    
    //solve   
    bishop(0);
    
    //output
    cout<<res<<endl;
    return 0;
}