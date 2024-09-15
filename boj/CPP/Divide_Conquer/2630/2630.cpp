#include <iostream>

using namespace std;

// 0 : white, 1 : blue
bool MAP[129][129] = {0};

int c_white = 0;
int c_blue = 0;

int compress(int x , int y, int size){
    if(size == 1){
        return MAP[x][y] ? 1 : 0;
    } else {
        int half = size/2;
        int upperLeft = compress(x, y, half);
        int upperRight = compress(x, y + half, half);
        int lowerLeft = compress(x + half, y, half);
        int lowerRight = compress(x + half, y + half, half);
        if( 0 == upperLeft && upperLeft == upperRight && upperRight == lowerLeft && lowerLeft == lowerRight){
            c_white -= 3;
            return 0;
        } else if ( 1 == upperLeft && upperLeft == upperRight && upperRight == lowerLeft && lowerLeft == lowerRight){
            c_blue -= 3;
            return 1;
        } else {
            return 2;
        }
    }
}

int main(){
    //input
    int N;
    cin>>N;
    for(int i = 0 ; i < N; i++){
        for(int j = 0; j < N; j++){
            cin>>MAP[i][j];
            if(MAP[i][j]) c_blue++;
            else c_white++;
        }
    }
    
    
    //solve
    compress(0,0, N);
    
    //output
    cout<<c_white<<endl<<c_blue<<endl;
    return 0;
}