#include <iostream>

#define MAX_N 50
#define MAX_M 50
using namespace std;

int N,M;
bool MAP[MAX_N][MAX_M] = {0};


int res = 64;

void tryout(int i, int j){
    if( i + 8 <= N && j + 8 <= M){
		bool color = MAP[i][j];
        int tofill = 0;
        for(int r = 0; r < 8; r++){
            for(int c = 0; c < 8; c++){
                if( ( (r+c) % 2 == 0 && MAP[i+r][j+c] != color ) ||
                    ( (r+c) % 2 == 1 && MAP[i+r][j+c] == color )
                    ){
                    tofill++;
                }
            }
        }
        res = min(min(tofill, 64 - tofill), res);
    }
}

int main(){
    cin>>N>>M;
    char temp;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin>>temp;
            if(temp == 'B') MAP[i][j] = 1;
            else MAP[i][j] = 0;
        }
    }
    
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j < M; j++){
            tryout(i,j);
        }
    }
    
    cout<<res<<endl;
    return 0;
}    