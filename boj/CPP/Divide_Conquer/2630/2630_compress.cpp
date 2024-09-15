//compress
#include <iostream>
#include <cstring>

using namespace std;

// 0 : white, 1 : blue
bool MAP[129][129] = {0};

int c_white = 0;
int c_blue = 0;

string compress(int x , int y, int size){
    if(size == 1){
        return MAP[x][y] ?  string("b") : string("w");
    } else {
        int half = size/2;
        string upperLeft = compress(x, y, half);
        string upperRight = compress(x, y + half, half);
        string lowerLeft = compress(x + half, y, half);
        string lowerRight = compress(x + half, y + half, half);
		if( string("w") == upperLeft && upperLeft == upperRight && upperRight == lowerLeft && lowerLeft == lowerRight){
			return string("w");
		} else if ( string("b") == upperLeft && upperLeft == upperRight && upperRight == lowerLeft && lowerLeft == lowerRight){
			return string("b");
		} else
        return string("x") + upperLeft + upperRight + lowerLeft + lowerRight;
    }
}

int main(){
    //input
    int N;
    cin>>N;
    for(int i = 0 ; i < N; i++){
        for(int j = 0; j < N; j++){
            cin>>MAP[i][j];
        }
    }
    
    
    //solve
    string compressed = compress(0,0, N);
    
	// cout<<compressed<<endl;
    //output
    for(string::iterator iter = compressed.begin(); iter != compressed.end(); iter++){
        if( *iter == 'w') c_white++;
        else if( *iter == 'b') c_blue++;
    }
    cout<<c_white<<endl<<c_blue<<endl;
    return 0;
}