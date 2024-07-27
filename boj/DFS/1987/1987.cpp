//DFS
#include <iostream>
#include <cstring>
using namespace std;

int R,C;
int MAP[22][22] = {0};
int NUM_VISIT[27] = {0};

int res = 0;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

void dfs(const int r, const int c, int & count){
    
    for(int i = 0; i < 4; i++){
        if(MAP[r + dr[i]][c + dc[i]] && NUM_VISIT[MAP[r + dr[i]][c + dc[i]]] <= 0){
            count++;
            NUM_VISIT[MAP[r+dr[i]][c + dc[i]]]+=1;
            dfs(r + dr[i], c + dc[i], count);
            count--;
            NUM_VISIT[MAP[r+dr[i]][c + dc[i]]]-=1;
        }
    }
    res = max(res, count);
}

int main(){  
    cin>>R>>C;
    string temp;
    for(int i = 1 ; i <= R; i++){
        cin>>temp;
        for(int j = 0 ; j < temp.size() ; j++)
            MAP[i][j+1] = temp[j] - '@';
    }
    //dfs
    int count = 1;
    
    NUM_VISIT[MAP[1][1]] += 1;
    dfs(1,1,count);
    
    //output
    cout<<res<<endl;
    return 0;
}