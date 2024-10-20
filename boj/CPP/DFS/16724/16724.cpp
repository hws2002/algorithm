// 19:44 ~ 
#include <iostream>
#include <vector>
#include <cstring>

#define MAX_N 1'000
#define endl '\n'
using namespace std;


int N,M;
// int DIREC[MAX_N][MAX_M] = {0};
vector<string> DIREC(MAX_N);
int MAP[MAX_N][MAX_N] = {0};
int res = 1;

int dfs(int x, int y, int szid){
    MAP[x][y] = szid;
    if(DIREC[x][y] == 'U'){
        if(MAP[x-1][y] > 0){
            return MAP[x][y] = MAP[x-1][y]; 
        }
        return MAP[x][y] = dfs(x-1,y,szid);
    } else if (DIREC[x][y] == 'R'){
        if(MAP[x][y+1] > 0) return MAP[x][y] = MAP[x][y+1];
        return MAP[x][y] = dfs(x,y+1,szid);
    } else if (DIREC[x][y] == 'D'){
        if(MAP[x+1][y] > 0) return MAP[x][y] = MAP[x+1][y];
        return MAP[x][y] = dfs(x+1,y,szid);
    } else {
        if(MAP[x][y-1] > 0){
            return MAP[x][y] = MAP[x][y-1];
        }
        return MAP[x][y] = dfs(x,y-1,szid);
    }
}

int main(){
    cin>>N>>M;

    for(int i = 0;  i < N; i++){
        cin>>DIREC[i];
    }
    
    //run dfs
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(MAP[i][j] == 0) {
                if(dfs(i, j, res) >= res) res++;
            }
        }
    }
    cout<<res-1<<endl;
    return 0;
}