//top-down

/*
dp(i,j) : (i,j)에서 아래층으로 내려갈때, 선택된 수의 최대 합

dp(i,j) = MAP[i][j] + max(MAP[i+1][j], MAP[i+1][j+1]);
*/

#include <iostream>
using namespace std;

int N;
int MAP[501][501] = {0};
int cache[501][501] = {0};

int dp(const int row, const int column){
    //base
    if(row >= N+1 || column > row) return 0;
    
    int& ret = cache[row][column];
    if(ret) return ret;
    return ret = MAP[row][column] + max( dp(row+1,column), dp(row+1,column+1) );
}

int main(){
    //input
    cin>>N;
    int temp;
    for(int i = 1 ; i <= N; i++){
        for(int j = 1; j <= i; j++){
            cin>>MAP[i][j];
        }
    }

    //solve
    cout<<dp(1,1)<<endl;
    return 0;
}
