#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N;
bool MAP[11][11] = {false};
int res = 0;
vector<int> Vector_White;
vector<int> Vector_Black;
vector<int>::iterator iter;

bool isSafe(const int & nextX, const int & nextY, const bool & white){
    int X,Y;
	
	if(white) {
		for(iter = Vector_White.begin(); iter != Vector_White.end(); iter++){
			X = (*iter) / N; Y = (*iter) % N;
			if( nextX - X == nextY - Y || nextX - X == Y - nextY) return false;
		}
	} else {
		for(iter = Vector_Black.begin(); iter != Vector_Black.end(); iter++){
			X = (*iter) / N; Y = (*iter) % N;
			if( nextX - X == nextY - Y || nextX - X == Y - nextY) return false;
		}
	}
    return true;
}

void bishop(const int lastBishop){
	int available = 0;
	for(int i = lastBishop; i < N*N; i++){
		if(MAP[i/N][i%N]) available++;
	}
    if( available + Vector_White.size()  + Vector_Black.size() <= res) return ;
    for(int nextBishop = lastBishop; nextBishop < N*N ; nextBishop++){
        int nextX = nextBishop / N; int nextY = nextBishop % N;
		bool white;
		if( (nextX + nextY) % 2) white = false;
		else white = true;
        if(MAP[nextX][nextY] && isSafe(nextX, nextY,white)){
			if(white) Vector_White.push_back(nextBishop);
			else Vector_Black.push_back(nextBishop);
			// Vector_Group.push_back(nextBishop); 
			MAP[nextX][nextY] = false;
            bishop(nextBishop+1);
			if(white){
	            if(!Vector_White.empty()) Vector_White.pop_back(); 
			} else {
				if(!Vector_Black.empty()) Vector_Black.pop_back();
			}
			MAP[nextX][nextY] = true;
        }
    }
    
    if( Vector_Black.size() + Vector_White.size() > res) res = Vector_Black.size()  + Vector_White.size();
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