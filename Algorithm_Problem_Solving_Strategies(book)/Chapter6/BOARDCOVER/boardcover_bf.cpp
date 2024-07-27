//https://algospot.com/judge/problem/read/BOARDCOVER
#include <iostream>
#include <string>

#define MAX_H 20
#define OPTIMIZE
#define endl '\n'

// #define DEBUG_INPUT
// #define DEBUG_BF
using namespace std;

// # : false, . : true
bool MAP[MAX_H][MAX_H] = {false};
int res = 0;

pair<int,int> boxtype[4][3] = {
	{{0,0}, {0,1}, {1,0} },
	{{0,0}, {0,1}, {1,1} },
	{{0,0}, {1,0}, {1,-1} },
	{{0,0}, {1,0}, {1,1} }
};

/*

##  ##   #  #
#    #  ##  ##

*/

int H,W;

bool isLastPosi(const int & x,const int & y){
	if( x == H-1 && y == W-1) return true;
	return false;
}

bool cancover(const int & x, const int & y,const int & btype, const bool & ctype){
	// printf("cancover(%d,%d,%d,%d) \n",x,y,btype,ctype);
	bool coverable = true;
	
	for(int i = 0; i < 3; i++){
		auto tocover = boxtype[btype][i];
		int nx = x + tocover.first;
		int ny = y + tocover.second;
		if(!(0 <= nx && nx < H && 0 <= ny && ny < W)){
			coverable = false;
		} else { 
			if(MAP[nx][ny] != ctype) coverable = false; 
			MAP[nx][ny] = !MAP[nx][ny];
		}
	}
	
	return coverable;
}

void countFrom(int x, int y){
	
	if(isLastPosi(x,y)){
		if(!MAP[x][y]) {
			// printf("res+=1 !\n");
			res++;
		}
		return ;
	}
	
	if(!MAP[x][y])
		countFrom( (x + (y+1)/W ), (y+1) % W );
	else {
#ifdef DEBUG_BF
	printf("countFrom(%d,%d)\n", x, y);
for(int i = 0; i < H; i++){
	for(int j = 0; j < W; j++)
		printf("%d ",MAP[i][j]);
	printf("\n");
}
#endif
		for(int type = 0; type < 4; type++){
			if(cancover(x, y, type, true)) // cover
				countFrom( (x + (y+1)/W ), (y+1) % W);
			cancover(x, y, type, false); //uncover
		}
	}
}

void solve(){
	cin>>H>>W;
#ifdef OPTIMIZE
	int blankcount = 0;
#endif
	for(int i = 0; i < H; i++){
		string temp;
		cin>>temp;
		for(int j = 0; j < W; j++){
			if(temp[j] == '#') {
				MAP[i][j] = 0;
			} else {
				MAP[i][j] = 1;
#ifdef OPTIMIZE
				blankcount++;
#endif
			}
		}
	}
	
#ifdef DEBUG_INPUT
for(int i = 0; i < H; i++){
	for(int j = 0; j < W; j++)
		cout<<MAP[i][j]<<" ";
	cout<<endl;
}
#endif
	
#ifdef OPTIMIZE
	if(blankcount % 3) {cout<<res<<endl; return ;}
#endif

	//brute force
	res = 0;
	countFrom(0,0);
	cout<<res<<endl;
}


int main(){
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	// cout.tie(NULL);
	
	int C;
	cin>>C;
	while(C--){
		solve();
	}
	
	return 0;
}